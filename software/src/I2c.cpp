#include "I2c.h"
#include <Wire.h>

#define DEBUG 0

#if DEBUG
#warning "In debug mode I2C works non-stable"
#define LOG(...) (printf(__VA_ARGS__))
#else
#define LOG(...)
#endif

I2C::I2C(uint32_t address, uint32_t regs_num, void * requestEvent, void * receiveEvent) {
    Init(address, regs_num, requestEvent, receiveEvent);
}

void I2C::Init(uint32_t address, uint32_t regs_num, void * requestEvent, void * receiveEvent) {
    this->addr = address;
    this->regs.Init(regs_num);
    Wire.begin((int)address);
    this->SetEvents(requestEvent, receiveEvent);
}

void I2C::PrintRegsContent(void) {
#if DEBUG
    printf("Registers:");
    uint8_t *reg_arr = regs.GetRegs();
    for (uint32_t i = 0; i < regs.GetRegsAmmount(); i++) {
        printf(" %lx:0x%x", i, reg_arr[i]);
    }
    printf("\n");
#endif
}

void I2C::SetEvents(void *requestEvent, void *receiveEvent) {
    Wire.onRequest((void (*)())requestEvent);    // register event
    Wire.onReceive((void (*)(int))receiveEvent); // register event
}

void I2C::SelectReg(uint32_t num) {
    this->regs.SelectReg(num);
    LOG("[I2C] Selected reg: 0x%lx\n", this->regs.GetSelectedRegNum());
}

void I2C::SelectNextReg(void) {
    this->regs.SelectNextReg();
    LOG("[I2C] Selected reg: 0x%lx\n", this->regs.GetSelectedRegNum());
}

void I2C::SetReg(uint8_t byte) {
    this->regs.SetReg(byte);
    LOG("[I2C] Wrote 0x%x to reg 0x%lx\n", byte, regs.GetSelectedRegNum());
}

void I2C::SetRegAndNext(uint8_t byte) {
    this->SetReg(byte);
    this->SelectNextReg();
}

uint8_t I2C::GetReg(void) {
    return this->regs.GetReg();
}

uint8_t I2C::GetRegAndNext(void) {
    return this->regs.GetRegAndNext();
}

uint8_t I2C::WriteReg(void) {
    uint8_t reg_val = this->regs.GetReg();
    Wire.write(&reg_val, (size_t)1);
    LOG("[I2C] Sent: %x\n", reg_val);
    return reg_val;
}

uint8_t I2C::WriteRegAndNext(void) {
    uint8_t reg_val = this->WriteReg();
    this->SelectNextReg();
    return reg_val;
}

uint8_t I2C::ReadToReg(void) {
    uint8_t val = Wire.read();
    regs.SetReg(val);
    return val;
}

uint8_t I2C::ReadToRegAndNext(void) {
    uint8_t val = this->ReadToReg();
    this->SelectNextReg();
    return val;
}

void I2C::Set(uint32_t reg_number, uint8_t value){
    if(reg_number>= this->regs.GetRegsAmmount()){
        return;
    } else{
        uint8_t *reg_arr = this->regs.GetRegs();
        reg_arr[reg_number] = value;
    }
}
uint8_t I2C::Get(uint32_t reg_number){
    if(reg_number>= this->regs.GetRegsAmmount()){
        return 0;
    } else{
        uint8_t *reg_arr = this->regs.GetRegs();
        return reg_arr[reg_number];
    }
}
void I2C::Print(void){
    printf("Registers:");
    uint8_t *reg_arr = this->regs.GetRegs();
    for (uint32_t i = 0; i < this->regs.GetRegsAmmount(); i++) {
        printf(" %lx:0x%x", i, reg_arr[i]);
    }
    printf("\n");
}

void I2C::requestEvent(I2C & i2c_instance) {
    i2c_instance.WriteRegAndNext();
}

void I2C::receiveEvent(I2C & i2c_instance) {
    uint32_t reg_num = (uint32_t)Wire.read();
    i2c_instance.SelectReg(reg_num); // set reg num

    if(Wire.available()){ // if extra data
        while (Wire.available()) { // if we have a multiple bytes
            i2c_instance.ReadToRegAndNext();
        }
    }
}

