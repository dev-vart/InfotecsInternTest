cmake_minimum_required(VERSION 3.22.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Program_2)

include_directories(source)

set(SOURCES
    src/main.cpp
    src/client.cpp
    src/receivehandler.cpp
)

set(HEADERS
    src/client.h
    src/receivehandler.h
)

add_executable(Program_2 ${SOURCES} ${HEADERS})
