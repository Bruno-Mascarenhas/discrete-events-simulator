# Discrete Events Simulator

The **Discrete Events Simulator** implements a Discrete Events Simulator (DES) in C++, designed to simulate and analyze scheduling algorithms. It provides a flexible framework to model tasks and explore different scheduling strategies.

## Project Structure

```bash
.
├── build                   # Build directory containing compiled binaries and build artifacts
├── CMakeLists.txt          # CMake configuration file
├── examples                # Example YAML files for tasks
│   └── tasks.yml
├── includes                # Header files for Tasks and Schedulers
├── outputs                 # Directory for output YAML files and Gantt charts
│   └── FIFO_completed_tasks.yaml
├── README.md               # Project documentation
├── run_pipeline.sh         # Shell script to run the C++ executable and Python script
├── src                     # Source files for implementation
└── tests                   # Test cases for Schedulers
    ├── SchedulersTests.cpp
    └── tasks                # YAML files used in tests
        └── tasks.yml
```

## Requirements

Before building the project, ensure you have the following dependencies installed:

- **CMake** (version 3.10 or higher)
- **C++17** compatible compiler
- **yaml-cpp**: 
  - Install via package manager or compile from source [yaml-cpp](https://github.com/jbeder/yaml-cpp)
- **GoogleTest**: 
  - Install via package manager or compile from source [GoogleTest](https://github.com/google/googletest)

### Python Package Requirements

To run the Python script for generating Gantt charts, install the following Python packages:

```sh
pip install matplotlib pyyaml
```

## Building the Project

Follow these steps to build the project:

1. **Clone the repository:**

    ```sh
    git clone <repository-url>
    cd <repository-name>
    ```

2. **Create, navigate, configure, and build the project:**

    ```sh
    mkdir build
    cd build
    cmake .. && make
    ```

3. **Run the executable:**

    ```sh
    ./discrete-events-simulator {"fifo" | "sjf" | "edf" | "robin" | "hpf" | "all"}
    ```

## Running Tests

To ensure the correctness of the scheduling algorithms, you can run the test suite inside the build folder:

```sh
ctest --verbose
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

## Generating Gantt Charts

The `run_pipeline.sh` script runs the C++ executable to generate YAML files and then uses a Python script to create Gantt charts for each YAML file. Ensure the `outputs` directory is present and set up as needed.

--- 
