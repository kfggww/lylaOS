d := $(subdir)

srcs_$(d) := $(wildcard $(d)/*.c)
objs_$(d) := $(srcs_$(d):%.o=%.c)
kobjs += $(objs_$(d))