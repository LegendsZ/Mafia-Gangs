cmake_minimum_required(VERSION 3.24)
project(Mafia-Gangs)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find the SDL2 code on the system, will define path variables
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Specify include directories that apply to all targets
include_directories(PUBLIC "${CMAKE_SOURCE_DIR}/include"
	$<TARGET_PROPERTY:SDL2::SDL2,INTERFACE_INCLUDE_DIRECTORIES>)

# List of source files to compile to objects 
set(OBJECT_SOURCES Audio Bullet Button CollisionMap Dialog Enemy FRect Game 
	GameManager GameMode Gun HUD Loading Menu MissionBase MissionManager
	MissionOne Rect Settings Text Window ScreenVisibility)

# Loop over `OBJECT_SOURCES` and compile each one, keeping track of the
# generated object files in `_OBJECTS_` (underscores used because `OBJECT` and
# `OBJECTS` are keywords)
foreach(_OBJECT_ ${OBJECT_SOURCES})

	# Declare a new object that should be built ...
	add_library(${_OBJECT_} OBJECT "${CMAKE_SOURCE_DIR}/src/${_OBJECT_}.cpp")

	target_include_directories(${_OBJECT_} PUBLIC "${CMAKE_SOURCE_DIR}/include")

	# ... add the output object to `OBJECTS` list
	list(APPEND _OBJECTS_ $<TARGET_OBJECTS:${_OBJECT_}>)

endforeach()

# Add specific additional include directories to targets where necessary
target_include_directories(Audio PUBLIC $<TARGET_PROPERTY:SDL2_mixer::SDL2_mixer,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(FRect PUBLIC $<TARGET_PROPERTY:SDL2_image::SDL2_image,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(Rect PUBLIC $<TARGET_PROPERTY:SDL2_image::SDL2_image,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(Window PUBLIC $<TARGET_PROPERTY:SDL2_image::SDL2_image,INTERFACE_INCLUDE_DIRECTORIES>
											$<TARGET_PROPERTY:SDL2_ttf::SDL2_ttf,INTERFACE_INCLUDE_DIRECTORIES>)


# Compile the complete executable against all objects and SDL libraries
add_executable(MafiaGangs "${CMAKE_SOURCE_DIR}/src/Source.cpp")
target_link_libraries(MafiaGangs SDL2::SDL2 SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf ${_OBJECTS_})
