# Discrete Events Simulator

The **Discrete Events Simulator** implements a Discrete Events Simulator (DES) in C++, designed to simulate and analyze scheduling algorithms. It provides a flexible framework to model tasks and explore different scheduling strategies.

## Project Structure

```bash
.
├── includes        # Header files for Tasks and Schedulers
│   ├── schedulers  # Scheduler-specific headers (EDF, RoundRobin, SJF...)
│   └── Tasks.hpp   # Header for Task class
├── src             # Source files for implementation
│   ├── main.cpp    # Entry point of the simulator
│   ├── Tasks.cpp   # Implementation of Task class
│   └── schedulers  # Scheduler implementations
├── examples        # Example YAML files for tasks
├── tests           # Test cases for Schedulers
│   ├── SchedulersTests.cpp # Test suite for Scheduler algorithms
│   └── tasks       # YAML files used in tests
├── build           # Build directory containing compiled binaries and build artifacts
├── .clang-format   # Clang-format configuration for code style consistency
└── CMakeLists.txt  # CMake configuration file
```

## Requirements

Before building the project, ensure you have the following dependencies installed:

- **CMake** (version 3.10 or higher)
- **C++17** compatible compiler
- **yaml-cpp**: 
  - Install via package manager or compile from source [yaml-cpp GitHub](https://github.com/jbeder/yaml-cpp)
- **GoogleTest**: 
  - Install via package manager or compile from source [GoogleTest GitHub](https://github.com/google/googletest)

## Building the Project

Follow these steps to build the project:

1. **Clone the repository:**

    ```sh
    git clone <repository-url>
    cd <repository-name>
    ```

2. **Create and navigate to the build directory:**

    ```sh
    mkdir build
    cd build
    ```

3. **Run CMake to configure and build the project:**

    ```sh
    cmake ..
    make
    ```

4. **Run the executable:**

    ```sh
    ./discrete-events-simulator
    ```

## Running Tests

To ensure the correctness of the scheduling algorithms, you can run the test suite inside the build folder:

```sh
ctest
```

## Code Formatting

To maintain a consistent code style across the project, use `clang-format`:

```sh
find src includes tests -name "*.cpp" -o -name "*.hpp" | xargs clang-format -i
```

This will automatically format all `.cpp` and `.hpp` files according to the style specified in `.clang-format`.

## Examples

Explore the example task configurations in the `examples` directory. These YAML files can be used to test different scheduling strategies:

- `tasks1.yml`, `tasks2.yml`, `tasks3.yml`: Different task configurations for various scheduling scenarios.

---