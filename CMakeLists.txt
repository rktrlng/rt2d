# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (rt2d)

# delete CMakeCache.txt from the build directory when you edit these options
####################################################################
OPTION(MAKE_START "Make RT2D start application" ON)
OPTION(MAKE_DEMO "Make RT2D demo (tests) application" ON)
OPTION(MAKE_FLOCKING "Make flocking application" ON)
OPTION(MAKE_BASIC3D "Make basic3D application" ON)
OPTION(MAKE_NOISE "Make Perlin Noise application" ON)
OPTION(MAKE_GEOMETRIC "Make GeoMetric application" ON)
OPTION(MAKE_SHADY "Make custom Shader application" ON)
OPTION(MAKE_WOLFENSTEIN "Make Wolfenstein3D raycasting application" ON)

OPTION(USE_RS232 "Use RS232 library" OFF)
OPTION(MAKE_SERIAL "Make serial application" OFF)

OPTION(USE_OPENAL "Use OpenAL library" OFF)
OPTION(MAKE_AUDIOSTART "Make OpenAL/RT2D audiostart" OFF)
OPTION(MAKE_OPENAL_TONEGEN "Make OpenAL Tone Generator" OFF)

OPTION(USE_BOX2D "Use Box2D" OFF)
OPTION(MAKE_BOX2DSTART "Make Box2D/RT2D box2dstart" OFF)
####################################################################

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like 'build')" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()


if(UNIX)
	#set(CMAKE_CXX_FLAGS "-Wall -std=c++0x -pedantic -O2 -g -pg")
	#set(CMAKE_CXX_FLAGS "-Wall -Wstrict-aliasing -std=c++0x -O2")

	set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -O2")

	# valgrind --leak-check=full ./demo
	# ./demo # creates cmon.out
	# gprof demo gmon.out > analysis.txt
	#set(CMAKE_CXX_FLAGS "-Wall -pg -std=c++11")
endif(UNIX)


if(WIN32)
	# suppress pedantic warnings
	add_definitions( "/W1 /D_CRT_SECURE_NO_WARNINGS /wd4514 /nologo" )
endif(WIN32)


# Compile external dependencies
find_package(OpenGL REQUIRED)

add_subdirectory (external)

include_directories(
	${CMAKE_SOURCE_DIR}/external/glfw-3.0.3/include/GLFW
	${CMAKE_SOURCE_DIR}/external/glm-0.9.8.4
	${CMAKE_SOURCE_DIR}/external/glew-1.9.0/include
	${CMAKE_SOURCE_DIR}/external
	${CMAKE_SOURCE_DIR}/rt2d
	${CMAKE_SOURCE_DIR}/.
)

link_directories(
	${CMAKE_SOURCE_DIR}/external/glfw-3.0.3/src
	${CMAKE_SOURCE_DIR}/external/glew-1.9.0
	${CMAKE_SOURCE_DIR}/external
	${CMAKE_SOURCE_DIR}/rt2d
)

