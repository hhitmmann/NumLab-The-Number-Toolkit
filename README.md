# C++ Console Calculator

A command-line calculator written in C++. It takes a first number, an operator, and (when needed) a second number, then shows the answer. After each calculation you can continue, and the previous answer carries over as the next first number.

## Features

| Operator | Operation | Needs |
|----------|-----------|-------|
| `+` | Addition | second number |
| `-` | Subtraction | second number |
| `*` | Multiplication | second number |
| `/` | Division (shows `inf` / `-inf` / `nan` for division by zero) | second number |
| `^` | Power | second number |
| `%` | Modulus (result is never negative) | second number |
| `!` | Factorial (whole numbers 0 to 170) | nothing extra |
| `s` | Square root | nothing extra |
| `l` | Logarithm: base 2, base 10 or natural (`2` / `t` / `e`) | log base |
| `a` | Anti-logarithm: base 2, base 10 or e (`2` / `t` / `e`) | base |
| `v` | Absolute value | nothing extra |

- **Result chaining:** the previous answer is shown as `First number (carried over)` and used as the next first number.
- **Input checking:** invalid numbers are re-requested, and errors such as square root of a negative or modulus by zero are reported clearly.
- **Clean screen:** the console is cleared between calculations.

## How it works

1. Enter the first number (first round only).
2. Enter an operator from the list.
3. Enter the second number, or the log base, if the operator needs one.
4. The answer is printed.
5. Choose `y` to continue with the answer carried over, or `n` to stop.

### Example session

```
Enter the first number : 5
Enter Your Operator : +
Addition is selected
Enter the second number : 3
Answer : 8
Do you want to continue with Calculations? (y/n) : y

First number (carried over) : 8
Enter Your Operator : *
Multiplication is selected
Enter the second number : 2
Answer : 16
```

## Project structure

```
Project1/
├── Calculator.cpp    # calculator logic and input handling
├── Calculator.h      # Calculator(), CalculatorUI(), CalculatorChoices()
└── ClearScreen.h     # console-clearing helper
```

## Build and run

Compile all the project's `.cpp` files together with a C++11 or newer compiler, for example:

```
g++ -std=c++17 -Wall -Wextra *.cpp -o calculator
./calculator
```

(On Windows, run `calculator.exe`.) Adjust the paths to match your folder layout and IDE.

## Possible improvements

- Add trigonometric functions.
- Let the user reset the carried-over value to start a fresh calculation.
- Add unit tests for each operator.
