cmake_minimum_required(VERSION 3.24)
project(PixelWork C)

set(CMAKE_C_STANDARD 99)

add_executable(PixelWork main.c Quat.h functions/functions.h functions/functions.c)
