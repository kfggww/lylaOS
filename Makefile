CORSS_COMPILE ?= riscv64-unknown-elf-
ARCH ?= riscv

CC := $(CORSS_COMPILE)gcc
LD := $(CORSS_COMPILE)ld

BUILD_DIR ?= build
BUILD_TYPE ?= Debug
Q := 

KERNEL_IMG := $(BUILD_DIR)/lylaOS
QEMU := qemu-system-riscv64
QEMU_OPTIONS := -M virt -kernel $(KERNEL_IMG) -nographic -s -S

CFLAGS += -mcmodel=medany
ifeq ($(BUILD_TYPE), Debug)
CFLAGS += -g
endif

build_dir:
	$(Q)mkdir -p $(BUILD_DIR)/sys/arch/$(ARCH)
	$(Q)mkdir -p $(BUILD_DIR)/usr

clean:
	$(Q)-rm -rf $(BUILD_DIR)/*

qemu-debug: lylaOS
	$(Q)$(QEMU) $(QEMU_OPTIONS)

.PHONY: build_dir clean

include sys/sys.mk
include usr/usr.mk