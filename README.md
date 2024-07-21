# Discrete Events Simulator

This project is a Discrete Events Simulator. The project structure is as follows:

```
.
├── includes        # Header files
├── src             # Source files
│   ├── main.cpp
│   ├── tasks.cpp
│   └── schedulers.cpp
├── .clang-format   # Clang-format configuration file
└── CMakeLists.txt  # CMake configuration file
```

## Requirements

- CMake (version 3.10 or higher)
- A C++17 compatible compiler

## Building the Project

1. **Clone the repository:**

    ```sh
    git clone <repository-url>
    cd <repository-name>
    ```

2. **Create a build directory:**

    ```sh
    mkdir build
    cd build
    ```

3. **Run CMake to configure the project:**

    ```sh
    cmake ..
    ```

4. **Build the project:**

    ```sh
    make
    ```

5. **Run the executable:**

    ```sh
    ./discrete-events-simulator
    ```

## Formatting the Code

The project uses `clang-format` to ensure consistent coding style. You can format the code using the provided `.clang-format` file.

To format the code, run:

```sh
clang-format -i src/*.cpp includes/*.h
```
