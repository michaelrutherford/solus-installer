#solus-installer

## About
solus-installer is an installer for the [Solus](https://solus-project.com/) operating system.

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
