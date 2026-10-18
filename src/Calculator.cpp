#include "Project1/Calculator.h"
#include <iostream>
#include <cmath>

void Calculator(){
    char op;
    
    CalculatorUI();

    std::cout<<"Enter Your Operater : ";
    std::cin>>op;

    CalculatorChoices(op);

}

void CalculatorUI(){
    std::cout<<"Calculater is selected\n";
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
    std::cout<<"n : Natural Logarithm\n";
    std::cout<<"v : absolute value\n";
}

void CalculatorChoices(char &op){
    double n1,n2;
    std::cout<<"Enter the first number : ";
    std::cin>>n1;
    std::cout<<"Enter the second number : ";
    std::cin>>n2;

    if(op=='+'){
        std::cout<<"Addition is selected\n";
        std::cout<<"Answer : "<<n1+n2<<"\n";
    }
    else if(op=='-'){
        std::cout<<"Subtraction is selected\n";
        std::cout<<"Answer : "<<n1-n2<<"\n";
    }
    else if(op=='*'){
        std::cout<<"Multiplication is selected\n";
        std::cout<<"Answer : "<<n1*n2<<"\n";
    }
    else if(op=='/'){
        std::cout<<"Division is selected\n";
        std::cout<<"Answer : "<<n1/n2<<"\n";
    }
    else if(op=='^'){
        std::cout<<"Power is selected\n";
        std::cout<<"Answer : "<<std::pow(n1,n2)<<"\n";
    }
    else if(op=='%'){
        std::cout<<"Modulus is selected\n";
        std::cout<<"Answer : "<<std::fmod(std::abs(n1),std::abs(n2))<<"\n";
    }
    else if(op=='!'){
        std::cout<<"Factorial is selected\n";
        std::cout<<"Answer1 : "<<std::tgamma(n1+1)<<"\n";
        std::cout<<"Answer2 : "<<std::tgamma(n2+1)<<"\n";
    }
    else if(op=='s'){
        std::cout<<"Square root is selected\n";
        std::cout<<"Answer1 : "<<std::sqrt(n1)<<"\n";
        std::cout<<"Answer2 : "<<std::sqrt(n2)<<"\n";
    }
    else if(op=='l'){
        std::cout<<"Logarithm is selected\n";
        std::cout<<"Answer1 : "<<std::log(n1)<<"\n";
        std::cout<<"Answer2 : "<<std::log(n2)<<"\n";
    }
    else if(op=='a'){
        std::cout<<"Anti-logarithm is selected\n";
        std::cout<<"Answer1 : "<<std::exp(n1)<<"\n";
        std::cout<<"Answer2 : "<<std::exp(n2)<<"\n";
    }
    else if(op=='n'){
        std::cout<<"Natural Logarithm is selected\n";
        std::cout<<"Answer1 : "<<std::log(n1)<<"\n";
        std::cout<<"Answer2 : "<<std::log(n2)<<"\n";
    }
    else if(op=='v'){
        std::cout<<"Absolute value is selected\n";
        std::cout<<"Answer1 : "<<std::abs(n1)<<"\n";
        std::cout<<"Answer2 : "<<std::abs(n2)<<"\n";
    }
    else{
        std::cout<<"Wrong operator entered!\nThis operator does not exist...\n";
    }
}