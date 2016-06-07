#!/bin/bash
gcc `pkg-config --cflags gtk+-3.0` src/solus-installer.c src/welcome.c src/timezone.c -o solus-installer `pkg-config --libs gtk+-3.0` -Wall --std=c11
