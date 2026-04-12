cmake_minimum_required(VERSION 3.28)
project(PhysSim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.0.1
    GIT_SHALLOW    TRUE
)
set(BUILD_SHARED_LIBS OFF)
FetchContent_MakeAvailable(SFML)

add_executable(Simulation
    "simulation/tests/tests.cpp"
    "simulation/src/core/particle.cpp"
    "simulation/src/core/particle_system.cpp"
    "simulation/src/render/sfml_x.cpp"
    "simulation/src/Application.cpp"
    "simulation/src/render/render_system.cpp"
)

target_include_directories(Simulation PRIVATE "simulation/include")

target_link_libraries(Simulation PRIVATE SFML::Graphics SFML::Window SFML::System)
