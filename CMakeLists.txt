project(asteroid)
cmake_minimum_required(VERSION 3.10)

# Activate C99 standard:
SET(CMAKE_C_COMPILER "gcc" )
SET(CMAKE_C_FLAGS "-std=c11" )
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

# RayLib:
#find_package(raylib 3.0 REQUIRED)
#set(raylib_VERBOSE 1)

# Local dependency: (RayLib) :
include_directories( ${PROJECT_SOURCE_DIR}/dpd/include )
link_directories( ${PROJECT_SOURCE_DIR}/dpd )

# Build the Asteroid game:
aux_source_directory(IMT-Projet-Info SRC_LIST)
add_executable(asteroid ${SRC_LIST})
target_link_libraries(asteroid raylib pthread dl rt X11 m)

#without cmake package... 
#include_directories(${PROJECT_SOURCE_DIR}/raylib/src)
#link_directories(${PROJECT_SOURCE_DIR}/raylib)
#target_link_libraries(nw-viewer raylib GL m pthread dl rt X11)
