#pragma once
#include <string>
#include <vector>
#include "Menu.h"
#include "TableFormat.h"


// int wId, wName, wPrice, wStock, wCategory;

// Column widths for the menu table
void printSeparator(int wId, int wName, int wPrice, int wStock, int wCateory);
void getItemWidths(const Menuitems& item, int& wId, int& wName, int& wPrice, int& wStock, int& wCategory);
void typeEffect(const std::string& text, int delayMs = 15);
void loadingBar();
void showMenuFeature();