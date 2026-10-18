#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Project1/UI_Choices.h"
#include "Project1/Calculator.h"
#include "Project1/Base_Converter.h"
#include "Project1/Data_Type_Converter.h"
#include "Project1/Overflow_Precision.h"
#include "Project1/Operator_Lab.h"



int main(){
    char ch;
    do{
        UI();
        std::cin>>ch;
        Choices(ch);
    }
    while(ch!=0);
}










