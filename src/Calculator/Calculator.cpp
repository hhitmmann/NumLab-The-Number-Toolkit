#include "numlab/Calculator/Calculator.h"
#include "numlab/UI/UI_Choices.h"
#include "numlab/UI/ClearScreen.h"
#include "numlab/Calculator/MathOps.h"
#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
#include <string>


double memory{};                    // current value; UI_Choices.cpp uses it too, so it can not be static
static double n1{}, n2{}, n3{};     // first, second and third numbers
static bool firstrun = true;
static bool choice_selected = false;
static std::string op1, op2, choice;
static bool readOp2();
static bool nestedFailed();

void Calculator(){
    std::cout << std::setprecision(15);
    bool FirstLoop = true;
    do{
        ClearScreen();
        CalculatorUI();

        // memory is the "current value": typed in on the first round,
        // the previous answer on every round after that.
        std::cout<<"1   ->  Enter number first\n";
        std::cout<<"2   ->  Enter operator first\n";
        std::cout<<"Enter your choice : ";
        if(!(std::cin>>choice)) return;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if(choice=="1"){
            choice_selected = true;
            if(FirstLoop){
                if(!readNumber("Enter the first number : ", memory)) return;
                FirstLoop = false;
            }
            else{
                std::cout<<"First number (carried over) : "<<memory<<"\n";
            }
            n1 = memory;
            std::cout<<"Enter Your Operator : ";
            if(!(std::cin>>op1)) return;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            CalculatorChoices(op1);
            if(!std::isfinite(memory)) memory = n1;   // a failed calculation keeps the old value 
        }
        else if(choice=="2"){
            choice_selected = false;
            std::cout<<"Enter Your Operator : ";
            if(!(std::cin>>op1)) return;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if(FirstLoop){
                if(!readNumber("Enter the first number : ", memory)) return;
                FirstLoop = false;
            }
            else{
                std::cout<<"First number (carried over) : "<<memory<<"\n";
            }
            n1 = memory;
            CalculatorChoices(op1);
            if(!std::isfinite(memory)) memory = n1;   // a failed calculation keeps the old value
        }
        else{
            std::cout<<"Invalid Choice! Try again.\n";
            continue;
        }
    }
    while(askYesNo("Do you want to continue with Calculations? (y/n) : "));
}

void CalculatorUI(){
    std::cout<<"Calculator is selected\n";
    std::cout<<"Following are the operators you can use :\n";
    std::cout<<"+           ->  Addition\n";
    std::cout<<"-           ->  Subtraction\n";
    std::cout<<"x           ->  Multiplication\n";
    std::cout<<"/           ->  Division\n";
    std::cout<<"^           ->  Power\n";
    std::cout<<"mod         ->  Modulus\n";
    std::cout<<"!           ->  Factorial\n";
    std::cout<<"sqrt        ->  Square root\n";
    std::cout<<"log         ->  Logarithm\n";
    std::cout<<"antilog     ->  Anti-logarithm\n";
    std::cout<<"abs         ->  absolute value\n";
    std::cout<<"sin         ->  sin\n";
    std::cout<<"cos         ->  cos\n";
    std::cout<<"tan         ->  tan\n";
    std::cout<<"arcsin      ->  arcsin\n";
    std::cout<<"arccos      ->  arccos\n";
    std::cout<<"arctan      ->  arctan\n";
    std::cout<<"sinh        ->  sinh\n";
    std::cout<<"cosh        ->  cosh\n";
    std::cout<<"tanh        ->  tanh\n";
    std::cout<<"arcsinh     ->  arcsinh\n";
    std::cout<<"arccosh     ->  arccosh\n";
    std::cout<<"arctanh     ->  arctanh\n";
}

// n1 (the first number) is already set by Calculator(), so each branch only asks
// for what it still needs: the second number, or the log base.

