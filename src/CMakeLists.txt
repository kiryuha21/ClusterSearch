include_directories(include)

add_executable(
        clusters
        main.cpp
        point.cpp
        cloud.cpp
        field.cpp
        user_interface.cpp
        Dbscan.cpp
        Forel.cpp
        Sptr.cpp
)