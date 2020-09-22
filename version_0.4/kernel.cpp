/* #include "lib/io.h" */
/* #include "lib/system.h" */
#include "lib/types.h"
#include "lib/gdt.h"
#include "lib/idt.h"
#include "lib/logo.h"

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void callConstructors(){
    for (constructor* i = &start_ctors; i != &end_ctors; i++){
        (*i)();
    }
}

extern "C" void kmain(const void* multiboot_structure){
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    /* DEVIDE BY ZERO MAKES IT CRASH | MIGHT BE AN IDT ERROR :( */
    logo();
    return;
}
