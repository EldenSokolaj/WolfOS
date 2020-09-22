main:
	echo "clean, compile, run, start"
clean:
	rm *.o
	rm kernel
compile:
	nasm -f elf32 loader.s -o kasm.o
	g++ -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -c kernel.cpp -o kc.o
	ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o
run:
	qemu-system-i386 -kernel kernel
start:
	nasm -f elf32 loader.s -o kasm.o
	clear
	g++ -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -c kernel.cpp -o kc.o
	clear
	ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o
	clear
	qemu-system-i386 -kernel kernel
	clear
	rm *.o
	rm kernel
	clear