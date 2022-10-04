CROSS_COMPILE ?= riscv64-unknown-elf-
ARCH ?= riscv

CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump

CFLAGS += -Wall -Werror -ffreestanding
CFLAGS += -nostdlib -fno-common -g
CFLAGS += -mcmodel=medany
CFLAGS += -Isys/arch/$(ARCH)/include
CFLAGS += -Isys/include

kernel_asm_srcs :=
kernel_srcs :=
kernel_objs :=
kernel_elf := sys/lylaOS
linker_script := sys/arch/$(ARCH)/lylaOS.ld

QEMU := qemu-system-riscv64
QEMU_OPTS := -machine virt -nographic -kernel $(kernel_elf)

all:

include sys/module.mk
include usr/module.mk

kernel_objs += $(patsubst %.S, %.o, $(kernel_asm_srcs))
kernel_objs += $(patsubst %.c, %.o, $(kernel_srcs))

$(kernel_elf): $(kernel_objs)
	$(LD) $(LDFLAGS) -T$(linker_script) $^ -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

gen-compile-commands:
	mkdir -p .vscode
	$(MAKE) clean
	bear -- $(MAKE) all && mv compile_commands.json .vscode

qemu-gdb: all
	$(QEMU) $(QEMU_OPTS) -s -S

clean:
	$(RM) $(kernel_objs) $(kernel_elf)

all: $(kernel_elf)

.PHONY: all clean qemu-gdb gen-compile-commands
