# NumLab – The Number Toolkit

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
![C++20](https://img.shields.io/badge/C%2B%2B-20-00599C.svg)
<!-- Uncomment the next line once the Actions tab shows a green build:
[![Build](https://github.com/hhitmmann/NumLab-The-Number-Toolkit/actions/workflows/build.yml/badge.svg)](https://github.com/hhitmmann/NumLab-The-Number-Toolkit/actions/workflows/build.yml)
-->

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
| `sin`, `cos`, `tan` | Trigonometric functions (angle in degrees) | nothing |
| `arcsin`, `arccos`, `arctan` | Inverse trigonometric functions (result in degrees) | nothing |
| `sinh`, `cosh`, `tanh` | Hyperbolic functions | nothing |
| `arcsinh`, `arccosh`, `arctanh` | Inverse hyperbolic functions | nothing |

Trigonometric functions work in **degrees**. The hyperbolic functions work on plain numbers, not angles. Radian and gradian modes are planned (see [Roadmap](#roadmap)). A value outside a function's domain (for example `arcsin` of 2, or `arccosh` of 0.5) reports a math error.

**Features**

- **Result chaining:** the previous answer is shown as `First number (carried over)` and becomes the next first number.
- **Input checking:** an invalid number, menu choice or log base is re-requested instead of crashing the program. The continue prompt accepts `y`, `yes`, `n` or `no` in any letter case.
- **Clear messages:** problems such as the square root of a negative number, a factorial of a non-whole number or modulus by zero print an explanation.
- **Safe errors:** when an operation has no valid answer, a math error is shown and the previous value is kept, so one mistake does not spoil the rest of a calculation.
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
├── .github/workflows/
│   └── build.yml                 # builds on Linux, Windows and macOS for every push
├── apps/
│   └── main.cpp                  # entry point: the main menu loop
├── include/numlab/               # headers: one folder per module
│   ├── Calculator/               # Calculator.h, MathOps.h
│   ├── UI/                       # UI_Choices.h, ClearScreen.h
│   ├── base_converter/
│   ├── data_type/
│   ├── operator_lab/
│   ├── Overflow_Precision/
│   └── Scientific_Function/
├── src/                          # implementations: the same folders as include/numlab/
│   ├── Calculator/
│   │   ├── Calculator.cpp        # calculator loop and operator handling
│   │   └── MathOps.cpp           # the math functions (power, factorial, log, trigonometry, ...)
│   ├── UI/
│   │   ├── UI_Choices.cpp        # main menu and input helpers
│   │   └── ClearScreen.cpp       # clears the console on Windows and Linux/macOS
│   └── ...                       # the other modules (in progress)
├── CMakeLists.txt
├── LICENSE
├── .clang-format
├── .editorconfig
├── .gitattributes
└── .gitignore
```

Each module has its own folder under `include/numlab/` and `src/`, and headers are included with their folder, for example `#include "numlab/Calculator/Calculator.h"`. When you add a source file, list it in `CMakeLists.txt`.

`CMakeLists.txt` builds everything except `main()` into a static library, `numlab_core`, and links the `numlab` executable against it. That keeps the code reusable for unit tests: a `tests/CMakeLists.txt` file is picked up automatically once it exists.

## Build and run

**Requirements:** a C++20 compiler (g++ 10 or newer, a recent clang, or MSVC 2019 16.5 or newer) and CMake 3.20 or newer.

```
cmake -S . -B build
cmake --build build
```

Then run the program:

- Linux / macOS: `./build/numlab`
- Windows: `build\numlab.exe` (with the Visual Studio generator it is in `build\Debug\`)

**Without CMake** (g++ on Linux, macOS, or Git Bash on Windows):

```
g++ -std=c++20 -Iinclude src/*/*.cpp apps/main.cpp -o numlab
./numlab
```

A GitHub Actions workflow (`.github/workflows/build.yml`) runs on every push to `main` and on every pull request. It builds the project on Linux, Windows and macOS, runs the unit tests once a `tests/` folder exists, and finishes with a smoke test that feeds `5 + 3` to the program and checks that it prints `Answer : 8`.

## Roadmap

- Radian and gradian angle modes for the trigonometric functions (they currently work in degrees)
- Type whole expressions such as `2 + 3 * (4 - 1)`, with operator precedence and parentheses
- Report errors with exceptions and keep the maths code separate from input/output
- Memory keys (M+, M−, MR, MC), a calculation history and nicer number display
- Unit tests for every operation
- Build the remaining menu modules

## License

Released under the [MIT License](LICENSE).