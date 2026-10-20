#include "Project1/Calculator.h"
#include "Project1/ClearScreen.h"
#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
#include <cctype>
#include <string>
#include <algorithm>

static void LogTypes(char &base,double &n1);
static void AntiLogTypes(char &base,double &n1);
static bool readNumber(const char* prompt, double& out);
static std::string toLower(std::string s);
static bool askYesNo(const char* prompt);
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
    std::cout<<"+ : Addition\n";
    std::cout<<"- : Subtraction\n";
    std::cout<<"* : Multiplication\n";
    std::cout<<"/ : Division\n";
    std::cout<<"^ : Power\n";
    std::cout<<"% : Modulus\n";
    std::cout<<"! : Factorial\n";
    std::cout<<"s : Square root\n";
    std::cout<<"l : Logarithm\n";
    std::cout<<"a : Anti-logarithm\n";
    std::cout<<"v : absolute value\n";
}

// n1 (the first number) is already set by Calculator(), so each branch only asks
// for what it still needs: the second number, or the log base.
void CalculatorChoices(char &op){
    if(op=='+'){
        std::cout<<"Addition is selected\n";
        if(!readNumber("Enter the second number : ", n2)) return;
        showAnswer(n1+n2);
    }
    else if(op=='-'){
        std::cout<<"Subtraction is selected\n";
        if(!readNumber("Enter the second number : ", n2)) return;
        showAnswer(n1-n2);
    }
    else if(op=='*'){
        std::cout<<"Multiplication is selected\n";
        if(!readNumber("Enter the second number : ", n2)) return;
        showAnswer(n1*n2);
    }
    else if(op=='/'){
        std::cout<<"Division is selected\n";
        if(!readNumber("Enter the second number : ", n2)) return;

        if(n2==0 && n1<0){
            showAnswer(-std::numeric_limits<double>::infinity());
        }
        else if(n2==0 && n1>0){
            showAnswer(std::numeric_limits<double>::infinity());
        }
        else if(n2==0 && n1==0){
            showAnswer(std::numeric_limits<double>::quiet_NaN());
        }
        else{
            showAnswer(n1/n2);
        }
    }
    else if(op=='^'){
        std::cout<<"Power is selected\n";
        if(!readNumber("Enter the second number : ", n2)) return;

        double result = std::pow(n1, n2);
        if(std::isnan(result)){
            std::cout<<"Answer is not a real number\n";
        }
        else if(std::isinf(result)){
            std::cout<<"Answer is infinite (overflow or zero to a negative power)\n";
        }
        else{
            showAnswer(result);
        }
    }
    else if(op=='%'){
        std::cout<<"Modulus is selected\n";
        if(!readNumber("Enter the second number : ", n2)) return;

        if(n2 == 0){
            std::cout<<"Modulus by zero is undefined\n";
        }
        else{
            double r = std::fmod(n1, n2);
            if(r < 0) r+=std::fabs(n2);
            showAnswer(r);
        }
    }
    else if(op=='!'){
        std::cout<<"Factorial is selected\n";

        if(n1 < 0 || n1 != std::floor(n1)){
            std::cout<<"Factorial is only defined for whole numbers (0 or greater)\n";
        }
        else if(n1 > 170){
            std::cout<<"Factorial overflow : result too large for double\n";
        }
        else{
            showAnswer(std::tgamma(n1+1));
        }
    }
    else if(op=='s'){
        std::cout<<"Square root is selected\n";

        if(n1>=0){
            showAnswer(std::sqrt(n1));
        }
        else{
            std::cout<<"Square root is not defined for negative numbers\n";
        }
    }
    else if(op=='l'){
        std::cout<<"Logarithm is selected\n";
        char base;
        std::cout << "  2  ->  Log base 2\n";
        std::cout << "  t  ->  Log base 10\n";
        std::cout << "  e  ->  Log base e(ln)\n";
        std::cout<<"Select Log Base: ";
        if(!(std::cin>>base)) return;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        LogTypes(base,n1);
    }
    else if(op=='a'){
        std::cout<<"Anti-Logarithm is selected\n";
        char base;
        std::cout << "  2  ->  Anti-Log base 2\n";
        std::cout << "  t  ->  Anti-Log base 10\n";
        std::cout << "  e  ->  Anti-Log base e(ln)\n";
        std::cout<<"Select Anti-Log Base: ";
        if(!(std::cin>>base)) return;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        AntiLogTypes(base,n1);
    }
    else if(op=='v'){
        std::cout<<"Absolute value is selected\n";
        showAnswer(std::abs(n1));
    }
    else{
        std::cout<<"Wrong operator entered!\nThis operator does not exist...\n";
    }
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


// Keeps asking until a valid number is typed. Returns false only if input is closed (EOF).
static bool readNumber(const char* prompt, double& out){
    while(true){
        std::cout << prompt;
        if(std::cin >> out){
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // drop anything left on the line
            return true;
        }
        if(std::cin.eof() || std::cin.bad()) return false;   // nothing more to read
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid number! Try again.\n";
    }
}


// Prints the answer and stores it, so it becomes the first number of the next round.
static void showAnswer(double value){
    memory = value;
    std::cout<<"Answer : "<<memory<<"\n";
}


static std::string toLower(std::string s){
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){
        return std::tolower(c);
    });
    return s;
}


static bool askYesNo(const char* prompt){
    std::string answer;
    while(true){
        std::cout << prompt;
        if(!(std::cin >> answer)) return false;   // input closed: stop
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        answer = toLower(answer);
        if(answer == "y" || answer == "yes" || answer == "ye") return true;
        if(answer == "n" || answer == "no")  return false;
        std::cout << "Invalid choice! Please enter 'y' or 'n'.\n";
    }
}