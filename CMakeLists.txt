cmake_minimum_required(VERSION 3.28)
project(PhysicsEngine LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

include(FetchContent)
FetchContent_Declare(3DEngine
        GIT_REPOSITORY https://github.com/Maks92384/3DEngine.git
        GIT_TAG main
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(3DEngine)

add_executable(main src/main.cpp
        src/events.cpp
        src/events.hpp
        src/configuration.hpp
        src/PhysicsEngine/Core/PhysicsEngine.cpp
        src/PhysicsEngine/Core/PhysicsEngine.hpp
        src/PhysicsEngine/Object/PhysicsObject.cpp
        src/PhysicsEngine/Object/PhysicsObject.hpp
        src/PhysicsEngine/Configuration/PhysicsEngineConfiguration.hpp
        src/PhysicsEngine/Display/Engine3DIntegration.cpp
        src/PhysicsEngine/Display/Engine3DIntegration.hpp
        src/PhysicsEngine/Constraints/Constraints.cpp
        src/PhysicsEngine/Constraints/Constraints.hpp
        src/PhysicsEngine/Constraints/ConstraintTemplate.cpp
        src/PhysicsEngine/Constraints/ConstraintTemplate.hpp
        src/PhysicsEngine/Constraints/PlaneConstraint.cpp
        src/PhysicsEngine/Constraints/PlaneConstraint.hpp
        src/PhysicsEngine/Math/Quaternion.cpp
        src/PhysicsEngine/Math/Quaternion.hpp
        src/PhysicsEngine/Constraints/PointConstraint.cpp
        src/PhysicsEngine/Constraints/PointConstraint.hpp
)

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
target_link_libraries(main PRIVATE 3DEngine)