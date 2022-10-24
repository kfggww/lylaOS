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

$(kobjs): KBOJS_INC_COMMON := $(d)/include
$(kobjs): CFLAGS += $(KBOJS_INC_COMMON)