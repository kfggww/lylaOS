SYS_SRCS := $(wildcard sys/*.c)
SYS_SRCS += $(wildcard sys/arch/${ARCH}/*.c)
SYS_ASMS := $(wildcard sys/arch/${ARCH}/*.S)

SYS_OBJS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(SYS_SRCS))
SYS_OBJS += $(patsubst %.S, $(BUILD_DIR)/%.o, $(SYS_ASMS))

CFLAGS += -Isys/arch/$(ARCH) -nostdlib -ffreestanding

lylaOS: build_dir $(SYS_OBJS)
	$(Q)$(LD) $(SYS_OBJS) -eentry -o $(BUILD_DIR)/$@

$(BUILD_DIR)/%.o: %.c
	$(Q)$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.S
	$(Q)$(CC) -c $(CFLAGS) $< -o $@