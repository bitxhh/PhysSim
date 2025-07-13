cmake_minimum_required(VERSION 3.31.6)
project(Engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Основная программа Engine
add_executable(Engine
        "Всякая хуйня/Что-то о физических библиотеках/tests.cpp"
        "Всякая хуйня/Что-то о физических библиотеках/Engine.cpp"
)

# Отдельный исполняемый файл для калькулятора
add_executable(Calculator
        "Всякая хуйня/Calculator_/Calculator.cpp"

)

# Отдельный исполняемый файл для swap
add_executable(Swap
       "Всякая хуйня/Swap/swapS.cpp"
)
add_executable(classes
        "Моделирование/tests/tests.cpp"
        "Моделирование/src/particle.cpp"
        "Моделирование/src/particle_system.cpp"
)
