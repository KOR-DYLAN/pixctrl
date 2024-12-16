TOPDIR			:=$(dir $(abspath $(firstword $(MAKEFILE_LIST))))
NPROC			:=$(shell nproc)
CMAKE 			:=cmake
TOOLCHAIN_FILE 	:=toolchain/gnu.toolchain.cmake
BUILD_DIR		:=build
OUTPUT_DIR		:=output
SOURCE_DIR		:=$(TOPDIR)
V				?=0

# empty(x86_64: default) | aarch64-none-linux-gnu- | aarch64-none-elf-
# CROSS_COMPILE	:=aarch64-none-linux-gnu-

# Debug | MinSizeRel | Release | RelWithDebInfo 
BUILD_TYPE		:=Debug

# sanitize( OFF | ON | TRAP )
ENABLE_SANTINIZE	?=OFF
SANTINIZE			?=leak,undefined,address

all: build

phony+=config
config:
	$(CMAKE) -DCMAKE_VERBOSE_MAKEFILE=$(V) -DCROSS_COMPILE=$(CROSS_COMPILE) -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN_FILE) \
			 -DCMAKE_BUILD_TYPE:STRING=$(BUILD_TYPE) -DENABLE_SANTINIZE=$(ENABLE_SANTINIZE) -DSANTINIZE=$(SANTINIZE) \
			 -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
			 -S$(SOURCE_DIR) -B$(BUILD_DIR)

phony+=build
build:
	$(CMAKE) --build $(BUILD_DIR) -j $(NPROC)

phony+=clean
clean:
	rm -rf $(RESULT_DIR)
	rm -rf $(OUTPUT_DIR)
	rm -rf $(BUILD_DIR)

.PHONY: $(phony)
