# Win32 Calculator

This is a simple calculator application for Windows, built with C++17 and the raw Win32 API. It does not use any external libraries.

## Features

- Basic arithmetic operations: addition, subtraction, multiplication, and division.
- A simple and intuitive graphical user interface.
- No external dependencies other than a C++17 compiler and the Windows SDK.

## Building the Project

To build the project, you will need a MinGW-w64 C++ compiler.

### Using `make`

If you have `make` installed, you can build the project by running the following command in the root directory of the project:

```sh
make
```

This will create the `calculator.exe` executable in the root directory.

### Manual Compilation

If you don't have `make`, you can compile the project manually using the following command:

```sh
x86_64-w64-mingw32-g++ -std=c++17 src/main.cpp -o calculator.exe -lgdi32 -luser32
```

## Running the Calculator

After building the project, you can run the calculator by executing the `calculator.exe` file.

```sh
./calculator.exe
```

## Cleaning the Build

To clean the build artifacts, you can use the following command if you have `make`:

```sh
make clean
```
