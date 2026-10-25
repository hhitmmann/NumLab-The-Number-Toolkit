# NumLab – The Number Toolkit

A console toolkit written in C++ for working with numbers. It starts with a calculator and is growing into a set of small tools: scientific functions, base and data-type converters, and labs for exploring overflow, precision and operators.

> **Status:** work in progress. The calculator works; the other modules are planned (see [Modules](#modules)).

## Modules

The program opens on a main menu:

| Menu | Module | Status |
|------|--------|--------|
| 1 | Calculator | Working |
| 2 | Scientific Functions | Planned |
| 3 | Base Converter | Planned: convert numbers between bases |
| 4 | Data Type Converter | Planned: see how values convert between C++ data types |
| 5 | Overflow & Precision Lab | Planned: experiment with integer overflow and floating-point precision |
| 6 | Operator Lab | Planned: explore how C++ operators behave |
| 0 | Exit | Working |

## Calculator

Enter a first number, choose an operator, and enter a second number if the operator needs one. The answer is shown, and you can carry on with it as the next first number.

| Operator | Operation | Asks for |
|----------|-----------|----------|
| `+` | Addition | second number |
| `-` | Subtraction | second number |
| `x` | Multiplication | second number |
| `/` | Division | second number |
| `^` | Power | second number |
| `mod` | Modulus (the result is never negative) | second number |
| `!` | Factorial (whole numbers, 0 to 170) | nothing |
| `sqrt` | Square root | nothing |
| `log` | Logarithm | a base: `2`, `t` (base 10) or `e` (natural) |
| `antilog` | Anti-logarithm | a base: `2`, `t` (base 10) or `e` (natural) |
| `abs` | Absolute value | nothing |

The names `sin`, `cos`, `tan`, `arcsin`, `arccos`, `arctan` and the hyperbolic versions are reserved for the upcoming trigonometry support and are **not implemented yet**.

**Features**

- **Result chaining:** the previous answer is shown as `First number (carried over)` and becomes the next first number.
- **Input checking:** an invalid number or menu choice is re-requested instead of crashing the program.
- **Clear messages:** problems such as the square root of a negative number, a factorial of a non-whole number or modulus by zero print an explanation.
- **Cross-platform:** the console is cleared between rounds on Windows, Linux and macOS.

### Example session

```
Enter the Choice : 1
Calculator is selected
Enter the first number : 5
Enter Your Operator : +
Addition is selected
Enter the second number : 3
Answer : 8
Do you want to continue with Calculations? (y/n) : y

First number (carried over) : 8
Enter Your Operator : x
Multiplication is selected
Enter the second number : 2
Answer : 16
Do you want to continue with Calculations? (y/n) : n
```

## Project structure

```
NumLab-The-Number-Toolkit/
├── apps/
│   └── main.cpp              # entry point: the main menu loop
├── include/Project1/         # headers, one per module plus shared helpers
│   ├── Calculator.h
│   ├── MathOps.h
│   ├── UI_Choices.h
│   ├── ClearScreen.h
│   └── ...
├── src/
│   ├── Calculator.cpp        # calculator loop and operator handling
│   ├── MathOps.cpp           # the math functions (power, factorial, log, ...)
│   ├── UI_Choices.cpp        # main menu and input helpers
│   ├── ClearScreen.cpp       # clears the console on Windows and Linux/macOS
│   └── ...                   # the other modules (in progress)
├── CMakeLists.txt
└── .clang-format
```

## Build and run

**Requirements:** a C++17 compiler (g++, clang or MSVC) and CMake 3.20 or newer.

```
cmake -S . -B build
cmake --build build
```

Then run the program:

- Linux / macOS: `./build/calclab_app`
- Windows: `build\calclab_app.exe` (with the Visual Studio generator it is in `build\Debug\`)

**Without CMake** (g++ on Linux, macOS, or Git Bash on Windows):

```
g++ -std=c++17 -Iinclude src/*.cpp apps/main.cpp -o numlab
./numlab
```

## Roadmap

- Trigonometric and hyperbolic functions with degree, radian and gradian modes
- Type whole expressions such as `2 + 3 * (4 - 1)`, with operator precedence and parentheses
- Report errors with exceptions and keep the maths code separate from input/output
- Unit tests for every operation
- Build the remaining menu modules