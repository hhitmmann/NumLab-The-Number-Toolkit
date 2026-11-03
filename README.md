# NumLab – The Number Toolkit

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
![C++20](https://img.shields.io/badge/C%2B%2B-20-00599C.svg)
<!-- Uncomment the next line once the Actions tab shows a green build:
[![Build](https://github.com/hhitmmann/NumLab-The-Number-Toolkit/actions/workflows/build.yml/badge.svg)](https://github.com/hhitmmann/NumLab-The-Number-Toolkit/actions/workflows/build.yml)
-->

A console toolkit written in C++ for working with numbers. It starts with a calculator and is growing into a set of small tools: scientific functions, base and data-type converters, and labs for exploring overflow, precision and operators.

> **Status:** work in progress. The calculator works: you can start a calculation with a number or with an operator, and chain two operators (see [Calculator](#calculator)); the other modules are planned (see [Modules](#modules)).

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

Each round starts by asking how you want to enter the calculation:

| Choice | Mode | You type |
|--------|------|----------|
| `1` | Number first | the first number, the first operator, the second operator, then the number or numbers the second operator needs |
| `2` | Operator first | the first operator, the first number, the second operator, then the number or numbers the second operator needs |

The second operator is worked out first on the numbers you type next, and its result is combined with the first number using the first operator. The answer is shown, and in the next round it is carried over as the first number.

| Operator | Operation | Numbers it asks for (as the second operator) |
|----------|-----------|----------------------------------------------|
| `+` | Addition | one number |
| `-` | Subtraction | one number |
| `x` | Multiplication | two numbers |
| `/` | Division | two numbers |
| `^` | Power | two numbers |
| `mod` | Modulus (the result is never negative) | two numbers |
| `!` | Factorial (whole numbers, 0 to 170) | one number |
| `sqrt` | Square root | one number |
| `log` | Logarithm | one number, then a base: `2`, `t` (base 10) or `e` (natural) |
| `antilog` | Anti-logarithm | one number, then a base: `2`, `t` (base 10) or `e` (natural) |
| `abs` | Absolute value | one number |
| `sin`, `cos`, `tan` | Trigonometric functions (angle in degrees) | one number |
| `arcsin`, `arccos`, `arctan` | Inverse trigonometric functions (result in degrees) | one number |
| `sinh`, `cosh`, `tanh` | Hyperbolic functions | one number |
| `arcsinh`, `arccosh`, `arctanh` | Inverse hyperbolic functions | one number |

**What is not allowed**

`x`, `/`, `mod` and `!` need a number on their left, so they cannot be used just anywhere:

- **Operator first:** the calculation cannot start with `x`, `/`, `mod` or `!`.
- **Number first:** `x`, `/`, `mod` and `!` cannot be followed by `x`, `/`, `mod` or `!`, so `5` `x` `x` is refused. Other pairs still work, for example `5` `x` `^` `2` `3`.

A refused combination shows a "Can not…" message, no answer is calculated and the previous value is kept.

**How the two operators combine**

Here *a* is the first number, and *b* and *c* are the numbers you type next.

| First operator | Second operator | You type | Result |
|----------------|-----------------|----------|--------|
| `+` or `-` | `+` or `-` | *b* | The two signs combine: `+ +` gives a + b, `+ -` gives a − b, `- -` gives a − (−b) and `- +` gives a − b |
| `+` `-` `x` `/` `^` `mod` | a function, such as `abs`, `sqrt` or `sin` | *b* | a (first operator) f(*b*) |
| `+` `-` `^` | `x` `/` `^` `mod` | *b* and *c* | a (first operator) (*b* (second operator) *c*) |
| `x` `/` `mod` | `^` | *b* and *c* | a (first operator) (*b* ^ *c*) |
| a function | a function | *b* | first(second(*b*)). The first number is typed but not used. |

Other pairings run, but are not documented yet because the design is still changing. To apply a function on its own to a non-negative number, give `abs` as the second operator, for example `sqrt`, then `abs`, then `16`.

| You type (number first) | It calculates | Result |
|-------------------------|---------------|--------|
| `5` `+` `+` `3` | 5 + 3 | 8 |
| `5` `+` `-` `3` | 5 + (−3) | 2 |
| `5` `-` `-` `3` | 5 − (−3) | 8 |
| `5` `+` `sqrt` `9` | 5 + √9 | 8 |
| `5` `x` `abs` `3` | 5 × abs(3) | 15 |
| `5` `+` `x` `2` `3` | 5 + (2 × 3) | 11 |
| `5` `x` `^` `2` `3` | 5 × 2³ | 40 |
| `5` `sinh` `sin` `20` | sinh(sin 20°) | 0.348727379347889 |
| `5` `sqrt` `abs` `16` | sqrt(abs 16) | 4 |

Trigonometric functions work in **degrees**. The hyperbolic functions work on plain numbers, not angles. Radian and gradian modes are planned (see [Roadmap](#roadmap)). A value outside a function's domain (for example `arcsin` of 2, or `arccosh` of 0.5) reports a math error.

**Features**

- **Two ways to start:** type a number first, or an operator first (for example `+`, then `5`, then `x`, `2`, `3` gives 5 + (2 × 3)).
- **Result chaining:** the previous answer is shown as `First number (carried over)` and becomes the first number of the next round, in either mode.
- **Input checking:** an invalid number, menu choice or log base is re-requested instead of crashing the program. The continue prompt accepts `y`, `yes`, `n` or `no` in any letter case.
- **Clear messages:** problems such as the square root of a negative number, a factorial of a non-whole number or modulus by zero print an explanation.
- **Safe errors:** when an operation has no valid answer, is not allowed, or uses an operator that does not exist, a message is shown, no answer is printed and the previous value is kept, so one mistake does not spoil the rest of a calculation.
- **Cross-platform:** the console is cleared between rounds on Windows, Linux and macOS.

### Example session

The list of operators that is shown at the top of every round is left out here.

```
Enter the Choice : 1
Calculator is selected
1   ->  Enter number first
2   ->  Enter operator first
Enter your choice : 1
Enter the first number : 5
Enter Your Operator : +
Addition is selected
Enter Your 2nd Operator : sqrt
Enter the second number : 9
Answer : 3
Answer : 8
Do you want to continue with Calculations? (y/n) : y

Calculator is selected
1   ->  Enter number first
2   ->  Enter operator first
Enter your choice : 1
First number (carried over) : 8
Enter Your Operator : x
Multiplication is selected
Enter Your 2nd Operator : sqrt
Enter the second number : 16
Answer : 4
Answer : 32
Do you want to continue with Calculations? (y/n) : y

Calculator is selected
1   ->  Enter number first
2   ->  Enter operator first
Enter your choice : 1
First number (carried over) : 32
Enter Your Operator : x
Multiplication is selected
Enter Your 2nd Operator : x
Can not perform this operation at this point!
Do you want to continue with Calculations? (y/n) : n
```

The first `Answer` is the second operator's own result (√9 = 3, then √16 = 4). The second `Answer` is the final result after the first operator is applied (5 + 3 = 8, then 8 × 4 = 32). In the last round `x` followed by `x` is refused, so no answer is shown and the value stays 32.

Starting with an operator looks like this:

```
Enter your choice : 2
Enter Your Operator : +
Enter the first number : 5
Addition is selected
Enter Your 2nd Operator : x
Enter the second number : 2
Enter the 3rd number : 3
Answer : 6
Answer : 11
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

A GitHub Actions workflow (`.github/workflows/build.yml`) runs on every push to `main` and on every pull request. It builds the project on Linux, Windows and macOS, runs the unit tests once a `tests/` folder exists, and finishes with a smoke test that types `5 + + 3` in number-first mode and checks that the program prints `Answer : 8`.

## Roadmap

- Radian and gradian angle modes for the trigonometric functions (they currently work in degrees)
- Type whole expressions such as `2 + 3 * (4 - 1)`, with operator precedence and parentheses
- Report errors with exceptions and keep the maths code separate from input/output
- Memory keys (M+, M−, MR, MC), a calculation history and nicer number display
- Unit tests for every operation
- Build the remaining menu modules

## License

Released under the [MIT License](LICENSE).