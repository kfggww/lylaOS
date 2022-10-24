dstack += $(d)
d := $(subdir)

subdir := $(d)/arch/$(ARCH)
include $(subdir)/module.mk

subdir := $(d)/drivers
include $(subdir)/module.mk

subdir := $(d)/fs
include $(subdir)/module.mk

subdir := $(d)/init
include $(subdir)/module.mk

subdir := $(d)/kernel
include $(subdir)/module.mk

subdir := $(d)/lib
include $(subdir)/module.mk

subdir := $(d)/mm
include $(subdir)/module.mk

arch_inc := $(d)/arch/$(ARCH)/include
lyla_inc := $(d)/include
$(kobjs): CFLAGS += -I$(lyla_inc) -I$(arch_inc)

d := $(lastword $(dstack))
dstack := $(filter-out $(d), $(dstack))