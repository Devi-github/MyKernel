FROM ubuntu:22.04
WORKDIR /osdev

# Configure

COPY . ./
# RUN ./configure
SHELL ["/bin/sh"]
RUN ["apt-get", "update"]
RUN ["apt-get", "install", "-y", "gcc", "make", "nasm"]
RUN ["apt-get", "install", "-y", "xorriso", "mtools", "grub2-common", "grub-pc"]

# Build
ENTRYPOINT [ "make", "iso" ]
