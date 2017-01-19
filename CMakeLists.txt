# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (rt2d)

# delete CMakeCache.txt from the build directory when you edit these options
OPTION(MAKE_START "Make RT2D start application" ON)
OPTION(MAKE_DEMO "Make RT2D demo (tests) application" ON)
OPTION(MAKE_FLOCKING "Make flocking application" ON)
OPTION(MAKE_RS232 "Make RS232 library" OFF)
OPTION(USE_OPENAL "Use OpenAL" OFF)
OPTION(MAKE_AUDIOSTART "Make OpenAL/RT2D audiostart" OFF)
OPTION(MAKE_OPENAL_TONEGEN "Make OpenAL Tone Generator" OFF)


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

	set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

	# valgrind --leak-check=full ./demo
	# ./demo # creates cmon.out
	# gprof demo gmon.out > analysis.txt
	#set(CMAKE_CXX_FLAGS "-Wall -pg -std=c++11")
endif(UNIX)


if(WIN32)
	# On Visual 2005 and above, this module can set the debug working directory
	list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-1c73e35")
	include(CreateLaunchers)
	include(MSVCMultipleProcessCompile) # /MP

	if(MINGW)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	ELSE(MINGW)
		add_definitions( "/W3 /D_CRT_SECURE_NO_WARNINGS /wd4514 /nologo" ) # suppress pedantic warnings
	endif(MINGW)
endif(WIN32)


# Compile external dependencies
find_package(OpenGL REQUIRED)

add_subdirectory (external)

include_directories(
	${CMAKE_SOURCE_DIR}/external/glfw-3.0.3/include/GLFW/
	${CMAKE_SOURCE_DIR}/external/glm-0.9.7.0/
	${CMAKE_SOURCE_DIR}/external/glew-1.9.0/include/
	${CMAKE_SOURCE_DIR}/rt2d/
	${CMAKE_SOURCE_DIR}/.
)

link_directories(
	${CMAKE_SOURCE_DIR}/external/glfw-3.0.3/src/
	${CMAKE_SOURCE_DIR}/external/glew-1.9.0/
	${CMAKE_SOURCE_DIR}/external/
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
# librs232.a                                                       #
####################################################################
IF(MAKE_RS232)
	include_directories(
		${CMAKE_SOURCE_DIR}/external/rs232/
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
# librt2d.a                                                        #
####################################################################
add_library(rt2d
	rt2d/camera.cpp
	rt2d/camera.h
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
	rt2d/stringutil.h
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
		projects/demo/canvas.cpp
		projects/demo/canvas.h
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
		projects/demo/scene03b.cpp
		projects/demo/scene03b.h
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
# RT2D/OpenAL audio start                                          #
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


if(WIN32)
	# Xcode and Visual working directories for demo
	#set_target_properties(demo PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/demo/")
	#create_target_launcher(demo WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/demo/")

	# Xcode and Visual working directories for start
	#set_target_properties(start PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/start/")
	#create_target_launcher(start WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/start/")

	# create file tabs in visual studio
	#SOURCE_GROUP(rt2d REGULAR_EXPRESSION ".*/rt2d/.*" )
	#SOURCE_GROUP(demo REGULAR_EXPRESSION ".*/demo/.*" )
	#SOURCE_GROUP(start REGULAR_EXPRESSION ".*/start/.*" )
	#SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shaders$" )
endif(WIN32)


if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
#add_custom_command(
#   TARGET demo POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/demo${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/demo/"
#)
elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
