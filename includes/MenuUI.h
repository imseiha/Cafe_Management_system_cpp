#pragma once
#include <string>
#include <vector>
#include "menu.h"

// Column widths for the menu table
const int W_ID = 6, W_NAME = 20, W_PRICE = 10, W_STOCK = 8;

void printSeparator(char left, char mid, char right);
void typeEffect(const std::string& text, int delayMs = 15);
void loadingBar();
void showMenuFeature();