.set IRQ_BASE, 0x20

.section .text

.extern _ZN16interruptManager6handleEhj

.macro HandleException num
.global _ZN16interruptManager19HandleException\num\()Ev
_ZN16interruptManager19HandleException\num\()Ev:
    movb $\num, (interruptNum)
    jmp int_bottom
.endm

.macro HandleInterruptRequest num
.global _ZN16interruptManager26HandleInterruptRequest\num\()Ev
_ZN16interruptManager26HandleInterruptRequest\num\()Ev:
    movb $\num + IRQ_BASE, (interruptNum)
    jmp int_bottom
.endm

HandleException 0x00
HandleException 0x01

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01

int_bottom:

  
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    #cld
    #mov $0x10, %eax
    #mov %eax, %eds
    #mov %eax, %ees

    pushl %esp
    push (interruptNum)
    call _ZN16interruptManager6handleEhj
    add %esp, 6
    mov %eax, %esp

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa

.global _ZN16interruptManager22IgnoreInterruptRequestEv
_ZN16interruptManager22IgnoreInterruptRequestEv:
    iret

.section .data
    interruptNum: .byte 0
