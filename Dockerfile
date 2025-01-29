FROM ubuntu:22.04
WORKDIR /osdev

# Configure
SHELL ["/bin/sh"]
RUN ["apt-get", "update"]
RUN ["apt-get", "install", "-y", "gcc", "make", "nasm"]
RUN ["apt-get", "install", "-y", "xorriso", "mtools", "grub2-common", "grub-pc"]

# Copy files
COPY . ./

# Build
ENTRYPOINT [ "make", "iso" ]
