#pragma once
#include <string>
#include <vector>
#include "Menu.h"
#include "TableFormat.h"

// Column widths for the menu table


void printSeparator(char left, char mid, char right);
void typeEffect(const std::string& text, int delayMs = 15);
void loadingBar();
void showMenuFeature();