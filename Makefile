CC := gcc
ASMC := nasm
LD := ld
MAKE ?= make
GRUB_MKRESCUE ?= grub-mkrescue

arch ?= x86_64
build_dir = $(shell pwd)/build/arch/$(arch)
source_dir = $(shell pwd)/src/arch/$(arch)
driver_build_dir = $(build_dir)/driver

kernel := $(build_dir)/kernel-$(arch).bin
iso := $(build_dir)/os-$(arch).iso

C_FLAGS := -ggdb -m64 -ffreestanding -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -nostdlib -I$(source_dir)/libc
ASM_FLAGS := -felf64
LINK_FLAGS := -n -T

linker_script := $(source_dir)/linker.ld
grub_cfg := $(source_dir)/grub.cfg
assembly_source_files := $(wildcard $(source_dir)/**/*.s)
assembly_object_files := $(patsubst $(source_dir)/%.s, \
	$(build_dir)/%.o, $(assembly_source_files))

enabled_drivers = vga
driver_obj_files = $(patsubst %,$(driver_build_dir)/%.o,$(enabled_drivers))

c_source_files := $(wildcard $(source_dir)/**/*.c)
c_object_files := $(patsubst $(source_dir)/%.c, \
	$(build_dir)/%.o, $(c_source_files))

export

.PHONY: all build rebuild clean run iso check drivers .FORCE

all: check

objdump: $(kernel)
	@objdump -S $(kernel)

clean:
	rm -r build

run: $(iso)
	qemu-system-x86_64 -cdrom $(iso)

rebuild: clean build

build: $(iso)

check: build
	file $(iso)

iso: $(iso)

.FORCE:
drivers: $(driver_obj_files)
# Build all drivers with makefile

$(driver_obj_files): $(driver_build_dir) .FORCE
	$(MAKE) -C $(source_dir)/driver

$(driver_build_dir):
	mkdir -p $(driver_build_dir)

$(iso): $(kernel) $(grub_cfg)
	mkdir -p build/isofiles/boot/grub
	cp $(kernel) build/isofiles/boot/kernel.bin
	cp $(grub_cfg) build/isofiles/boot/grub
	$(GRUB_MKRESCUE) -o $(iso) build/isofiles
	rm -r build/isofiles

$(kernel): $(assembly_object_files) $(c_object_files) $(linker_script) drivers
	$(LD) $(LINK_FLAGS) $(linker_script) -o $(kernel) $(c_object_files) $(driver_obj_files) $(assembly_object_files)

# compile c files
$(build_dir)/%.o: $(source_dir)/%.c $(c_source_files)
	@mkdir -p $(shell dirname $@)
	$(CC) $(C_FLAGS) -c $< -o $@

# compile assembly files
$(build_dir)/%.o: $(source_dir)/%.s $(assembly_source_files)
	@mkdir -p $(shell dirname $@)
	$(ASMC) $(ASM_FLAGS) $< -o $@