void CalculatorChoices(std::string &op){
    if(op=="+"){
        if(firstrun){
            firstrun = false;
            std::cout<<"Addition is selected\n";
            if(!readOp2()) return;
            choice_selected = true;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            if(op1=="+" && op2=="+"){
            }
            else if(op1=="+" && op2=="-"){ 
            }
            else{
                memory = add(n1,memory);
            }
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            if(op1=="-"){
                memory = subtract(n1,n2);
            }
            else{
                memory = add(n1,n2);
            }
            showAnswer(memory); 
        }
    }
    else if(op=="-"){
       if(firstrun){
            firstrun = false;
            std::cout<<"Subtraction is selected\n";
            if(!readOp2()) return;
            choice_selected = true;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            if(op1=="-" && op2=="-"){
            }
            else if(op1=="-" && op2=="+"){ 
            }
            else{
                memory = subtract(n1,memory);
            }
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            if(op1=="-" && op2 == "-"){
                memory = add(n1,n2);
            }
            else{
                memory = subtract(n1,n2);
            }
            showAnswer(memory);
        }
    }
    else if(op=="x"){
        if(choice_selected){
            if(firstrun){
                firstrun = false;
                std::cout<<"Multiplication is selected\n";
                if(!readOp2()) return;
                if((op1=="x" && op2=="x") || (op1=="x" && op2=="/") || (op1=="x" && op2=="!") || (op1=="x" && op2=="mod")){
                    choice_selected = false;
                }
                else{
                    choice_selected = true;
                }
                CalculatorChoices(op2);
                if(nestedFailed()) return;
                memory = multiply(n1,memory);
                showAnswer(memory);
                choice_selected = false;
            }
            else{
                firstrun = true;
                if(!readNumber("Enter the second number : ", n2)) return;
                if(!readNumber("Enter the 3rd number : ", n3)) return;
                memory = multiply(n2,n3);
                showAnswer(memory);
            }
        }
        else{
            std::cout<<"Can not perform this operation at this point!\n";
        }
        
    }
    else if(op=="/"){
        if(choice_selected){
            if(firstrun){
                firstrun = false;
                std::cout<<"Division is selected\n";
                if(!readOp2()) return;
                if((op1=="/" && op2=="x") || (op1=="/" && op2=="/") || (op1=="/" && op2=="!") || (op1=="/" && op2=="mod")){
                    choice_selected = false;
                }
                else{
                    choice_selected = true;
                }
                CalculatorChoices(op2);
                if(nestedFailed()) return;
                memory = divide(n1,memory);
                showAnswer(memory);
                choice_selected = false;
            }
            else{
                firstrun = true;
                if(!readNumber("Enter the second number : ", n2)) return;
                if(!readNumber("Enter the 3rd number : ", n3)) return;
                memory = divide(n2,n3);
                showAnswer(memory);
            }
        }
        else{
            std::cout<<"Can not use Division at start!\n";
        }
        
    }
    else if(op=="^"){
        if(firstrun){
            firstrun = false;
            std::cout<<"power is selected\n";
            if(!readOp2()) return;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            memory = power(n1,memory);
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            if(!readNumber("Enter the 3rd number : ", n3)) return;
            memory = power(n2,n3);
            showAnswer(memory);
        }
    }
    else if(op=="mod"){
        if(choice_selected){
            if(firstrun){
                firstrun = false;
                std::cout<<"modulus is selected\n";
                if(!readOp2()) return;
                if((op1=="mod" && op2=="x") || (op1=="mod" && op2=="/") || (op1=="mod" && op2=="!") || (op1=="mod" && op2=="mod")){
                    choice_selected = false;
                }
                else{
                    choice_selected = true;
                }
                CalculatorChoices(op2);
                if(nestedFailed()) return;
                memory = modulus(n1,memory);
                showAnswer(memory);
                choice_selected = false;
            }
            else{
                firstrun = true;
                if(!readNumber("Enter the second number : ", n2)) return;
                if(!readNumber("Enter the 3rd number : ", n3)) return;
                memory = modulus(n2,n3);
                showAnswer(memory);
            }
        }
        else{
            std::cout<<"Can not use modulus at start!\n";
        }
    }
    else if(op=="!"){
        if(choice_selected){
            if(firstrun){
                firstrun = false;
                std::cout<<"factorial is selected\n";
                if(!readOp2()) return;
                if((op1=="!" && op2=="x") || (op1=="!" && op2=="/") || (op1=="!" && op2=="!") || (op1=="!" && op2=="mod")){
                    choice_selected = false;
                }
                else{
                    choice_selected = true;
                }
                CalculatorChoices(op2);
                if(nestedFailed()) return;
                memory = factorial(n1);
                showAnswer(memory);
                choice_selected = false;
            }
            else{
                firstrun = true;
                if(!readNumber("Enter the second number : ", n2)) return;
                if(!readNumber("Enter the 3rd number : ", n3)) return;
                memory = factorial(n2);
                showAnswer(memory);
            }
        }
        else{
            std::cout<<"Can not use factorial at start!\n";
        }
    }
    else if(op=="sqrt"){
        if(firstrun){
            firstrun = false;
            std::cout<<"Square root is selected\n";
            if(!readOp2()) return;
            choice_selected = true;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            memory = squareRoot(memory);
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            memory = squareRoot(n2);
            showAnswer(memory);
        }
    }
    else if(op=="log"){
        if(firstrun){
            firstrun = false;
            std::cout<<"Logarithm is selected\n";
            if(!readOp2()) return;
            choice_selected = true;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            memory = logarithm(memory);
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            memory = logarithm(n2);
            showAnswer(memory);
        }
    }
    else if(op=="antilog"){
        if(firstrun){
            firstrun = false;
            std::cout<<"Anti-Logarithm is selected\n";
            if(!readOp2()) return;
            choice_selected = true;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            memory = anti_logarithm(memory);
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            memory = anti_logarithm(n2);
            showAnswer(memory);
        }
    }
    else if(op=="abs"){
        if(firstrun){
            firstrun = false;
            std::cout<<"Absolute value is selected\n";
            if(!readOp2()) return;
            choice_selected = true;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            memory = absolute(memory);
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            memory = absolute(n2);
            showAnswer(memory);
        }
    }
    else if(op=="sin"){
        if(firstrun){
            firstrun = false;
            std::cout<<"sin function is selected\n";
            if(!readOp2()) return;
            choice_selected = true;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            memory = SIN(memory);
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            memory = SIN(n2);
            showAnswer(memory);
        }
    }
    else if(op=="cos"){
        if(firstrun){
            firstrun = false;
            std::cout<<"cos function is selected\n";
            if(!readOp2()) return;
            choice_selected = true;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            memory = COS(memory);
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            memory = COS(n2);
            showAnswer(memory);
        }
    }
    else if(op=="tan"){
        if(firstrun){
            firstrun = false;
            std::cout<<"tan function is selected\n";
            if(!readOp2()) return;
            choice_selected = true;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            memory = TAN(memory);
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            memory = TAN(n2);
            showAnswer(memory);
        }
    }
    else if(op=="arcsin"){
        if(firstrun){
            firstrun = false;
            std::cout<<"Inverse sin function is selected\n";
            if(!readOp2()) return;
            choice_selected = true;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            memory = ASIN(memory);
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            memory = ASIN(n2);
            showAnswer(memory);
        }
    }
    else if(op=="arccos"){
        if(firstrun){
            firstrun = false;
            std::cout<<"Inverse cos function is selected\n";
            if(!readOp2()) return;
            choice_selected = true;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            memory = ACOS(memory);
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            memory = ACOS(n2);
            showAnswer(memory);
        }
    }
    else if(op=="arctan"){
        if(firstrun){
            firstrun = false;
            std::cout<<"Inverse tan function is selected\n";
            if(!readOp2()) return;
            choice_selected = true;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            memory = ATAN(memory);
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            memory = ATAN(n2);
            showAnswer(memory);
        }
    }
    else if(op=="sinh"){
        if(firstrun){
            firstrun = false;
            std::cout<<"sinh function is selected\n";
            if(!readOp2()) return;
            choice_selected = true;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            memory = SINH(memory);
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            memory = SINH(n2);
            showAnswer(memory);
        }
    }
    else if(op=="cosh"){
        if(firstrun){
            firstrun = false;
            std::cout<<"cosh function is selected\n";
            if(!readOp2()) return;
            choice_selected = true;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            memory = COSH(memory);
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            memory = COSH(n2);
            showAnswer(memory);
        }
    }
    else if(op=="tanh"){
        if(firstrun){
            firstrun = false;
            std::cout<<"tanh function is selected\n";
            if(!readOp2()) return;
            choice_selected = true;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            memory = TANH(memory);
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            memory = TANH(n2);
            showAnswer(memory);
        }
    }
    else if(op=="arcsinh"){
        if(firstrun){
            firstrun = false;
            std::cout<<"Inverse sinh function is selected\n";
            if(!readOp2()) return;
            choice_selected = true;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            memory = ASINH(memory);
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            memory = ASINH(n2);
            showAnswer(memory);
        }
    }
    else if(op=="arccosh"){
        if(firstrun){
            firstrun = false;
            std::cout<<"Inverse cosh function is selected\n";
            if(!readOp2()) return;
            choice_selected = true;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            memory = ACOSH(memory);
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            memory = ACOSH(n2);
            showAnswer(memory);
        }
    }
    else if(op=="arctanh"){
        if(firstrun){
            firstrun = false;
            std::cout<<"Inverse tanh function is selected\n";
            if(!readOp2()) return;
            choice_selected = true;
            CalculatorChoices(op2);
            if(nestedFailed()) return;
            memory = ATANH(memory);
            showAnswer(memory);
        }
        else{
            firstrun = true;
            if(!readNumber("Enter the second number : ", n2)) return;
            memory = ATANH(n2);
            showAnswer(memory);
        }
    }
    else{
        std::cout<<"Wrong operator entered!\nThis operator does not exist...\n";
    }
}


// Asks for the 2nd operator and reads it. Returns false only if input is closed (EOF).
static bool readOp2(){
    std::cout<<"Enter Your 2nd Operator : ";
    if(!(std::cin>>op2)) return false;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}

// Call after the 2nd operator ran: true if it did not finish or gave no usable answer.
static bool nestedFailed(){
    if(!firstrun || !std::isfinite(memory)){ firstrun = true; return true; }
    return false;
}