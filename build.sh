#!/bin/sh

export DOCKER_DEFAULT_PLATFORM=linux/amd64

rm -rf build

echo "Building docker image"
docker build . -t mykernel:latest
echo "Building OS"
docker run --name mykernel-builder mykernel:latest

echo "Finishing up"
docker cp mykernel-builder:/osdev/build ./build

docker rm mykernel-builder
