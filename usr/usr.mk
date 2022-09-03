
USR_SRCS := $(wildcard usr/*.c)
USR_OBJS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(USR_SRCS))

initcode: usr/init.c
	$(Q)$(CC) $< -o $(BUILD_DIR)/usr/init -nostdlib -emain -Ttext 0x10000000