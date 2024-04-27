#!/bin/sh

set -e

cd cpp-backend
rm -fr build bin dependencies/libserial/build

mkdir -p build
cd build

cmake -DCMAKE_BUILD_TYPE=Release -GNinja ..
ninja install

cd ../..

rm -fr dist/x86_64-linux
mkdir -p dist/x86_64-linux
cd dist/x86_64-linux

mkdir -p bin
cp ../../cpp-backend/bin/cpp-backend bin/

mkdir -p js-server
cd js-server
cp ../../../js-server/{index.{html,js},{arduino_lib,server}.js,style.css,package{,-lock}.json} .
npm install

cd ..

cp ../../{README.md,LICENSE} .

cp ../../scripts/run-linux.sh run.sh
chmod 755 run.sh

cp ../../docs/simple-README-linux.md README.md

mkdir -p arduino
cp ../../arduino/arduino.ino arduino/

cd ../..

tar -czf dist/x86_64-linux.tar.gz -C dist x86_64-linux