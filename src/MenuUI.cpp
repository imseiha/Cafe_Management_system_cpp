#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <algorithm>
#include <string>

#include "../includes/MenuUI.h"

void printSeparator(int wId, int wName, int wPrice, int wStock, int wCategory) {
    std::cout << "+"
               << std::string(wId, '-') << "+"
               << std::string(wName, '-') << "+"
               << std::string(wPrice, '-') << "+"
               << std::string(wStock, '-') << "+"
               << std::string(wCategory, '-') << "+"
               << std::endl;
}

void typeEffect(const std::string& text, int delayMs) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
    std::cout << std::endl;
}

void loadingBar() {
    std::cout << "Loading";
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "." << std::flush;
    }
    std::cout << std::endl;
}

void showMenuFeature() {
    const int width = 30;

    loadingBar();
    std::cout << std::endl;

    std::cout << "+" << std::string(width, '-') << "+" << std::endl;
    typeEffect("|         MENU SYSTEM          |");
    std::cout << "+" << std::string(width, '-') << "+" << std::endl;

    typeEffect("| 1. Add Menu                  |");
    typeEffect("| 2. Show Menu                 |");
    typeEffect("| 3. Update Menu               |");
    typeEffect("| 4. Delete Menu               |");
    typeEffect("| 5. Order                     |");
    typeEffect("| 6. Save Data                 |");
    typeEffect("| 7. Order History             |");
    typeEffect("| 8. Exit                      |");

    std::cout << "+" << std::string(width, '-') << "+" << std::endl;
    std::cout << "Enter your choice : ";
}
void getItemWidths(const Menuitems& item, int& wId, int& wName, int& wPrice, int& wStock, int& wCategory) {
    wId    = std::max((int)std::string("ID").length(), (int)std::to_string(item.getId()).length()) + 2;
    wName  = std::max((int)std::string("Name").length(), (int)item.getName().length()) + 2;
    wPrice = std::max((int)std::string("Price").length(), (int)std::to_string(item.getPrice()).length()) + 2;
    wStock = std::max((int)std::string("Stock").length(), (int)std::to_string(item.getStock()).length()) + 2;
    wCategory = std::max((int)std::string("Category").length(), (int)item.getCategory().length()) + 2;
}

void printSectionHeader(const std::string& title) {
    const int width = 38;
    int pad = std::max(0, (width - (int)title.length()) / 2);
    std::cout << "+" << std::string(width, '-') << "+" << std::endl;
    std::cout << "|" << std::string(pad, ' ')
              << title
              << std::string(width - pad - (int)title.length(), ' ')
              << "|" << std::endl;
    std::cout << "+" << std::string(width, '-') << "+" << std::endl;
}

std::string promptString(const std::string& label) {
    while (true) {
        std::cout << "  " << std::left << std::setw(15) << label << ": ";
        std::string input;
        std::getline(std::cin, input);
        if (!input.empty()) {
            return input;
        }
        std::cout << "  Input cannot be empty. Please try again." << std::endl;
    }
}

int promptInt(const std::string& label) {
    while (true) {
        std::string input = promptString(label);
        try {
            size_t pos = 0;
            int value = std::stoi(input, &pos);
            if (pos == input.length() && value >= 0) {
                return value;
            }
        } catch (...) {}
        std::cout << "  Invalid input. Please enter a whole number." << std::endl;
    }
}

double promptDouble(const std::string& label) {
    while (true) {
        std::string input = promptString(label);
        try {
            size_t pos = 0;
            double value = std::stod(input, &pos);
            if (pos == input.length() && value >= 0) {
                return value;
            }
        } catch (...) {}
        std::cout << "  Invalid input. Please enter a number." << std::endl;
    }
}