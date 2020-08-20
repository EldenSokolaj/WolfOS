#include "lib/all.h"

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void callConstructors(){
    for (constructor* i = &start_ctors; i != &end_ctors; i++){
        (*i)();
    }
}

extern "C" void kmain(const void* multiboot_structure){
    GDT gdt;
    interruptManager interrupts(&gdt);
    interrupts.activate();
    logo();
    return;
}
