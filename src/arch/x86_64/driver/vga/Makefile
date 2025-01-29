driver = $(driver_build_dir)/vga.o
c_files = vga.c

$(driver): $(c_files) vga.h
	@mkdir -p $(driver_build_dir)
	$(CC) $(C_FLAGS) -c $(c_files) -o $(driver)
