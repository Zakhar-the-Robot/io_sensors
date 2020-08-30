#include <Arduino.h>
#include <Wire.h>
#include "common.h"
#include "registers.hpp"
#include "printf.h"
#include "ArduinoLog.h"
#define BUILTIN_LED 13


int sensorValue = 0; // variable to store the value coming from the sensor

//handling read from master
void i2c_reqEv()
{
    uint8_t val = regs.GetReg();
    Log.verbose("Read: val - 0x%x\n", val);
    Wire.write(val);
}

// handling write or read from master
void i2c_rcvEv(int howMany)
{
    uint32_t reg_num = (uint32_t)Wire.read();
    uint32_t val = (uint32_t)Wire.read();
    if (val == 0xff) { // handling read
        Log.verbose("Read: from 0x%x\n", reg_num);
        regs.SelectReg(reg_num);
    } else { // handling write
        Log.verbose("Write: 0x%x to 0x%x\n", val, reg_num);
        regs.Write(reg_num, val);
    }

    if (Wire.available()) { // if extra data
        Log.warning("Unexpected extra data\n");
        Wire.flush();
    }
}



void setup()
{
    Serial.begin(9600);
    // printf_init();
    Log.begin(LOG_LEVEL, &Serial);
    printf("hello");
    Serial.println("hello");

    Wire.begin(DEVICE_I2C_ADDRESS);
    Wire.onRequest((void (*)())i2c_reqEv);    // register event
    Wire.onReceive((void (*)(int))i2c_rcvEv); // register event

    pinMode(PIN_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output

    /* ??? */
    pinMode(A2, OUTPUT);          // Initialize the BUILTIN_LED pin as an output
    digitalWrite(A2, HIGH);       // Initialize the BUILTIN_LED pin as an output
    /* ??? */

    Log.notice("Init complete");
}

void loop()
{
    int val = analogRead(PIN_SENSOR_PHOTORES);
    REGW(REG_LIGHT_LO, ((uint8_t)(val >> 0) & 0xFF));
    REGW(REG_LIGHT_HI, ((uint8_t)(val >> 8) & 0xFF));
    // i2c.SelectReg(0);
    // i2c.SetRegAndNext((uint8_t)(val>>0)&0xFF);
    // i2c.SetRegAndNext((uint8_t)(val>>8)&0xFF);
    if (val <= 200) {
        digitalWrite(BUILTIN_LED, HIGH); //led off
    }
    digitalWrite(BUILTIN_LED, LOW); //led on - defaults
    _delay_ms(10);

}