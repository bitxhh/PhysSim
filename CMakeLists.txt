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

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(nlohmann_json)

# ── Общие источники (без SFML-зависимостей) ────────────────────────────────
set(PHYSSIM_CORE_SOURCES
    "simulation/src/config.cpp"
    "simulation/src/core/particle.cpp"
    "simulation/src/core/particle_system.cpp"
    "simulation/src/integrators/euler.cpp"
    "simulation/src/integrators/verlet.cpp"
    "simulation/src/scenarios/billiards.cpp"
    "simulation/src/scenarios/solar_system.cpp"
    "simulation/src/forces/global_gravity.cpp"
    "simulation/src/forces/pair_gravity.cpp"
    "simulation/src/forces/linear_damping.cpp"
    "simulation/src/collisions/box_constraint.cpp"
    "simulation/src/collisions/brute_force_collision.cpp"
    "simulation/src/simulation_runner.cpp"
)

# ── Основное приложение ────────────────────────────────────────────────────
add_executable(Simulation
    "simulation/src/main.cpp"
    "simulation/src/render/sfml_backend.cpp"
    "simulation/src/Application.cpp"
    ${PHYSSIM_CORE_SOURCES}
)

target_include_directories(Simulation PRIVATE "simulation/include")
target_link_libraries(Simulation PRIVATE SFML::Graphics SFML::Window SFML::System nlohmann_json::nlohmann_json)

# ── Тесты ──────────────────────────────────────────────────────────────────
add_executable(PhysSimTests
    "simulation/tests/test_physics.cpp"
    ${PHYSSIM_CORE_SOURCES}
)

target_include_directories(PhysSimTests PRIVATE "simulation/include")
target_link_libraries(PhysSimTests PRIVATE nlohmann_json::nlohmann_json)

enable_testing()
add_test(NAME PhysicsTests COMMAND PhysSimTests)
