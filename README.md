#solus-installer

## About
solus-installer is an installer for the Solus operating system.
Website: https://solus-project.com/

## Compiling
```
gcc `pkg-config --cflags gtk+-3.0` -o solus-installer solus-installer.c `pkg-config --libs gtk+-3.0` -Wall --std=c11
```

## Running
```
./solus-installer
```

## License
solus-installer is licensed under GPLv2, see LICENSE
