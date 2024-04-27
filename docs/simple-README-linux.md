# arduino-server

A server for interacting with an arduino.

## Arduino support

Currently only `Arduino Uno R3` is supported. To add support for others, you will need to add more pin support in the `js-server` and `arduino` folders.
To add more pin support, you will need to update the first line of `js-server/index.js` to be the number of pins you want to support. Then, you will need to update the `arduino/arduino.ino` file to support the new pins.

## Requirements

1. cjson
2. nodejs

### Installation of requirements

#### Debian/Ubuntu

Run `sudo apt update && sudo apt install libcjson-dev nodejs`

#### Arch

Run `sudo pacman -Syu cjson nodejs`

## Building

The arduino code will needed to be compiled and uploaded to the arduino. It can be found at arduino/arduino.ino.

## Running

Run `./run.sh <serial_port>`, where `<serial_port>` is the serial port the arduino is connected to.
The server launches a http server on port 8080.

## HTTPS support

For https support, a key and certificate with the names `selfsigned.key` and `selfsigned.crt`, respectively, will need to be generated in the `js-server` folder. Also, lines 12-18, 93 and 99-101 in `js-server/server.js` will need to be uncommented. With this, a https server will also start on port 8443.
