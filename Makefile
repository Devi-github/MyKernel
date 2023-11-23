CXX := gcc
ASMC := nasm
LDXX := ld

arch ?= x86_64
kernel := build/kernel-$(arch).bin
iso := build/os-$(arch).iso

C_FLAGS := -ggdb -m64 -ffreestanding -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -nostdlib
ASM_FLAGS := -felf64
LINK_FLAGS := -n -T

linker_script := src/arch/$(arch)/linker.ld
grub_cfg := src/arch/$(arch)/grub.cfg
assembly_source_files := $(wildcard src/arch/$(arch)/*.s)
assembly_object_files := $(patsubst src/arch/$(arch)/%.s, \
	build/arch/$(arch)/%.o, $(assembly_source_files))

h_files := $(wildcard src/arch/$(arch)/*.h)

c_source_files := $(wildcard src/arch/$(arch)/*.c)
c_object_files := $(patsubst src/arch/$(arch)/%.c, \
	build/arch/$(arch)/%.o, $(c_source_files))

.PHONY: all build rebuild clean run iso check

all: check

objdump: $(kernel)
	@objdump -S $(kernel)

clean:
	@rm -r build

run: $(iso)
	@qemu-system-x86_64 -cdrom $(iso)

rebuild: clean build

build: $(iso)

check: build
	@file $(iso)

iso: $(iso)

$(iso): $(kernel) $(grub_cfg)
	@mkdir -p build/isofiles/boot/grub
	@cp $(kernel) build/isofiles/boot/kernel.bin
	@cp $(grub_cfg) build/isofiles/boot/grub
	@grub-mkrescue -o $(iso) build/isofiles
	@rm -r build/isofiles

$(kernel): $(assembly_object_files) $(c_object_files) $(linker_script)
	@$(LDXX) $(LINK_FLAGS) $(linker_script) -o $(kernel) $(c_object_files) $(assembly_object_files)

# compile c files
build/arch/$(arch)/%.o: src/arch/$(arch)/%.c $(h_files)
	@mkdir -p $(shell dirname $@)
	@$(CXX) $(C_FLAGS) -c $< -o $@

# compile assembly files
build/arch/$(arch)/%.o: src/arch/$(arch)/%.s
	@mkdir -p $(shell dirname $@)
#	@gcc -c $< -o $@
	@$(ASMC) $(ASM_FLAGS) $< -o $@
	