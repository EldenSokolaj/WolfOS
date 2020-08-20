;;kernel.asm
bits 32			;nasm directive - 32 bit
section .text

;multiboot spec
    align 4
    dd 0x1BADB002            ;magic
    dd 0x00                  ;flags
    dd - (0x1BADB002 + 0x00) ;checksum. m+f+c should be zero

global start
extern kmain
extern callConstructors

start:
  cli
  mov esp, stack_space
  
  call callConstructors
  
  call kmain
  hlt

section .bss
resb 8192		;8KB for stack
stack_space: