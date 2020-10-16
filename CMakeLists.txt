cmake_minimum_required(VERSION 3.13)
project(RaspberryPi_cpp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -l wiringPi")

#add_executable(RaspberryPi_cpp main.cpp Display.cpp Display.h)
file(GLOB sources *.cpp)
file(GLOB headers *.h)

add_executable(RaspberryPi_cpp ${sources} ${headers})