set(ALL_GRAPHICS_LIBS
	${OPENGL_LIBRARY}
	rt2d
	GLFW_303
	GLEW_190
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

####################################################################
# librt2d.a                                                        #
####################################################################
add_library(rt2d
	rt2d/camera.cpp
	rt2d/camera.h
	rt2d/canvas.cpp
	rt2d/canvas.h
	rt2d/color.h
	rt2d/core.cpp
	rt2d/core.h
	rt2d/entity.cpp
	rt2d/entity.h
	rt2d/input.cpp
	rt2d/input.h
	rt2d/line.cpp
	rt2d/line.h
	rt2d/mesh.cpp
	rt2d/mesh.h
	rt2d/noise.cpp
	rt2d/noise.h
	rt2d/pointx.h
	rt2d/renderer.cpp
	rt2d/renderer.h
	rt2d/resourcemanager.cpp
	rt2d/resourcemanager.h
	rt2d/rt2dconfig.h
	rt2d/scene.cpp
	rt2d/scene.h
	rt2d/shader.cpp
	rt2d/shader.h
	rt2d/sprite.cpp
	rt2d/sprite.h
	rt2d/text.cpp
	rt2d/text.h
	rt2d/texture.cpp
	rt2d/texture.h
	rt2d/timer.cpp
	rt2d/timer.h
	rt2d/util.c
	rt2d/util.h
	rt2d/vectorx.h
)
file(
	COPY ${CMAKE_SOURCE_DIR}/rt2d/shaders
	DESTINATION ${CMAKE_BINARY_DIR}
)
file(
	COPY ${CMAKE_SOURCE_DIR}/rt2d/fonts
	DESTINATION ${CMAKE_BINARY_DIR}
)

####################################################################
# start                                                            #
####################################################################
IF(MAKE_START)
	add_executable(start
		start/main.cpp
		start/myentity.cpp
		start/myentity.h
		start/myscene.cpp
		start/myscene.h
	)
	target_link_libraries(start
		${ALL_GRAPHICS_LIBS}
	)
	# Copy assets to the build directory
	file(
		COPY start/assets
		DESTINATION ${CMAKE_BINARY_DIR}
	)
ENDIF()

####################################################################
# demo                                                             #
####################################################################
IF(MAKE_DEMO)
	add_executable(demo
		projects/demo/main.cpp
		projects/demo/basicentity.cpp
		projects/demo/basicentity.h
		projects/demo/scene00.cpp
		projects/demo/scene00.h
		projects/demo/scene01.cpp
		projects/demo/scene01.h
		projects/demo/scene02.cpp
		projects/demo/scene02.h
		projects/demo/scene03.cpp
		projects/demo/scene03.h
		projects/demo/scene03a.cpp
		projects/demo/scene03a.h
		projects/demo/scene04.cpp
		projects/demo/scene04.h
		projects/demo/scene05.cpp
		projects/demo/scene05.h
		projects/demo/scene06.cpp
		projects/demo/scene06.h
		projects/demo/scene06a.cpp
		projects/demo/scene06a.h
		projects/demo/scene07.cpp
		projects/demo/scene07.h
		projects/demo/scene08.cpp
		projects/demo/scene08.h
		projects/demo/scene09.cpp
		projects/demo/scene09.h
		projects/demo/scene10.cpp
		projects/demo/scene10.h
		projects/demo/scene11.cpp
		projects/demo/scene11.h
	    projects/demo/scene12.cpp
	    projects/demo/scene12.h
	    projects/demo/scene13.cpp
	    projects/demo/scene13.h
	    projects/demo/scene14.cpp
	    projects/demo/scene14.h
		projects/demo/scene15.cpp
		projects/demo/scene15.h
		projects/demo/scene16.cpp
		projects/demo/scene16.h
		projects/demo/scene17.cpp
		projects/demo/scene17.h
		projects/demo/scene18.cpp
		projects/demo/scene18.h
		projects/demo/scene19.cpp
		projects/demo/scene19.h
		projects/demo/scene20.cpp
		projects/demo/scene20.h
		projects/demo/scene21.cpp
		projects/demo/scene21.h
		projects/demo/scene22.cpp
		projects/demo/scene22.h
		projects/demo/superscene.cpp
		projects/demo/superscene.h
	)
	target_link_libraries(demo
		${ALL_GRAPHICS_LIBS}
	)
	# Copy assets to the build directory
	file(
		COPY projects/demo/assets
		DESTINATION ${CMAKE_BINARY_DIR}
	)
ENDIF()

####################################################################
# Cube                                                             #
####################################################################
IF(MAKE_BASIC3D)
	add_executable(basic3D
		projects/basic3D/main.cpp
		projects/basic3D/cube.cpp
		projects/basic3D/cube.h
		projects/basic3D/myscene.cpp
		projects/basic3D/myscene.h
	)
	target_link_libraries(basic3D
		${ALL_GRAPHICS_LIBS}
	)
	# Copy assets to the build directory
	file(
		COPY projects/basic3D/assets
		DESTINATION ${CMAKE_BINARY_DIR}
	)
ENDIF()


####################################################################
# Noise                                                            #
####################################################################
IF(MAKE_NOISE)
	add_executable(noise
		projects/perlinnoise/main.cpp
		projects/perlinnoise/myscene.cpp
		projects/perlinnoise/myscene.h
	)
	target_link_libraries(noise
		${ALL_GRAPHICS_LIBS}
	)
ENDIF()

####################################################################
# geometric                                                        #
####################################################################
IF(MAKE_GEOMETRIC)
	add_executable(geometric
		projects/geometric/main.cpp
		projects/geometric/geometric.cpp
		projects/geometric/geometric.h
		projects/geometric/myscene.cpp
		projects/geometric/myscene.h
	)
	target_link_libraries(geometric
		${ALL_GRAPHICS_LIBS}
	)
ENDIF()

####################################################################
# slim shady                                                       #
####################################################################
IF(MAKE_SHADY)
	add_executable(slimshady
		projects/slimshady/main.cpp
		projects/slimshady/myentity.cpp
		projects/slimshady/myentity.h
		projects/slimshady/myscene.cpp
		projects/slimshady/myscene.h
	)
	target_link_libraries(slimshady
		${ALL_GRAPHICS_LIBS}
	)
	# Copy shaders to the build directory
	file(
		COPY projects/slimshady/shaders
		DESTINATION ${CMAKE_BINARY_DIR}
	)
	# Copy assets to the build directory
	file(
		COPY projects/slimshady/assets
		DESTINATION ${CMAKE_BINARY_DIR}
	)
ENDIF()

####################################################################
# flocking                                                         #
####################################################################
IF(MAKE_FLOCKING)
	add_executable(flocking
		projects/flocking/boid.cpp
		projects/flocking/flock.cpp
		projects/flocking/scene01.cpp
		projects/flocking/main.cpp
	)
	target_link_libraries(flocking
		${ALL_GRAPHICS_LIBS}
	)
	# Copy assets to the build directory
	file(
		COPY projects/flocking/assets
		DESTINATION ${CMAKE_BINARY_DIR}
	)
ENDIF()

####################################################################
# Wolfenstein3D                                                    #
####################################################################
IF(MAKE_WOLFENSTEIN)
	add_executable(wolfenstein
		projects/wolfenstein/wolfenstein.cpp
		projects/wolfenstein/main.cpp
	)
	target_link_libraries(wolfenstein
		${ALL_GRAPHICS_LIBS}
	)
ENDIF()

####################################################################
# librs232.a                                                       #
####################################################################
IF(USE_RS232)
	include_directories(
		${CMAKE_SOURCE_DIR}/external/rs232
	)
	link_directories(
		${CMAKE_SOURCE_DIR}/external/rs232
	)
	add_library( rs232 STATIC
		external/rs232/rs232.c
		external/rs232/rs232.h
	)
ENDIF()

####################################################################
# serial                                                           #
####################################################################
IF(MAKE_SERIAL AND USE_RS232)
	add_executable(serial
		projects/serial/main.cpp
		projects/serial/myscene.cpp
		projects/serial/myscene.h
	)
	target_link_libraries(serial
		${ALL_GRAPHICS_LIBS}
		rs232
	)
ENDIF()

####################################################################
# OpenAL                                                           #
####################################################################
IF(USE_OPENAL)
	add_subdirectory (external/openal)
	include_directories(
		${CMAKE_SOURCE_DIR}/external/openal/include/
	)

	link_directories(
		${CMAKE_SOURCE_DIR}/external/openal/
	)

	IF(WIN32)
		SET(OPENAL OpenAL32)
	ELSE()
		SET(OPENAL openal)
	ENDIF()
ENDIF()

####################################################################
# RT2D/OpenAL audiostart                                           #
####################################################################
IF(MAKE_AUDIOSTART AND USE_OPENAL)
	add_executable(audiostart
		projects/audiostart/main.cpp
		projects/audiostart/myentity.cpp
		projects/audiostart/myentity.h
		projects/audiostart/myscene.cpp
		projects/audiostart/myscene.h
		projects/audiostart/audio/audio.cpp
		projects/audiostart/audio/audio.h
		projects/audiostart/audio/sound.cpp
		projects/audiostart/audio/sound.h
		projects/audiostart/audio/wav.cpp
		projects/audiostart/audio/wav.h
	)
	target_link_libraries(audiostart
		${ALL_GRAPHICS_LIBS}
		${OPENAL}
	)
	# Copy assets to the build directory
	file(
		COPY projects/audiostart/assets
		DESTINATION ${CMAKE_BINARY_DIR}
	)
ENDIF()

####################################################################
# OpenAL tone generator                                            #
####################################################################
IF(MAKE_OPENAL_TONEGEN AND USE_OPENAL)
	add_executable(altonegenrt
		external/openal/examples/altonegen.c
		external/openal/examples/common/alhelpers.c
	)
	target_link_libraries(altonegenrt
		${OPENAL}
	)
ENDIF()

####################################################################
# box2d.a                                                          #
####################################################################
IF(USE_BOX2D)
	option(BOX2D_INSTALL "Install Box2D libs, includes, and CMake scripts" OFF)
	option(BOX2D_INSTALL_DOC "Install Box2D documentation" OFF)
	option(BOX2D_BUILD_SHARED "Build Box2D shared libraries" OFF)
	option(BOX2D_BUILD_STATIC "Build Box2D static libraries" ON)
	option(BOX2D_BUILD_EXAMPLES "Build Box2D examples" OFF)

	set(BOX2D_VERSION 2.3.2)
	set(LIB_INSTALL_DIR lib${LIB_SUFFIX})

	# The Box2D library.
	add_subdirectory(external/Box2D)

	include_directories(
		${CMAKE_SOURCE_DIR}/external/Box2D
	)
	link_directories(
		${CMAKE_SOURCE_DIR}/external/Box2D
	)
	add_definitions(
	    -DBOX2D_BUILD_STATIC
	)
	set(BOX2D_LIB
	    Box2D
	)
ENDIF()

####################################################################
# Box2D/RT2D box2dstart                                            #
####################################################################
IF(MAKE_BOX2DSTART AND USE_BOX2D)
	add_executable(box2dstart
		projects/box2dstart/main.cpp
		projects/box2dstart/scene01.cpp
	)
	target_link_libraries (box2dstart
		${BOX2D_LIB}
		${ALL_GRAPHICS_LIBS}
	)
ENDIF()

####################################################################
