dstack += $(d)
d := $(subdir)

srcs_$(d) := $(wildcard $(d)/*.c)
asms_$(d) := $(wildcard $(d)/*.S)

objs_$(d) := $(srcs_$(d):%.c=%.o) $(asms_$(d):%.S=%.o)
kobjs += $(objs_$(d))

d := $(lastword $(dstack))
dstack := $(filter-out $(d), $(dstack))