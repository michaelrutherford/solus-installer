# solus-installer

## About
solus-installer is an installer for the [Solus](https://solus-project.com/) operating system.

## Compiling
*Navigate to the root directory of solus-installer and run the following command:*
```
gcc `pkg-config --cflags gtk+-3.0` src/solus-installer.c -o solus-installer `pkg-config --libs gtk+-3.0` -Wall --std=c11
```

## Running
*After compiling solus-installer, enter the following command:*
```
./solus-installer
```

## License
solus-installer is licensed under GPLv2, see LICENSE
