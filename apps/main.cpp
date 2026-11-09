#include <iostream>
#include <limits>
#include "numlab/UI/UI_Choices.h"
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