#include "lib/io.h"
#include "lib/logo.h"
//#include "lib/gdt.h"
#include "lib/interrupts.h"

extern "C" void kmain(const void* multiboot_structure){
    GDT gdt;
    interruptManager interrupts(&gdt);
    interrupts.activate();
    logo();
    return;
}
