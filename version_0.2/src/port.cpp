#include "../lib/port.h"

port::port(uint16_t portNum){
    this->portNum = portNum;
}

port::~port(){}

port8bit::port8bit(uint16_t portNum)
: port(portNum){}

port8bit::~port8bit(){}

void port8bit::write(uint8_t data){
__asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (portNum));
}

uint8_t port8bit::read(){
    uint8_t result;
    __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (portNum));
    return result;
}

port8bitSlow::port8bitSlow(uint16_t portNum)
: port8bit(portNum){}

port8bitSlow::~port8bitSlow(){}

void port8bitSlow::write(uint8_t data){
__asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (data), "Nd" (portNum));
}

port16bit::port16bit(uint16_t portNum)
: port(portNum){}

port16bit::~port16bit(){}

void port16bit::write(uint16_t data){
__asm__ volatile("outw %0, %1" : : "a" (data), "Nd" (portNum));
}

uint16_t port16bit::read(){
    uint16_t result;
    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (portNum));
    return result;
}

port32bit::port32bit(uint16_t portNum)
: port(portNum){}

port32bit::~port32bit(){}

void port32bit::write(uint32_t data){
__asm__ volatile("outl %0, %1" : : "a" (data), "Nd" (portNum));
}

uint32_t port32bit::read(){
    uint32_t result;
    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (portNum));
    return result;
}
