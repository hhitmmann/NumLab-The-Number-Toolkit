#include "numlab/UI/ClearScreen.h"
#include <cstdlib>


void ClearScreen(){
#ifdef _WIN32
    std::system("cls");     // Windows
#else
    std::system("clear");   // Linux / macOS
#endif
}