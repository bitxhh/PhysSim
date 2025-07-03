cmake_minimum_required(VERSION 3.31.6)
project(Engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Engine
        main.cpp
        Engine.cpp
)
