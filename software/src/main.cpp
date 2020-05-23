#include "I2c.h"
#include "VirtualRegs.h"
#include "printf.h"
#include <Arduino.h>
#include <Wire.h>
#define BUILTIN_LED 13
#define I2C_ADDRESS 0x2b
#define REGS_NUM 8

int sensorPin = A3;  // select the input pin
int sensorValue = 0; // variable to store the value coming from the sensor

I2C i2c;
void i2c_reqEv() { I2C::requestEvent(i2c); }
void i2c_rcvEv(int howMany) { I2C::receiveEvent(i2c); }

void setup() {
    i2c.Init(I2C_ADDRESS, 4, (void *)i2c_reqEv, (void *)i2c_rcvEv);
    pinMode(BUILTIN_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output
    pinMode(A2, OUTPUT);          // Initialize the BUILTIN_LED pin as an output
    digitalWrite(A2, HIGH);       // Initialize the BUILTIN_LED pin as an output
    Serial.begin(9600);
    printf_init();
}

void loop() {
    int val = analogRead(sensorPin);
    i2c.Set(2,(uint8_t)(val>>0)&0xFF);
    i2c.Set(3,(uint8_t)(val>>8)&0xFF);
    // i2c.SelectReg(0);
    // i2c.SetRegAndNext((uint8_t)(val>>0)&0xFF);
    // i2c.SetRegAndNext((uint8_t)(val>>8)&0xFF);
    if (val <= 200) {
        digitalWrite(BUILTIN_LED, HIGH); //led off
    }
    digitalWrite(BUILTIN_LED, LOW); //led on - defaults
    i2c.Print();
    _delay_ms(10);

}