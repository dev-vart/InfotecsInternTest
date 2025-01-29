cmake_minimum_required(VERSION 3.22.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Program_1)

include_directories(src)

set(SOURCES
    src/main.cpp
    src/server.cpp
    src/inputhandler.cpp
    src/bufferprocessor.cpp
)

set(HEADERS
    src/safebuffer.h
    src/server.h
    src/inputhandler.h
    src/bufferprocessor.h
)

add_executable(Program_1 ${SOURCES} ${HEADERS})
