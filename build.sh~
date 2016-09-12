#!/bin/bash

echo "Starting build script..."

if [ ! -d build ]; then
  echo "Creating the build directory..."
  mkdir build && echo "Build directory created successfully." || (echo "Failed to create build directory." && exit 1)
else
  echo "Build directory already exists."
fi

echo "Moving to the build directory..."
cd build && echo "Navigated to the build directory successfully." || (echo "Build directory doesn't exist." && exit 1)

echo "Compiling solus-installer..."
gcc `pkg-config --cflags gtk+-3.0` ../src/solus-installer.c ../src/welcome.c ../src/timezone.c -o solus-installer `pkg-config --libs gtk+-3.0` -Wall --std=c11 && echo "Successfully compiled solus-installer." || echo "Failed to compile solus-installer."

echo "Exiting build script..."
