cmake_minimum_required(VERSION 3.13.4)
project(clusters)

set(CMAKE_CXX_STANDARD 17)

add_executable(clusters main.cpp point.cpp point.h cloud.cpp cloud.h field.cpp field.h user_interface.cpp user_interface.h)