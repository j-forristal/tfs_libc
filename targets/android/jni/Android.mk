LOCAL_PATH := $(call my-dir)

TARGET := android

###########################################

include $(CLEAR_VARS)

LOCAL_MODULE := tfs_libc

CFLAGS += -Wall -Werror -fPIC -O3 -fno-exceptions \
        -ffast-math -fno-unwind-tables -fvisibility=hidden \
        -fomit-frame-pointer -finline-limit=64 \
        -fno-asynchronous-unwind-tables

SRC += \
	src/memcmp.c \
	src/memcpy.c \
	src/memset.c \
	src/strlen.c \
	src/strstr.c \
	src/itoa.c \
	src/atoi.c \
	src/android/helpers.c \
	src/android/sys.$(TARGET_ARCH).S

LOCAL_CFLAGS += $(CFLAGS) 
LOCAL_SRC_FILES := $(SRC)

include $(BUILD_STATIC_LIBRARY)

