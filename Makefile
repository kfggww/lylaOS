CORSS_COMPILE ?= riscv64-unknown-elf-
ARCH ?= riscv

CC := $(CORSS_COMPILE)gcc
LD := $(CORSS_COMPILE)ld

BUILD_DIR ?= build
Q := @

build_dir:
	$(Q)mkdir -p $(BUILD_DIR)/sys/arch/$(ARCH)
	$(Q)mkdir -p $(BUILD_DIR)/usr

clean:
	$(Q)-rm -rf $(BUILD_DIR)/*

.PHONY: build_dir clean

include sys/sys.mk
include usr/usr.mk