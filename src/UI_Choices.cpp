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


void UI(){
    ClearScreen();
    std::cout<<"Main Menu\n";
    std::cout<<"Please enter  your Choice (1~0) : \n";
    std::cout<<"1. Calculator\n";
    std::cout<<"2. Scientific Functions\n";
    std::cout<<"3. Base Converter\n";
    std::cout<<"4. Data Type Converter\n";
    std::cout<<"5. Overflow & precision lab\n";
    std::cout<<"6. Operator lab\n";
    std::cout<<"0. Exit\n";
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