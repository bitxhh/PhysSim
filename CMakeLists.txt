cmake_minimum_required(VERSION 3.31.6)
project(PHISICS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SFML_DIR "/opt/homebrew/Cellar/sfml/3.0.1/lib/cmake/SFML")

find_package(SFML 3.0.1 REQUIRED COMPONENTS Graphics Window System)


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
        "Моделирование/src/visualize.cpp"
)

target_link_libraries(classes PRIVATE SFML::Graphics SFML::Window SFML::System)