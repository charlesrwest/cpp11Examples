cmake_minimum_required (VERSION 2.8.3)
PROJECT(cpp11Examples)


#Get c++11
ADD_DEFINITIONS(-std=c++11)

find_package(Threads)

#Tell compiler where to find required libraries
link_directories(/usr/lib/x86_64-linux-gnu/ lib/)

include_directories(./src/library/ ./src/executables/unitTests)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

#Get lists of the source files
FILE(GLOB SOURCEFILES ./src/library/*.cpp ./src/library/*.c)

FILE(GLOB UNIT_TESTS_EXECUTABLE_SOURCE ./src/executables/unitTests/*.cpp ./src/executables/unitTests/*.c)

#Set the binaries to be placed in the ./bin/ directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib/")

#Create a libraries
add_library(library SHARED  ${SOURCEFILES})

#Tell CMake what executables to make
ADD_EXECUTABLE(unitTests ${UNIT_TESTS_EXECUTABLE_SOURCE} ) 

target_link_libraries(library dl ${CMAKE_THREAD_LIBS_INIT})

#link libraries to executable
target_link_libraries(unitTests library)

