cmake_minimum_required(VERSION 3.31.6)
project(Engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа Engine
add_executable(Engine
        "Что-то о физических библиотеках/tests.cpp"
        "Что-то о физических библиотеках/Engine.cpp"
)

# Отдельный исполняемый файл для калькулятора
add_executable(Calculator
        Calculator_/Calculator.cpp

)

# Отдельный исполняемый файл для swap
add_executable(Swap
       Swap/swapS.cpp
)
add_executable(classes
        "Тестовые классы/tests.cpp"
        "Тестовые классы/particle.cpp"
)