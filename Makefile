# The top level makefile of lylaOS

# Tool chain settings
ARCH := riscv
CROSS_COMPILE ?= riscv64-unknown-elf-
CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump

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

# Include subdirs
subdir := $(source_dir)/sys
include $(subdir)/module.mk

subdir := $(source_dir)/usr
include $(subdir)/module.mk

all: $(kobjs) $(uobjs)
	@echo $(source_dir) $(build_dir)

.PHONY: all