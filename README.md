RT2D
====

RT2D is a RealTime 2D framework, based on somewhat 'modern' OpenGL (2.1+). It compiles and runs on Mac, Linux and Windows.

Compatibility is chosen over features. Readability over efficiency. Simplicity over speed. There's no fancy OpenGL stuff here. Just update and render scenes with entities that contain (colored) sprites, spritesheets, spritebatches, pixelbuffers, fonts and lines.

Compiling
---------

Use cmake to create your project files in a separate `build` directory.

> You should always be able to delete the `build` directory without losing your work! Whatever you do, work in the `src` directory! That's `demo` and/or `rt2d`.

Documentation
-------------

To generate the documentation, run doxygen (with Doxyfile as input) in the root directory of this project:

	doxygen Doxyfile

Then open `documentation.html` in the `doc` directory.

Linux
-----

On Debian-based Linux, install the following libraries:

	sudo apt-get install -y git cmake doxygen g++ libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxi-dev

Run `bootstrap.sh` or:

	mkdir build
	cd build
	cmake -Wno-dev ..
	make

Then you can run the demo:

	./demo

Make sure to add any new files you create to the `CMakeLists.txt` file.

Mac OS X
--------

Install the following:

- XCode + commandline developer tools
- git
- cmake
- doxygen

Run `bootstrap.sh` or:

	mkdir build
	cd build
	cmake -Wno-dev ..
	make

Then you can run the demo:

	./demo

Make sure to add any new files you create to the `CMakeLists.txt` file.

MS Windows (VS2015)
-------------------

Install the following:

- Visual Studio 2015 Community Edition (VS2013 also works fine).
- git
- cmake
- doxygen

In the powershell, run:

	mkdir build
	cd build
	cmake -Wno-dev ..

Then doubleclick the `rt2d.sln` file in the `build` directory. Right-click the 'start' directory in Visual Studio and select 'Set as StartUp Project'. Then press ctrl-F5.

Make sure that when you add new files within Visual Studio, you move them to the correct directory in `src` and add them to the `CMakeLists.txt` file.

Libraries
---------

- glfw: <http://www.glfw.org/>
- glew: <http://glew.sourceforge.net/>
- glm: <http://glm.g-truc.net/>
- OpenAL: <https://github.com/kcat/openal-soft>
- Box2D: <https://github.com/erincatto/Box2D>

Links
-----

- <http://www.opengl-tutorial.org/>
- <http://learnopengl.com/>
- <http://simonschreibt.de/gat/renderhell/>
- <https://github.com/ellisonleao/magictools>

The `CMakeLists.txt` file and `rt2d/shader.cpp` are based on the ones found here: <http://www.opengl-tutorial.org/>.

If you're having trouble compiling this project, follow instructions on <http://www.opengl-tutorial.org/>. Once that compiles, this will probably also compile.

License
-------

Copyright 2015 Rik Teerling <rik@onandoffables.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.
