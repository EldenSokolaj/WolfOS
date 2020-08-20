main:
	echo "clean, compile, run, start"
clean:
	rm *.o
	rm kernel
compile:
	nasm -f elf32 loader.s -o kasm.o
	as --32 -o interruptstubs.o ./src/interruptstubs.s
	g++ -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -c kernel.cpp -o kc.o
	g++ -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -c ./src/gdt.cpp -o gdt.o
	g++ -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -c ./src/port.cpp -o port.o
	g++ -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -c ./src/interrupts.cpp -o interrupts.o
	ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o gdt.o port.o interrupts.o interruptstubs.o
run:
	qemu-system-i386 -kernel kernel
start:
	nasm -f elf32 loader.s -o kasm.o
	clear
	as --32 -o interruptstubs.o ./src/interruptstubs.s
	clear
	g++ -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -c ./src/gdt.cpp -o gdt.o
	clear
	g++ -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -c kernel.cpp -o kc.o
	clear
	g++ -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -c ./src/port.cpp -o port.o
	clear
	g++ -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -c ./src/interrupts.cpp -o interrupts.o
	clear
	ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o gdt.o port.o interrupts.o interruptstubs.o
	clear
	qemu-system-i386 -kernel kernel
	clear
	rm *.o
	rm kernel
	clear