
ARMGNU ?= arm-none-eabi

AOPS = --warn --fatal-warnings
COPS = -std=c99 -Wall -Werror -Wextra -Wuninitialized -O2 -nostdlib -nostartfiles -ffreestanding -march=armv6z
CFLAGS=-I./include
#CFILES :=  $(filter-out src/kernel.c, $(wildcard src/*.c))
CFILES :=  $(wildcard src/*.c)
OBJ_FILES := $(addprefix obj/,$(notdir $(CFILES:.c=.o)))
DEBUGFLAG = 


#CFILES_TESTS := $(wildcard tests/src/*.c)
#OBJ_FILES_TESTS := $(addprefix tests/obj/,$(notdir $(CFILES_TESTS:.c=.o)))

#debug variable: $(info $$CFILES is [${CFILES}])

gcc : kernel.img kernel.hex kernel.s

all : gcc bootfiles

clean :
	rm -f *.o
	rm -f *.img
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc
	rm -f kernel.s
	rm -f kernel.hex
	rm -f boot/kernel.img
	rm -f obj/*.*
	rm -f tests/obj/*.*


###############
# Kernel part #
###############

kernel_main.o: linker_map.o $(OBJ_FILES)
	$(ARMGNU)-gcc $(COPS) $(CFLAGS) $(DEBUGFLAG) -r -o obj/$@ $(OBJ_FILES)

obj/%.o: src/%.c
	$(ARMGNU)-gcc $(COPS) $(CFLAGS) $(DEBUGFLAG) -o $@ -c $<

linker_map.o : linker_map.s
	$(ARMGNU)-as linker_map.s -o obj/linker_map.o


kernel.elf : memory_map.d linker_map.o kernel_main.o
	$(ARMGNU)-ld obj/linker_map.o obj/kernel_main.o -T memory_map.d -o kernel.elf

kernel.img : kernel.elf
	$(ARMGNU)-objcopy kernel.elf -O binary boot/kernel.img

kernel.hex : kernel.elf
	$(ARMGNU)-objcopy kernel.elf -O ihex kernel.hex

kernel.s : src/kernel.c
	$(ARMGNU)-gcc $(CFLAGS) -S -o kernel.s src/kernel.c

bootfiles:
	curl -o boot/LICENCE.broadcom https://github.com/raspberrypi/firmware/blob/master/boot/LICENCE.broadcom?raw=true
	curl -o boot/bootcode.bin https://github.com/raspberrypi/firmware/blob/master/boot/bootcode.bin?raw=true
	curl -o boot/fixup.dat https://github.com/raspberrypi/firmware/blob/master/boot/fixup.dat?raw=true
	curl -o boot/start.elf https://github.com/raspberrypi/firmware/blob/master/boot/start.elf?raw=true

deploy:
	@cp boot/kernel.img /Volumes/RECOVERY/
	@shasum boot/kernel.img
	@shasum /Volumes/RECOVERY/kernel.img
	@diskutil unmountDisk /dev/disk2

connect:
	@rm -f screenlog.0
	@screen -L /dev/tty.usbserial 115200
	@reset


################
# Testing part #
################
.PHONY: tests
tests:
	cp include/*.h tests/src
	cp src/*.c tests/src
	gcc -DTEST tests/src/malloc.c tests/src/malloc_test.c tests/src/base_test.c -o tests/obj/malloc_test.o
	gcc -DTEST tests/src/strings.c tests/src/malloc.c tests/src/strings_test.c tests/src/base_test.c -o tests/obj/strings_test.o
	gcc -DTEST tests/src/queue.c tests/src/malloc.c tests/src/queue_test.c tests/src/base_test.c -o tests/obj/queue_test.o

run_tests:
	@./tests/obj/malloc_test.o
	@./tests/obj/strings_test.o
	@./tests/obj/queue_test.o
