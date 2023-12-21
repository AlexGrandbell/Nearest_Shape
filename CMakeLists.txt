cmake_minimum_required(VERSION 3.27)
project(Nearest_Shape)

set(CMAKE_CXX_STANDARD 17)

add_executable(Nearest_Shape main.cpp
        Point/Point.cpp
        Point/Point.h
        LineSegment/LineSegment.cpp
        LineSegment/LineSegment.h
        Triangle/Triangle.cpp
        Triangle/Triangle.h
        Management/Management.cpp
        Management/Management.h
        Tool/Tool.h
        Tool/Tool.cpp
        Point/PointManagement.cpp
        Point/PointManagement.h
        LineSegment/LineSegementManagement.cpp
        LineSegment/LineSegementManagement.h
        Triangle/TriangleManagement.cpp
        Triangle/TriangleManagement.h
)
