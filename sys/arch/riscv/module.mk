d := $(subdir)

subdir := $(d)/boot
include $(subdir)/module.mk

subdir := $(d)/mm
include $(subdir)/module.mk