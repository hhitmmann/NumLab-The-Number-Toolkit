#include "Project1/UI_Choices.h"
#include "Project1/Calculator.h"
#include "Project1/Scientific_Function.h"
#include "Project1/Base_Converter.h"
#include "Project1/Data_Type_Converter.h"
#include "Project1/Overflow_Precision.h"
#include "Project1/Operator_Lab.h"
#include "Project1/ClearScreen.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
#include <cctype>
#include <string>
#include <algorithm>


static void LogTypes(char &base,double &n1);
static void AntiLogTypes(char &base,double &n1);

double add(double &a, double &b){
    return (a + b);
}

double subtract(double &a, double &b){
    return (a - b);
}

double multiply(double &a, double &b){
    return (a * b);
}

double divide(double &a, double &b){
    if(b==0 && a<0){
        return -std::numeric_limits<double>::infinity();
    }
    else if(b==0 && a>0){
        return std::numeric_limits<double>::infinity();
    }
    else if(b==0 && a==0){
        return std::numeric_limits<double>::quiet_NaN();
    }
    else{
        return (a/b);
    }
}

double power(double &base, double &exponent){
        if(std::isnan(std::pow(base, exponent))){
            std::cout<<"Answer is not a real number\n";
            return std::nan("");
        }
        else if(std::isinf(std::pow(base, exponent))){
            std::cout<<"Answer is infinite (overflow or zero to a negative power)\n";
            return std::numeric_limits<double>::infinity();
        }
        else{
            return std::pow(base, exponent);
        }
    
}

double modulus(double &a, double &b){
    if(b == 0){
        std::cout<<"Modulus by zero is undefined\n";
        return std::numeric_limits<double>::infinity();
    }
    else{
        double r = std::fmod(a, b);
        if(r < 0){
            r += std::fabs(b);
        }
        return r;
    }
}

double factorial(double &a){
    if(a < 0 || a != std::floor(a)){
        std::cout<<"Factorial is only defined for whole numbers (0 or greater)\n";
        return std::numeric_limits<double>::quiet_NaN();
    }
    else if(a > 170){
        std::cout<<"Factorial overflow : result too large for double\n";
        return std::numeric_limits<double>::infinity();
    }
    else{
        return std::tgamma(a + 1);
    }
}

double squareRoot(double &a){
    if(a>=0){
        return std::sqrt(a);
    }
    else{
        std::cout<<"Square root is not defined for negative numbers\n";
        return std::numeric_limits<double>::quiet_NaN();
    }
}

double absolute(double &a){
    return std::abs(a);
}

double log(double &a){
    char base;
    std::cout << "  2  ->  Log base 2\n";
    std::cout << "  t  ->  Log base 10\n";
    std::cout << "  e  ->  Log base e(ln)\n";
    std::cout<<"Select Log Base: ";
    if(!(std::cin>>base)) return;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    LogTypes(base,a);
    
}

double anti_log(double &a){
    char base;
    double number;
    std::cout << "  2  ->  Anti-Log base 2\n";
    std::cout << "  t  ->  Anti-Log base 10\n";
    std::cout << "  e  ->  Anti-Log base e(ln)\n";
    std::cout<<"Select Anti-Log Base: ";
    if(!(std::cin>>base)) return;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    AntiLogTypes(base,a);
}


static void LogTypes(char &base,double &n1){
    if(base=='2'){
        std::cout<<"Log base 2 is selected\n";
        if(n1<0){
            std::cout<<"Logarithm is not defined for negative numbers\n";
        }
        else if(n1==0){
            showAnswer(-std::numeric_limits<double>::infinity());
        }
        else{
            showAnswer(std::log2(n1));
        }
    }
    else if(base=='t'){
        std::cout<<"Log base 10 is selected\n";
        if(n1 < 0){
            std::cout<<"Logarithm is not defined for negative numbers\n";
        }
        else if(n1 == 0){
            showAnswer(-std::numeric_limits<double>::infinity());
        }
        else{
            showAnswer(std::log10(n1));
        }
    }
    else if(base=='e'){
        std::cout<<"Log base e(Natural Logarithm) is selected\n";

        if(n1<0){
            std::cout<<"Natural Logarithm is not defined for negative numbers\n";
        }
        else if(n1==0){
            showAnswer(-std::numeric_limits<double>::infinity());
        }
        else{
            showAnswer(std::log(n1));
        }
    }
    else{
        std::cout<<"Wrong Log Base entered!\nThis Log Base does not exist...\n";
    }
}



static void AntiLogTypes(char &base,double &n1){
    if(base=='2'){
        std::cout<<"Anti-Log base 2 is selected\n";
        double result = std::pow(2.0, n1);
        if(std::isinf(result)){
            std::cout<<"Anti-logarithm overflow : result too large for double\n";
        }
        else if(result == 0.0){
            std::cout<<"Anti-logarithm underflow : result too small (approaches 0)\n";
        }
        else{
            showAnswer(result);
        }
    }
    else if(base=='t'){
        std::cout<<"Anti-Log base 10 is selected\n";

        double result = std::pow(10.0, n1);

        if(std::isinf(result)){
            std::cout<<"Anti-logarithm overflow : result too large for double\n";
        }
        else if(result == 0.0 && n1 < 0.0){
            std::cout<<"Anti-logarithm underflow : result too small (approaches 0)\n";
        }
        else{
            showAnswer(result);
        }
    }
    else if(base=='e'){
        std::cout<<"Anti-Log base e (Natural AntiLogarithm) is selected\n";

        double result = std::exp(n1);
        if(std::isinf(result)){
            std::cout<<"Anti-Natural Logarithm overflow\n";
        }
        else if( result == 0.0){
            std::cout<<"Anti-Natural Logarithm underflow\n";
        }
        else{
            showAnswer(result);
        }
    }
    else{
        std::cout<<"Wrong Anti-Log Base entered!\nThis Anti-Log Base does not exist...\n";
    }
}
