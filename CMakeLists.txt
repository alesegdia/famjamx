cmake_minimum_required(VERSION 2.8.11)

project(fgjx)

add_subdirectory(module/aether)

include("module/aether/cmake/Build.cmake")

file(GLOB_RECURSE GAMESOURCES "src/*.cpp" "src/*.h")

ADD_AETHER_TARGET(fgjx "${GAMESOURCES}")
add_executable(bmptomap util/bitmap_image.hpp util/mapgen.cpp)
set_target_properties(bmptomap PROPERTIES COMPILE_FLAGS "-g")

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")
