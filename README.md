# SEMduino-temp-shield
## Install prerequisites
### Linux
```
sudo apt-get install gcc-avr binutils-avr avr-libc gdb-avr avrdude
sudo usermod -a -G dialout $USER
```
Logout and log back in after `usermod`.

## Build/flash
Build: `make`

Flash: `make flash`

Clean: `make clean`
