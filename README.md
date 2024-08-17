# arduino-server

A server for interacting with an arduino.

## COPYING

Copyright (©) 2024  Frosty515

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

## Arduino support

Currently only `Arduino Uno R3` is supported. To add support for others, you will need to add more pin support in the `cpp-frontend`, `js-server` and `arduino` folders.
To add more pin support, you will need to update the `PIN_COUNT` macro in `cpp-frontend/src/App.cpp`. Then, you will need to update the first line of `js-server/index.js` to be the number of pins you want to support. Then, you will need to update the `arduino/arduino.ino` file to support the new pins.

## Requirements

- cjson
- GCC
- binutils
- nodejs
- npm
- ninja
- cmake

### Installation of requirements

#### Debian/Ubuntu

Run `sudo apt update && sudo apt install build-essential libcjson-dev nodejs npm cmake ninja-build`

#### Arch

Run `sudo pacman -Syu base-devel cjson nodejs npm cmake ninja`

## Building

1. For the first build, run `cd js-server && npm update`.
2. `arduino/arduino.ino` needs to be built and uploaded to the arduino.
3. Create and enter a build directory with `mkdir build && cd build`.
4. Run `cmake -GNinja ..` to configure the build.
5. Run `ninja install` to build and install the project to the `bin` directory in the root of the project.

## Running

Run `cd js-server && ../cpp-backend/bin/cpp-backend server.js <serial_port>`, where `<serial_port>` is the serial port the arduino is connected to.
The server lauches a http server on port 8080.

## Connecting

### HTML web frontend

The web frontend is in the `js-server` folder with the server. To connect to the server, open a web browser and go to `http://localhost:8080`.

### GTK+ 4 based C++ frontend

The C++ frontend is in the `cpp-frontend` folder. To connect to the server, run `./bin/cpp-frontend`.

## HTTPS support

For https support, a key and certificate with the names `selfsigned.key` and `selfsigned.crt`, respectively, will need to be generated in the `js-server` folder. Also, lines 29-35, 106 and 112-114 in `js-server/server.js` will need to be uncommented. With this, a https server will also start on port 8443.
