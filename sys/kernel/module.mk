local_srcs := kernel.c
local_srcs := $(addprefix sys/kernel/, $(local_srcs))
local_objs := $(patsubst %.c, %.o, $(local_srcs))

kernel_objs += $(local_objs)