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
#include <string>


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

        std::string op;
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
    std::cout<<"+       ->  Addition\n";
    std::cout<<"-       ->  Subtraction\n";
    std::cout<<"x       ->  Multiplication\n";
    std::cout<<"/       ->  Division\n";
    std::cout<<"^       ->  Power\n";
    std::cout<<"mod     ->  Modulus\n";
    std::cout<<"!       ->  Factorial\n";
    std::cout<<"sqrt    ->  Square root\n";
    std::cout<<"log     ->  Logarithm\n";
    std::cout<<"antilog ->  Anti-logarithm\n";
    std::cout<<"abs     ->  absolute value\n";
}

// n1 (the first number) is already set by Calculator(), so each branch only asks
// for what it still needs: the second number, or the log base.
void CalculatorChoices(std::string &op){
    if(op=="+"){
        std::cout<<"Addition is selected\n";
        if(!readNumber("Enter the second number : ", n2)) return;
        showAnswer(add(n1,n2));
    }
    else if(op=="-"){
        std::cout<<"Subtraction is selected\n";
        if(!readNumber("Enter the second number : ", n2)) return;
        showAnswer(subtract(n1,n2));
    }
    else if(op=="x"){
        std::cout<<"Multiplication is selected\n";
        if(!readNumber("Enter the second number : ", n2)) return;
        showAnswer(multiply(n1,n2));
    }
    else if(op=="/"){
        std::cout<<"Division is selected\n";
        if(!readNumber("Enter the second number : ", n2)) return;
        showAnswer(divide(n1,n2));
    }
    else if(op=="^"){
        std::cout<<"Power is selected\n";
        if(!readNumber("Enter the second number : ", n2)) return;
        showAnswer(power(n1, n2));
    }
    else if(op=="mod"){
        std::cout<<"Modulus is selected\n";
        if(!readNumber("Enter the second number : ", n2)) return;
        showAnswer(modulus(n1,n2));
    }
    else if(op=="!"){
        std::cout<<"Factorial is selected\n";
        showAnswer(factorial(n1));
    }
    else if(op=="sqrt"){
        std::cout<<"Square root is selected\n";
        showAnswer(squareRoot(n1));
    }
    else if(op=="log"){
        std::cout<<"Logarithm is selected\n";
        showAnswer(logarithm(n1));

    }
    else if(op=="antilog"){
        std::cout<<"Anti-Logarithm is selected\n";
        showAnswer(anti_logarithm(n1));
    }
    else if(op=="abs"){
        std::cout<<"Absolute value is selected\n";
        showAnswer(absolute(n1));
    }
    else if(op=="sin"){
        std::cout<<"sin function is selected\n";
        showAnswer(SIN(n1));
    }
    else if(op=="cos"){
        std::cout<<"cos function is selected\n";
        showAnswer(COS(n1));
    }
    else if(op=="tan"){
        std::cout<<"tan function is selected\n";
        showAnswer(TAN(n1));
    }
    else if(op=="arcsin"){
        std::cout<<"Inverse sin function is selected\n";
        showAnswer(ASIN(n1));
    }
    else if(op=="arccos"){
        std::cout<<"Inverse cos function is selected\n";
        showAnswer(ACOS(n1));
    }
    else if(op=="arctan"){
        std::cout<<"Inverse tan function is selected\n";
        showAnswer(ATAN(n1));
    }
    else if(op=="sinh"){
        std::cout<<"sinh function is selected\n";
        showAnswer(SINH(n1));
    }
    else if(op=="cosh"){
        std::cout<<"cosh function is selected\n";
        showAnswer(COSH(n1));
    }
    else if(op=="tanh"){
        std::cout<<"tanh function is selected\n";
        showAnswer(TANH(n1));
    }
    else if(op=="arcsinh"){
        std::cout<<"Inverse sinh function is selected\n";
        showAnswer(ATANH(n1));
    }
    else if(op=="arccosh"){
        std::cout<<"Inverse cosh function is selected\n";
        showAnswer(ACOSH(n1));
    }
    else if(op=="arctanh"){
        std::cout<<"Inverse tanh function is selected\n";
        showAnswer(ATANH(n1));
    }
    else{
        std::cout<<"Wrong operator entered!\nThis operator does not exist...\n";
    }
}