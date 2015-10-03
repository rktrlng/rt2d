#!/bin/bash

# sudo apt-get install -y git cmake g++ libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxi-dev

if [ -d build ]; then
	rm -rf build
fi

mkdir -p build
cd build
cmake -Wno-dev ..
make

./demo

cd ..
