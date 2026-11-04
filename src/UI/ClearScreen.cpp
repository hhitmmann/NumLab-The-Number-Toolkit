#include "numlab/UI/ClearScreen.h"
#include <cstdio>
#include <cstdlib>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

// Prints the terminal's "clear screen" escape codes instead of starting a shell
// (system("clear") / system("cls") launches a new process on every call).
void ClearScreen(){
#ifdef _WIN32
    // Windows consoles understand the codes once virtual-terminal mode is on;
    // if that is not possible (old console, output redirected), fall back to cls.
    static const bool vt = []{
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode = 0;
        return h != INVALID_HANDLE_VALUE && GetConsoleMode(h, &mode) &&
               SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }();
    if(!vt){
        std::system("cls");
        return;
    }
#endif
    std::fputs("\033[H\033[2J\033[3J", stdout);
}