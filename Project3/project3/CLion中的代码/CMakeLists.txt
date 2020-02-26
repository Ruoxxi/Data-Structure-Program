cmake_minimum_required(VERSION 3.15)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES
        CoorTrans.h
        CoorTrans.cpp
        test.cpp
        CreateHeap.h
        CreateGraph1.h
        Graph1.h
        Dijkstra.cpp)

add_executable(untitled main.cpp ${SOURCE_FILED} ${SOURCES} CreateHeap.h CreateGraph1.h Dijkstra.cpp Graph1.h switch.cpp)