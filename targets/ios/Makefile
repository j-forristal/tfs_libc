
LIBNOM := libtfs_libc
TARGET := ios
BUILD_DIR = build/
ARCH ?= host

##############################################

INCS := \
	-Isrc/ \
	-Isrc/ios/

ASM_SRC :=

ifeq ($(ARCH),armv7)
ASM_SRC += src/ios/sys.arm.s
endif
ifeq ($(ARCH),armv7s)
ASM_SRC += src/ios/sys.arm.s
endif

ifeq ($(ARCH),arm64)
ASM_SRC += src/ios/sys.arm64.s
endif

C_SRC := \
	src/memcpy.c \
	src/memcmp.c \
	src/memset.c \
	src/strlen.c \
	src/strstr.c \
	src/itoa.c \
	src/atoi.c \
	src/ios/helpers.c 
	
OBJ_DIR = $(BUILD_DIR)/obj_$(ARCH)/
ASM_OBJ := $(ASM_SRC:%.s=$(OBJ_DIR)/%.o)
C_OBJ := $(C_SRC:%.c=$(OBJ_DIR)/%.o)

HEADERS := src/platform.libc.h

##############################################

DEFS := -DNDEBUG=1

CFLAGS += -Wall -Werror -fPIC -O3 $(INCS) $(DEFS) -fno-exceptions \
	-ffast-math -fno-unwind-tables -fvisibility=hidden \
	-fno-asynchronous-unwind-tables
#	-fomit-frame-pointer \

LDFLAGS += -arch $(ARCH)

##############################################

.PHONY: default build clean link title

default: title build 

title:
	@echo ------ arch $(ARCH) ---------

build: $(LIBNOM)_$(ARCH).a
	@mkdir -p $(BUILD_DIR)/include/
	@cp $(HEADERS) $(BUILD_DIR)/include/
	@echo '' >> $(BUILD_DIR)/build.environment
	@echo $(LIBNOM)_$(ARCH) >> $(BUILD_DIR)/build.environment
	@$(CC) $(CFLAGS) --version >> $(BUILD_DIR)/build.environment
	@echo $(CFLAGS) >> $(BUILD_DIR)/build.environment

$(ASM_OBJ): $(OBJ_DIR)/%.o: %.s
	@mkdir -p $(@D)
	@echo - CC $<
	@$(CC) $(CFLAGS) -c -o $@ $<

$(C_OBJ): $(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo - CC $<
	@$(CC) $(CFLAGS) -c -o $@ $<

$(LIBNOM)_$(ARCH).a: $(C_OBJ) $(ASM_OBJ)
	@mkdir -p $(BUILD_DIR)/lib/
	@$(LD) $(LDFLAGS) -r -bitcode_bundle $(EXTOBJ) $(C_OBJ) $(ASM_OBJ) -o $(BUILD_DIR)/lib/$@.o
	@$(AR) rcs $(BUILD_DIR)/lib/$@ $(BUILD_DIR)/lib/$@.o
	@strip -x $(BUILD_DIR)/lib/$@

link: $(LIBNOM)_$(ARCH).a
	@$(CC) $(CFLAGS) -framework Foundation -framework Security -o $(BUILD_DIR)/test_link src/test_link.c $(BUILD_DIR)/lib/$(LIBNOM)_$(ARCH).a

clean:
	rm -rf $(BUILD_DIR)/
