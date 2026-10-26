#pragma once
#include <string>
void UI();
void Choices(char &ch);
bool askYesNo(const char* prompt);
std::string toLower(std::string s);
void showAnswer(double value);
bool readNumber(const char* prompt, double& out);