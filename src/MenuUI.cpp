#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <algorithm>
#include <string>

#include "../includes/MenuUI.h"

void printSeparator() {
    std::cout << "+"
               << std::string(W_ID, '-') << "+"
               << std::string(W_NAME, '-') << "+"
               << std::string(W_PRICE, '-') << "+"
               << std::string(W_STOCK, '-') << "+"
               << std::string(W_CATEGORY, '-') << "+"
               << std::endl;
}

void printOrderSeparator() {
    std::cout << "+"
               << std::string(W_ID, '-') << "+"
               << std::string(W_NAME, '-') << "+"
               << std::string(W_PRICE, '-') << "+"
               << std::string(W_STOCK, '-') << "+"
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

void showWelcome() {
    loadingBar();
    std::cout << std::endl;
    printSectionHeader("CAFE MANAGEMENT SYSTEM");
    std::cout << std::endl;
}

void showMenuFeature() {
    const int width = 30;

    std::cout << "+" << std::string(width, '-') << "+" << std::endl;
    std::cout << "|         MENU SYSTEM          |" << std::endl;
    std::cout << "+" << std::string(width, '-') << "+" << std::endl;

    std::cout << "| 1. Add Menu                  |" << std::endl;
    std::cout << "| 2. Show Menu                 |" << std::endl;
    std::cout << "| 3. Update Menu               |" << std::endl;
    std::cout << "| 4. Delete Menu               |" << std::endl;
    // std::cout << "| 5. Order                     |" << std::endl;
    // std::cout << "| 5. Save Data                 |" << std::endl;
    // std::cout << "| 7. Order History             |" << std::endl;
    std::cout << "| 5. Exit                      |" << std::endl;

    std::cout << "+" << std::string(width, '-') << "+" << std::endl;
    std::cout << "Enter your choice : ";
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