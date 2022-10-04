local_srcs := main.c
local_srcs := $(addprefix sys/init/, $(local_srcs))

kernel_srcs += $(local_srcs)