main:
	echo "clean, compile, run"
clean:
	rm *.o
	rm kernel
compile:
	nasm -f elf32 kernel.asm -o kasm.o
	gcc -m32 -c kernel.c -o kc.o
	ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o
run:
	qemu-system-i386 -kernel kernel
all:
	rm *.o
	rm kernel
	nasm -f elf32 kernel.asm -o kasm.o
	gcc -m32 -c kernel.c -o kc.o
	ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o
	qemu-system-i386 -kernel kernel
