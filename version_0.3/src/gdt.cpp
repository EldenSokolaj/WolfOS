#include "../lib/gdt.h"

GDT::GDT(){
    setEntry(0, 0, 0, null);
    setEntry(0, 0, 0, unused);
    setEntry(0, 64*1024*1024, 0x9A, code);
    setEntry(0, 64*1024*1024, 0x92, data);
    gdtPtr i;
    i.limit = 4 * sizeof(entry);
    i.base = (uint32_t)&gdt;
    asm volatile("lgdt (%0)": :"p" (((uint8_t *) &i)+2));
}

GDT::~GDT(){}

uint32_t GDT::CodeSegmentSelector(){
    return (uint32_t) &gdt[code];
}

uint32_t GDT::DataSegmentSelector(){
    return (uint32_t) &gdt[data];
}

int GDT::setEntry(uint32_t base, uint32_t limit, uint8_t type, gdtSegment targetSegment){
    uint8_t *target = (uint8_t*)&gdt[targetSegment];

    if (limit <= 65536){
        target[6] = 0x40;
    } else {
        if ((limit & 0xFFF) != 0xFFF){
            limit = (limit >> 12)-1;
        } else {
            limit = limit >> 12;
        }
        target[6] = 0xC0;
    }

    target[0] = limit & 0xFF;
    target[1] = (limit >> 8) & 0xFF;
    target[6] |= (limit >> 16) & 0xF;

    target[2] = base & 0xFF;
    target[3] = (base >> 8) & 0xFF;
    target[4] = (base >> 16) & 0xFF;
    target[7] = (base >> 24) & 0xFF;

    target[5] = type;
}

uint32_t GDT::Base(gdtSegment targetSegment){
    uint8_t* target = (uint8_t*)&gdt[targetSegment];

    uint32_t result = target[7];
    result = (result << 8) + target[4];
    result = (result << 8) + target[3];
    result = (result << 8) + target[2];

    return result;
}

uint32_t GDT::Limit(gdtSegment targetSegment){
    uint8_t* target = (uint8_t*)&gdt[targetSegment];

    uint32_t result = target[6] & 0xF;
    result = (result << 8) + target[1];
    result = (result << 8) + target[0];

    if((target[6] & 0xC0) == 0xC0){
        result = (result << 12) | 0xFFF;
    }

    return result;
}
