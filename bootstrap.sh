#!/bin/bash

# sudo apt-get install -y git cmake g++ libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxi-dev

if [ -d build ]; then
	rm -rf build
fi

mkdir -p build
cd build
cmake -Wno-dev ..

if [ "$OSTYPE" == "win32" ] || [ "$OSTYPE" == "msys" ]; then
	echo "Double-click the 'rt2d.sln' file in the 'build' directory to open the project in Visual Studio."
	echo "Right-click 'demo' tab and select 'Set as StartUp Project'. Then press <ctrl>-F5."
else
	make
	./demo
fi

cd ..
