#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Project1/UI_Choices.h"
#include "Project1/Calculator.h"
#include "Project1/Base_Converter.h"
#include "Project1/Data_Type_Converter.h"
#include "Project1/Overflow_Precision.h"
#include "Project1/Operator_Lab.h"
#include "Project1/ClearScreen.h"
static bool readCh(const char *prompt, char &out);

int main(){
    char ch;
    do{
        UI();
        if(!readCh("Enter the Choice : ", ch)) break;
        Choices(ch);
    }
    while(true);
}


static bool readCh(const char *prompt, char &out){
    while(true){
        std::cout << prompt;
        if(std::cin >> out){
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return true;
        }
        if(std::cin.eof() || std::cin.bad()) return false;   // nothing more to read
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid Choice input! Try again.\n";
    }
}







