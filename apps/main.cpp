#include <iostream>
#include <cstdlib>
#include <cmath>
#include "numlab/UI/UI_Choices.h"
#include "numlab/Calculator/Calculator.h"
#include "numlab/base_converter/Base_Converter.h"
#include "numlab/data_type/Data_Type_Converter.h"
#include "numlab/Overflow_Precision/Overflow_Precision.h"
#include "numlab/operator_lab/Operator_Lab.h"
#include "numlab/Scientific_Function/Scientific_Function.h"
#include "numlab/UI/ClearScreen.h"
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