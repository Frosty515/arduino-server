# arduino-server

A server for interacting with an arduino.

## Arduino support

Currently only `Arduino Uno R3` is supported. To add support for others, you will need to add more pin support in the `js-server` and `arduino` folders.

## Requirements

1. cjson
2. make
3. GCC
4. binutils
5. nodejs

### Installation of requirements

#### Debian/Ubuntu

Run `sudo apt update && sudo apt install build-essential libcjson-dev nodejs`

#### Arch

Run `sudo pacman -Syu base-devel cjson nodejs`

## Building

1. `arduino/arduino.ino` needs to be built and uploaded to the arduino.
2. Run `make -C cpp-backend -j<N> all`, where `<N>` is the number of jobs or the amount of logical processors in your system.

## Running

Run `cd js-server && ../cpp-backend/bin/cpp-backend server.js <serial_port>`, where `<serial_port>` is the serial port the arduino is connected to.
The server lauches a http server on port 8080.

## HTTPS support
For https support, a key and certificate with the names `selfsigned.key` and `selfsigned.crt`, respectively, will need to be generated in the `js-server` folder. Also, lines 12-18, 93 and 99-101 in `js-server/server.js` will need to be uncommented. With this, a https server will also start on port 8443.


