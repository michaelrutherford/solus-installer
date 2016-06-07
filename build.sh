#!/bin/bash
echo "Creating the build directory..."
mkdir build
echo "Build directory created successfully."
echo "Moving to the build directory..."
cd build
echo "Navigated to the build directory successfully."
echo "Compiling solus-installer..."
gcc `pkg-config --cflags gtk+-3.0` src/solus-installer.c src/welcome.c src/timezone.c -o solus-installer `pkg-config --libs gtk+-3.0` -Wall --std=c11
echo "Successfully compiled solus-installer."
