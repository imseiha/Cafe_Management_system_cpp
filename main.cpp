#include <iostream>
#include <limits>
#include "SaleManager.h"
#include "StaffManager.h"
#include "MenuManager.h"
#include "FinanceManager.h"

int main() {
    int choice = 0;

    do {
        std::cout << "\n\n";
        std::cout << "============================================\n";
        std::cout << "          CAFE MANAGEMENT SYSTEM\n";
        std::cout << "============================================\n";

        std::cout << "1. Sale Management\n";
        std::cout << "2. Staff Management\n";
        std::cout << "3. Menu Management\n";
        std::cout << "4. Financial Management\n";
        std::cout << "5. Exit\n";

        std::cout << "============================================\n";

        std::cout << "Choose option: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nInvalid input!";
            std::cout << "\nPlease enter a number from 1 to 5.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                SaleManager saleManager;
                saleManager.run();
                break;
            }
            case 2: {
                StaffManager staffManager;
                staffManager.staffMenu();
                break;
            }
            case 3: {
                MenuManager menuManager;
                menuManager.run();
                break;
            }
            case 4: {
                FinanceManager financeManager;
                financeManager.run();
                break;
            }
            case 5:
                break;
            default:
                std::cout << "\nInvalid input!\n";
                break;
        }
    } while (choice != 5);

    return 0;
}