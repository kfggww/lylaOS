local_asm_srcs := entry.S \
				kernelvec.S \
				uservec.S
local_asm_srcs := $(addprefix sys/arch/riscv/boot/, $(local_asm_srcs))

local_srcs := trap.c
local_srcs := $(addprefix sys/arch/riscv/boot/, $(local_srcs))

kernel_asm_srcs += $(local_asm_srcs)
kernel_srcs += $(local_srcs)