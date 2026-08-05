#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

#include "../includes/MenuUI.h"

void printSeparator(char left, char mid, char right) {
    std::cout << left
               << std::string(W_ID, '-') << mid
               << std::string(W_NAME, '-') << mid
               << std::string(W_PRICE, '-') << mid
               << std::string(W_STOCK, '-') << right
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