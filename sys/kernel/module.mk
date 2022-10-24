dstack += $(d)
d := $(subdir)

srcs_$(d) := $(wildcard $(d)/*.c)
objs_$(d) := $(srcs_$(d):%.c=%.o)
kobjs += $(objs_$(d))

d := $(lastword $(dstack))
dstack := $(filter-out $(d), $(dstack))