#include "types.h"

struct regs{
    uint32 gs, fs, es, ds;      /* pushed the segs last */
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    uint32 int_no, err_code;    /* our 'push byte #' and ecodes do this */
    uint32 eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

void *memcpy(void *dest, const void *src, uint16 count){
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, int8 val, uint16 count){
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(uint16 *dest, uint16 val, uint16 count){
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

uint16 strlen(const char *str){
    uint16 retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

uint8 inportb (uint16 _port){
    unsigned char rv;
    asm volatile ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (uint16 _port, uint8 _data){
    asm volatile ("outb %1, %0" : : "dN" (_port), "a" (_data));
}