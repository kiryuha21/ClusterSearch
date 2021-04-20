cmake_minimum_required(VERSION 3.13.4)
project(clusters)

set(CMAKE_CXX_STANDARD 17)

add_executable(clusters
        /home/kiryuha21/CLionProjects/clusters/src/main.cpp
        /home/kiryuha21/CLionProjects/clusters/src/point.cpp
        /home/kiryuha21/CLionProjects/clusters/src/cloud.cpp
        /home/kiryuha21/CLionProjects/clusters/src/field.cpp
        /home/kiryuha21/CLionProjects/clusters/src/user_interface.cpp
        /home/kiryuha21/CLionProjects/clusters/src/Dbscan.cpp

        /home/kiryuha21/CLionProjects/clusters/include/point.h
        /home/kiryuha21/CLionProjects/clusters/include/cloud.h
        /home/kiryuha21/CLionProjects/clusters/include/field.h
        /home/kiryuha21/CLionProjects/clusters/include/user_interface.h
        /home/kiryuha21/CLionProjects/clusters/include/Dbscan.h)