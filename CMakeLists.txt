cmake_minimum_required(VERSION 3.13.4)
project(clusters)

set(CMAKE_CXX_STANDARD 17)

add_executable(clusters
        src/main.cpp
        src/point.cpp
        src/cloud.cpp
        src/field.cpp
        src/user_interface.cpp
        src/Dbscan.cpp

        include/point.h
        include/cloud.h
        include/field.h
        include/user_interface.h
        include/Dbscan.h)