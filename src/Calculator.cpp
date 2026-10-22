#include "Project1/Calculator.h"
#include "Project1/UI_Choices.h"
#include "Project1/ClearScreen.h"
#include "Project1/MathOps.h"
#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
#include <cctype>
#include <string>
#include <algorithm>


static bool readNumber(const char* prompt, double& out);
static void showAnswer(double value);

double n1{}, n2{}, memory{}; // Global variables to store numbers and memory

void Calculator(){
    std::cout << std::setprecision(15);
    bool FirstLoop = true;
    do{
        ClearScreen();
        CalculatorUI();

        // memory is the "current value": typed in on the first round,
        // the previous answer on every round after that.
        if(FirstLoop){
            if(!readNumber("Enter the first number : ", memory)) return;
            FirstLoop = false;
        }
        else{
            std::cout<<"First number (carried over) : "<<memory<<"\n";
        }
        n1 = memory;

        char op;
        std::cout<<"Enter Your Operator : ";
        if(!(std::cin>>op)) return;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        CalculatorChoices(op);   // asks only for what is still missing, prints "Answer" on success
    }
    while(askYesNo("Do you want to continue with Calculations? (y/n) : "));
}

void CalculatorUI(){
    std::cout<<"Calculator is selected\n";
    std::cout<<"Following are the operators you can use :\n";
    std::cout<<"+ -> Addition\n";
    std::cout<<"- -> Subtraction\n";
    std::cout<<"* -> Multiplication\n";
    std::cout<<"/ -> Division\n";
    std::cout<<"^ -> Power\n";
    std::cout<<"% -> Modulus\n";
    std::cout<<"! -> Factorial\n";
    std::cout<<"s -> Square root\n";
    std::cout<<"l -> Logarithm\n";
    std::cout<<"a -> Anti-logarithm\n";
    std::cout<<"v -> absolute value\n";
}

// n1 (the first number) is already set by Calculator(), so each branch only asks
// for what it still needs: the second number, or the log base.
void CalculatorChoices(char &op){
    if(op=='+'){
        std::cout<<"Addition is selected\n";
        if(!readNumber("Enter the second number : ", n2)) return;
        showAnswer(add(n1,n2));
    }
    else if(op=='-'){
        std::cout<<"Subtraction is selected\n";
        if(!readNumber("Enter the second number : ", n2)) return;
        showAnswer(subtract(n1,n2));
    }
    else if(op=='*'){
        std::cout<<"Multiplication is selected\n";
        if(!readNumber("Enter the second number : ", n2)) return;
        showAnswer(multiply(n1,n2));
    }
    else if(op=='/'){
        std::cout<<"Division is selected\n";
        if(!readNumber("Enter the second number : ", n2)) return;
        showAnswer(divide(n1,n2));
    }
    else if(op=='^'){
        std::cout<<"Power is selected\n";
        if(!readNumber("Enter the second number : ", n2)) return;
        showAnswer(power(n1, n2));
    }
    else if(op=='%'){
        std::cout<<"Modulus is selected\n";
        if(!readNumber("Enter the second number : ", n2)) return;
        showAnswer(modulus(n1,n2));
    }
    else if(op=='!'){
        std::cout<<"Factorial is selected\n";
        showAnswer(factorial(n1));
    }
    else if(op=='s'){
        std::cout<<"Square root is selected\n";
        showAnswer(squareRoot(n1));
    }
    else if(op=='l'){
        std::cout<<"Logarithm is selected\n";
        logarithm(n1);
    }
    else if(op=='a'){
        std::cout<<"Anti-Logarithm is selected\n";
        anti_logarithm(n1);
    }
    else if(op=='v'){
        std::cout<<"Absolute value is selected\n";
        showAnswer(absolute(n1));
    }
    else{
        std::cout<<"Wrong operator entered!\nThis operator does not exist...\n";
    }
}