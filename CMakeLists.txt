cmake_minimum_required(VERSION 3.27)
project(Nearest_Shape)

set(CMAKE_CXX_STANDARD 17)

add_executable(Nearest_Shape main.cpp
        Point.cpp
        Point.h
        LineSegment.cpp
        LineSegment.h
        Triangle.cpp
        Triangle.h
        Management.cpp
        Management.h
        Tool.h
        Tool.cpp
)
