#include "types.h"
#include "system.h"
#include "io.h"

struct idt_entry{
    uint16 base_lo;
    uint16 sel;
    uint8 always0;
    uint8 flags;
    uint16 base_hi;
}__attribute__((packed));

struct idt_ptr{
    uint16 limit;
    uint32 base;
}__attribute__((packed));

/* Declare an IDT of 256 entries. or risk "Unhandled Interrupt" exception */
struct idt_entry idt[256];
struct idt_ptr idtp;

/* load the IDT */
void idt_load(){
    asm volatile("lidt %0" : : "m" (idtp));
}

/* Use this function to set an entry in the IDT. A lot simpler than twiddling with the GDT ;) */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags){
    /* The interrupt routine's base address */
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    /* The segment or 'selector' that this IDT entry will use is set here, along with any access flags */
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

/* Installs the IDT */
void idt_install(){
    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = (uint32)&idt;

    /* Clear out the entire IDT, initializing it to zeros */
    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    /* Add any new ISRs to the IDT here using idt_set_gate */

    /* Points the processor's internal register to the new IDT */
    idt_load();
}

extern "C" void _isr0();
extern "C" void _isr1();
extern "C" void _isr2();
extern "C" void _isr3();
extern "C" void _isr4();
extern "C" void _isr5();
extern "C" void _isr6();
extern "C" void _isr7();
extern "C" void _isr8();
extern "C" void _isr9();
extern "C" void _isr10();
extern "C" void _isr11();
extern "C" void _isr12();
extern "C" void _isr13();
extern "C" void _isr14();
extern "C" void _isr15();
extern "C" void _isr16();
extern "C" void _isr17();
extern "C" void _isr18();
extern "C" void _isr19();
extern "C" void _isr20();
extern "C" void _isr21();
extern "C" void _isr22();
extern "C" void _isr23();
extern "C" void _isr24();
extern "C" void _isr25();
extern "C" void _isr26();
extern "C" void _isr27();
extern "C" void _isr28();
extern "C" void _isr29();
extern "C" void _isr30();
extern "C" void _isr31();

/* This is a very repetitive function... it's not hard, it's
*  just annoying. As you can see, we set the first 32 entries
*  in the IDT to the first 32 ISRs. We can't use a for loop
*  for this, because there is no way to get the function names
*  that correspond to that given entry. We set the access
*  flags to 0x8E. This means that the entry is present, is
*  running in ring 0 (kernel level), and has the lower 5 bits
*  set to the required '14', which is represented by 'E' in
*  hex. */
void isrs_install(){
    idt_set_gate(0, (unsigned)_isr0, 0x08, 0x8E);
    idt_set_gate(1, (unsigned)_isr1, 0x08, 0x8E);
    idt_set_gate(2, (unsigned)_isr2, 0x08, 0x8E);
    idt_set_gate(3, (unsigned)_isr3, 0x08, 0x8E);
    idt_set_gate(4, (unsigned)_isr4, 0x08, 0x8E);
    idt_set_gate(5, (unsigned)_isr5, 0x08, 0x8E);
    idt_set_gate(6, (unsigned)_isr6, 0x08, 0x8E);
    idt_set_gate(7, (unsigned)_isr7, 0x08, 0x8E);

    idt_set_gate(8, (unsigned)_isr8, 0x08, 0x8E);
    idt_set_gate(9, (unsigned)_isr9, 0x08, 0x8E);
    idt_set_gate(10, (unsigned)_isr10, 0x08, 0x8E);
    idt_set_gate(11, (unsigned)_isr11, 0x08, 0x8E);
    idt_set_gate(12, (unsigned)_isr12, 0x08, 0x8E);
    idt_set_gate(13, (unsigned)_isr13, 0x08, 0x8E);
    idt_set_gate(14, (unsigned)_isr14, 0x08, 0x8E);
    idt_set_gate(15, (unsigned)_isr15, 0x08, 0x8E);

    idt_set_gate(16, (unsigned)_isr16, 0x08, 0x8E);
    idt_set_gate(17, (unsigned)_isr17, 0x08, 0x8E);
    idt_set_gate(18, (unsigned)_isr18, 0x08, 0x8E);
    idt_set_gate(19, (unsigned)_isr19, 0x08, 0x8E);
    idt_set_gate(20, (unsigned)_isr20, 0x08, 0x8E);
    idt_set_gate(21, (unsigned)_isr21, 0x08, 0x8E);
    idt_set_gate(22, (unsigned)_isr22, 0x08, 0x8E);
    idt_set_gate(23, (unsigned)_isr23, 0x08, 0x8E);

    idt_set_gate(24, (unsigned)_isr24, 0x08, 0x8E);
    idt_set_gate(25, (unsigned)_isr25, 0x08, 0x8E);
    idt_set_gate(26, (unsigned)_isr26, 0x08, 0x8E);
    idt_set_gate(27, (unsigned)_isr27, 0x08, 0x8E);
    idt_set_gate(28, (unsigned)_isr28, 0x08, 0x8E);
    idt_set_gate(29, (unsigned)_isr29, 0x08, 0x8E);
    idt_set_gate(30, (unsigned)_isr30, 0x08, 0x8E);
    idt_set_gate(31, (unsigned)_isr31, 0x08, 0x8E);

    for (int i = 32; i < 256; i++){
        idt_set_gate(i, (unsigned)_isr31, 0x08, 0x8E);
    }
}

/* This is a simple string array. It contains the message that
*  corresponds to each and every exception. We get the correct
*  message by accessing like:
*  exception_message[interrupt_number] */
const char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

/* All of our Exception handling Interrupt Service Routines will
*  point to this function. This will tell us what exception has
*  happened! Right now, we simply halt the system by hitting an
*  endless loop. All ISRs disable interrupts while they are being
*  serviced as a 'locking' mechanism to prevent an IRQ from
*  happening and messing up kernel data structures */
extern "C" void _fault_handler(struct regs *r){
    if (r->int_no < 32){
        print((char*)exception_messages[r->int_no]);
        print("Exception. System Halted!\n");
        for (;;);
    }
    for(;;);
}

/* These are own ISRs that point to our special IRQ handler
*  instead of the regular 'fault_handler' function */
extern "C" void _irq0();
extern "C" void _irq1();
extern "C" void _irq2();
extern "C" void _irq3();
extern "C" void _irq4();
extern "C" void _irq5();
extern "C" void _irq6();
extern "C" void _irq7();
extern "C" void _irq8();
extern "C" void _irq9();
extern "C" void _irq10();
extern "C" void _irq11();
extern "C" void _irq12();
extern "C" void _irq13();
extern "C" void _irq14();
extern "C" void _irq15();

/* This array is actually an array of function pointers. We use
*  this to handle custom IRQ handlers for a given IRQ */
void *irq_routines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

/* This installs a custom IRQ handler for the given IRQ */
void irq_install_handler(int irq, void (*handler)(struct regs *r)){
    //irq_routines[irq] = handler;
}

/* This clears the handler for a given IRQ */
void irq_uninstall_handler(int irq){
    irq_routines[irq] = 0;
}

/* Normally, IRQs 0 to 7 are mapped to entries 8 to 15. This
*  is a problem in protected mode, because IDT entry 8 is a
*  Double Fault! Without remapping, every time IRQ0 fires,
*  you get a Double Fault Exception, which is NOT actually
*  what's happening. We send commands to the Programmable
*  Interrupt Controller (PICs - also called the 8259's) in
*  order to make IRQ0 to 15 be remapped to IDT entries 32 to
*  47 */
void irq_remap(){
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}

/* We first remap the interrupt controllers, and then we install
*  the appropriate ISRs to the correct entries in the IDT. This
*  is just like installing the exception handlers */
void irq_install(){
    irq_remap();

    idt_set_gate(32, (unsigned)_irq0, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)_irq1, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)_irq2, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)_irq3, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)_irq4, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)_irq5, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)_irq6, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)_irq7, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)_irq8, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)_irq9, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)_irq10, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)_irq11, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)_irq12, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)_irq13, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)_irq14, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)_irq15, 0x08, 0x8E);
}

