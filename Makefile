# The top level makefile of lylaOS

# Tool chain settings
ARCH := riscv
CROSS_COMPILE ?= riscv64-unknown-elf-
CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump
QEMU := qemu-system-riscv64
QEMU_OPTS = -machine virt -nographic -kernel $(kernel_img)

CFLAGS :=
CFLAGS += -Wall -Werror -ffreestanding
CFLAGS += -nostdlib -fno-common
CFLAGS += -mcmodel=medany

# Directories settings
BUILD_TYPE := Debug
BUILD_DIR := build
source_dir := $(realpath .)
build_dir := $(BUILD_DIR)

ifeq ($(BUILD_TYPE), Debug)
	CFLAGS += -g
endif

# Build outputs
kobjs :=
uobjs :=
dirs :=
d := $(source_dir)
dstack :=

kernel_linker_script := $(source_dir)/sys/arch/$(ARCH)/lylaOS.ld
kernel_img := $(source_dir)/sys/lylaOS

# Include subdirs
subdir := $(source_dir)/sys
include $(subdir)/module.mk

subdir := $(source_dir)/usr
include $(subdir)/module.mk

# Pattern rules
%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.S
	$(CC) -c $(CFLAGS) -o $@ $<

all: sys usr

sys: $(kobjs)
	$(LD) $(LDFLAGS) -T$(kernel_linker_script) -o $(kernel_img) $^

usr: $(uobjs)
	$(Q)echo Makefing target [$@]

qemu-gdb: all
	$(QEMU) $(QEMU_OPTS) -s -S

clean:
	$(RM) $(kobjs)

.PHONY: all sys usr clean