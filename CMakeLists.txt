cmake_minimum_required(VERSION 2.8.9)
include_directories(src/include)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

file(GLOB FACECOPE_SOURCES "src/main.cpp" "src/playground/*.cpp")

project(facecope)
add_executable(${CMAKE_PROJECT_NAME} ${FACECOPE_SOURCES})



