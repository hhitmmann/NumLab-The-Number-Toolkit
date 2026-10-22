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


void UI(){
    ClearScreen();
    std::cout<<"Main Menu\n";
    std::cout<<"Please enter  your Choice (1~0) : \n";
    std::cout<<"1 -> Calculator\n";
    std::cout<<"2 -> Scientific Functions\n";
    std::cout<<"3 -> Base Converter\n";
    std::cout<<"4 -> Data Type Converter\n";
    std::cout<<"5 -> Overflow & precision lab\n";
    std::cout<<"6 -> Operator lab\n";
    std::cout<<"0 -> Exit\n";
}


void Choices(char &ch){
switch(ch){

case '1': 
    Calculator(); 
    break;
case '2':
    Scientific_Function();
    break;
case '3':
    Base_Converter();
    break;
case '4':
    Data_Type_Converter();
    break;
case '5':
    Overflow_Precision();
    break;
case '6':
    Operator_Lab();
    break;
case '0':
    std::exit(EXIT_SUCCESS);
default:
    std::cout<<"Wrong Choice enter!\nThis choice does not exist...\n";
    break;
}
}


bool askYesNo(const char* prompt){
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


std::string toLower(std::string s){
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){
        return std::tolower(c);
    });
    return s;
}


// Keeps asking until a valid number is typed. Returns false only if input is closed (EOF).
bool readNumber(const char* prompt, double& out){
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
void showAnswer(double value){
    double memory = value;
    std::cout<<"Answer : "<<memory<<"\n";
}

