#include "Project1/UI_Choices.h"
#include "Project1/MathOps.h"
#include "Project1/Calculator.h"
#include "Project1/Base_Converter.h"
#include "Project1/ClearScreen.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
#include <cctype>
#include <string>
#include <algorithm>
#include <numbers>  // for pi here


static double LogTypes(char &base,double &n1);
static double AntiLogTypes(char &base,double &n1);
static bool readBase(const char *prompt, char &out);
static double Radians_To_Degree(double &Rad);
static double Degree_To_Radians(double &Degree);

long double pi = std::numbers::pi_v<long double>;

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

double logarithm(double &a){
    char base;
    std::cout << "  2  ->  Log base 2\n";
    std::cout << "  t  ->  Log base 10\n";
    std::cout << "  e  ->  Log base e(ln)\n";
    if(!readBase("Select Log Base: ", base)){
       std::cout<<"No valid base selected.\n";
       return std::numeric_limits<double>::quiet_NaN();
    }
    return LogTypes(base, a);
}

double anti_logarithm(double &a){
    char base;
    std::cout << "  2  ->  Anti-Log base 2\n";
    std::cout << "  t  ->  Anti-Log base 10\n";
    std::cout << "  e  ->  Anti-Log base e(ln)\n";
    if(!readBase("Enter Anti-Log Base: ", base)){
        std::cout<<"No valid base selected.\n";
        return std::numeric_limits<double>::quiet_NaN();
    }
    return AntiLogTypes(base,a); 
}


static double LogTypes(char &base,double &n1){
    if(base=='2'){
        std::cout<<"Log base 2 is selected\n";
        if(n1<0){
            return std::numeric_limits<double>::quiet_NaN();
        }
        else if(n1==0){
            return -std::numeric_limits<double>::infinity();
        }
        else{
            return std::log2(n1);
        }
    }
    else if(base=='t'){
        std::cout<<"Log base 10 is selected\n";
        if(n1 < 0){
            return std::numeric_limits<double>::quiet_NaN();
        }
        else if(n1 == 0){
            return -std::numeric_limits<double>::infinity();
        }
        else{
            return std::log10(n1);
        }
    }
    else if(base=='e'){
        std::cout<<"Log base e(Natural Logarithm) is selected\n";

        if(n1<0){
            return std::numeric_limits<double>::quiet_NaN();
        }
        else if(n1==0){
            return -std::numeric_limits<double>::infinity();
        }
        else{
            return std::log(n1);
        }
    }
    else{
        std::cout<<"Wrong Log Base entered!\nThis Log Base does not exist...\n";
        return std::numeric_limits<double>::quiet_NaN();
    }
}

double SIN(double a){
    return std::sin(Degree_To_Radians(a));
}
double COS(double a){
    return std::cos(Degree_To_Radians(a));
}
double TAN(double a){
    return std::tan(Degree_To_Radians(a));
}
double ASIN(double a){
    double r = std::asin(a);
    return Radians_To_Degree(r);
}
double ACOS(double a){
    double r = std::acos(a);
    return Radians_To_Degree(r);
}
double ATAN(double a){
    double r = std::atan(a);
    return Radians_To_Degree(r);
}
double SINH(double a){
    return std::sinh(a);
}
double COSH(double a){
    return std::cosh(a);
}
double TANH(double a){
    return std::tanh(a);
}
double ASINH(double a){
    return std::asinh(a);
}
double ACOSH(double a){
    return std::acosh(a);
}
double ATANH(double a){
    return std::atanh(a);
}


static double Radians_To_Degree(double &Rad){
    double Degree = Rad*(pi/180);
    return Degree;
}

static double Degree_To_Radians(double &Degree){
    double Rad = Degree*(pi/180);
    return Rad;
}

static double AntiLogTypes(char &base,double &n1){
    if(base=='2'){
        std::cout<<"Anti-Log base 2 is selected\n";
        double result = std::pow(2.0, n1);
        if(std::isinf(result)){
            return std::numeric_limits<double>::quiet_NaN();
        }
        else if(result == 0.0){
            return std::numeric_limits<double>::quiet_NaN();
        }
        else{
            return result;
        }
    }
    else if(base=='t'){
        std::cout<<"Anti-Log base 10 is selected\n";
        double result = std::pow(10.0, n1);
        if(std::isinf(result)){
            return std::numeric_limits<double>::infinity();
        }
        else if(result == 0.0 && n1 < 0.0){
            return std::numeric_limits<double>::quiet_NaN();
        }
        else{
            return result;
        }
    }
    else if(base=='e'){
        std::cout<<"Anti-Log base e (Natural AntiLogarithm) is selected\n";
        double result = std::exp(n1);
        if(std::isinf(result)){
            return std::numeric_limits<double>::infinity();
        }
        else if(result == 0.0){
            return std::numeric_limits<double>::quiet_NaN();
        }
        else{
            return result;
        }
    }
    else{
        std::cout<<"Wrong Anti-Log Base entered!\nThis Anti-Log Base does not exist...\n";
        return std::numeric_limits<double>::quiet_NaN();
    }
}


static bool readBase(const char *prompt, char &out){
    while(true){
        std::cout << prompt;
        if(std::cin >> out){
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return true;
        }
        if(std::cin.eof() || std::cin.bad()) return false;   // nothing more to read
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid Base input! Try again.\n";
    }
}