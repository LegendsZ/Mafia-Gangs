cmake_minimum_required(VERSION 3.26)
project(Mafia-Gangs)
set(CMAKE_CXX_STANDARD 20)

# Find the SDL2 code on the system, will define path variables
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Define global include directories (because all targets require the same
# include directories)
include_directories(PUBLIC "${CMAKE_SOURCE_DIR}/include" 
							${SDL2_INCLUDE_DIRS})

# List of source files to compile to objects 
set(OBJECT_SOURCES Audio Bullet Button CollisionMap Dialog Enemy FRect Game 
	GameManager GameMode Gun HUD Loading Menu MissionBase MissionManager
	MissionOne Rect Settings Text Window ScreenVisibility)

# Loop over `OBJECT_SOURCES` and compile each one, keeping track of the
# generated object files in `_OBJECTS_` (underscores used because `OBJECT` and
# `OBJECTS` are keywords)
foreach(_OBJECT_ ${OBJECT_SOURCES})

	# Declare a new object that should be built, link the SDL2 libraries
	add_library(${_OBJECT_} OBJECT "${CMAKE_SOURCE_DIR}/src/${_OBJECT_}.cpp")
	target_link_libraries(${_OBJECT_} ${SDL_LIBRARIES})

	# Add the output object to `OBJECTS` list
	list(APPEND _OBJECTS_ $<TARGET_OBJECTS:${_OBJECT_}>)
endforeach()

# Compile the complete executable against all objects and SDL libraries/headers
add_executable(MafiaGangs "${CMAKE_SOURCE_DIR}/src/Source.cpp")
target_link_libraries(MafiaGangs ${_OBJECTS_} ${SDL_LIBRARIES})
