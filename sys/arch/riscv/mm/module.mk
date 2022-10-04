local_srcs := pm.c \
	vm.c
local_srcs := $(addprefix sys/arch/riscv/mm/, $(local_srcs))
local_objs := $(patsubst %.c, %.o, $(local_srcs))
kernel_objs += $(local_objs)