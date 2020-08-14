#include "../lib/interrupts.h"

interruptManager::gateDescriptor interruptManager::IDT[256];

void print(char* str);

const uint8_t IDT_DESC_PRESENT = 0x80;

    void interruptManager::setIDTentry(uint8_t interruptNumber, uint16_t CodeSegment, void (*handler)(), uint8_t discriptorAccess, uint8_t discriptorType){
        IDT[interruptNumber].handlerLo = ((uint32_t)handler) & 0xFFFF;
        IDT[interruptNumber].handlerHi = (((uint32_t)handler) >> 16) & 0xFFFF;
        IDT[interruptNumber].gdt_codeSegmentSelector = CodeSegment;
        IDT[interruptNumber].access = IDT_DESC_PRESENT | discriptorType | ((discriptorAccess&3) << 5);
        IDT[interruptNumber].reserved = 0;
    }

    interruptManager::interruptManager(GDT* gdt)
    : picMasterCommand(0x20),
    picMasterData(0x21),
    picWorkerCommand(0xA0),
    picWorkerData(0xA1)
    {
        uint16_t codeSegment = gdt->CodeSegmentSelector();
        const uint8_t IDT_INTERRUPT_GATE = 0xE;
        for (uint16_t i = 0; i < 256; i++){
            setIDTentry(i, codeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPT_GATE);
        }
    setIDTentry(0x20, codeSegment, &interruptManager::HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
    setIDTentry(0x21, codeSegment, &interruptManager::HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);

    picMasterCommand.write(0x11);
    picWorkerCommand.write(0x11);

    picMasterData.write(0x20);
    picWorkerData.write(0x28);

    picMasterCommand.write(0x04);
    picWorkerCommand.write(0x02);

    picMasterCommand.write(0x01);
    picWorkerCommand.write(0x01);

    picMasterCommand.write(0x00);
    picWorkerCommand.write(0x00);

    interruptManager::IDTpointer idt_pointer;
    idt_pointer.size = 265 * sizeof(interruptManager::gateDescriptor) - 1;
    idt_pointer.base = (uint32_t)&IDT;
    asm volatile("lidt %0" : : "m" (idt_pointer));
    }

    interruptManager::~interruptManager(){
        interruptManager::deactivate();
    }

    void interruptManager::activate(){
        asm("sti");
    }

    void interruptManager::deactivate(){

    }

uint32_t interruptManager::handle(uint8_t interruptNum, uint32_t esp){
print((char*)"interupt");
return esp;
}
