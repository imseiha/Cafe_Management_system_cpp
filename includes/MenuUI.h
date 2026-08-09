#pragma once
#include <string>
#include <vector>
#include "Menu.h"
#include "TableFormat.h"


// int wId, wName, wPrice, wStock, wCategory;

// Fixed-width table borders
void printSeparator();
void printOrderSeparator();
void typeEffect(const std::string& text, int delayMs = 15);
void loadingBar();
void showWelcome();
void showMenuFeature();

// Banner for sections / input forms
void printSectionHeader(const std::string& title);
// Input helpers with aligned labels and validation
std::string promptString(const std::string& label);
int promptInt(const std::string& label);
double promptDouble(const std::string& label);