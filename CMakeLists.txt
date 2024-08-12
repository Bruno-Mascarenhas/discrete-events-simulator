cmake_minimum_required(VERSION 3.10)

# Project name
project(discrete-events-simulator)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find yaml-cpp package
find_package(yaml-cpp REQUIRED)

# Find GoogleTest package
find_package(GTest REQUIRED)

# Include directories
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${YAML_CPP_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/includes)

# Source files for main executable
set(MAIN_SOURCES
    src/main.cpp
    src/Tasks.cpp
    src/schedulers/EDF.cpp
    src/schedulers/SJF.cpp
    src/schedulers/FIFO.cpp
    src/schedulers/RoundRobin.cpp
    src/schedulers/BaseScheduler.cpp
)

# Add main executable
add_executable(discrete-events-simulator ${MAIN_SOURCES})

# Link yaml-cpp library to main executable
target_link_libraries(discrete-events-simulator yaml-cpp)

# Enable testing
enable_testing()

# Source files for test executable
set(TEST_SOURCES
    tests/SchedulersTests.cpp
    src/Tasks.cpp
    src/schedulers/EDF.cpp
    src/schedulers/SJF.cpp
    src/schedulers/FIFO.cpp
    src/schedulers/RoundRobin.cpp
    src/schedulers/BaseScheduler.cpp
)

# Add test executable
add_executable(schedulers_tests ${TEST_SOURCES})

# Link libraries to test executable
target_link_libraries(schedulers_tests ${GTEST_LIBRARIES} pthread yaml-cpp)

# Add tests
add_test(NAME SchedulersTests COMMAND schedulers_tests)
