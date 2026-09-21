#include <iostream>
#include <limits>
#include "SaleManager.h"
#include "StaffManager.h"
#include "MenuManager.h"
#include "OrderManager.h"
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
        std::cout << "4. Order Management\n";
        std::cout << "5. Financial Management\n";
        std::cout << "6. Exit\n";

        std::cout << "============================================\n";

        std::cout << "Choose option: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nInvalid input!";
            std::cout << "\nPlease enter a number from 1 to 6.\n";
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
                OrderManager orderManager;
                orderManager.run();
                break;
            }
            case 5: {
                FinanceManager financeManager;
                financeManager.run();
                break;
            }
            case 6:
                break;
            default:
                std::cout << "\nInvalid input!\n";
                break;
        }
    } while (choice != 6);

    return 0;
}