/* Each of the IRQ ISRs point to this function, rather than
*  the 'fault_handler' in 'isrs.c'. The IRQ Controllers need
*  to be told when you are done servicing them, so you need
*  to send them an "End of Interrupt" command (0x20). There
*  are two 8259 chips: The first exists at 0x20, the second
*  exists at 0xA0. If the second controller (an IRQ from 8 to
*  15) gets an interrupt, you need to acknowledge the
*  interrupt at BOTH controllers, otherwise, you only send
*  an EOI command to the first controller. If you don't send
*  an EOI, you won't raise any more IRQs */
extern "C" void _irq_handler(struct regs *r){
    /* 
    IMPORT TO NOTE THAT THIS DOESN'T WORK AS IT SHOULD
    //This is a blank function pointer
    void (*handler)(struct regs *r);

    //Find out if we have a custom handler to run for this IRQ, and then finally, run it
    handler = irq_routines[r->int_no - 32];
    if (handler){
        handler(r);
    }
    */

    /* If the IDT entry that was invoked was greater than 40
    *  (meaning IRQ8 - 15), then we need to send an EOI to
    *  the slave controller */
    if (r->int_no >= 40){
        outportb(0xA0, 0x20);
    }
    /* In either case, we need to send an EOI to the master
    *  interrupt controller too */
    outportb(0x20, 0x20);
}