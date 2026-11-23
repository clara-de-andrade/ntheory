SHELL   := /bin/sh

CC      ?= gcc
AR      ?= ar
CFLAGS  := -Wall -Wextra -O2
LDLIBS  := -lgmp

INC_DIR := include
SRC_DIR := source

ifeq ($(OS),Windows_NT)
    BUILD_DIR := build/windows
else
    BUILD_DIR := build/linux
endif

TARGET  := $(BUILD_DIR)/ntheory.a

rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SRCS    := $(call rwildcard,$(SRC_DIR),*.c)
OBJS    := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS    := $(OBJS:.o=.d)

.PHONY: all clean clean-all

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -MMD -MP -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

clean-all:
	rm -rf build

-include $(DEPS)