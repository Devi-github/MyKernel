FROM ubuntu:22.04
WORKDIR /osdev

# Configure

COPY . ./
RUN ./configure

# Build
ENTRYPOINT [ "make", "iso" ]
