cmake_minimum_required(VERSION 3.31.6)
project(Engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа Engine
add_executable(Engine
        main.cpp
        Engine.cpp
        Engine.h
)

# Отдельный исполняемый файл для калькулятора
add_executable(Calculator
        Calculator_/Calculator.cpp
)

# Отдельный исполняемый файл для swap
add_executable(Swap
       Swap/swapS.cpp
)