#include "Finance.h"
#include "Menu.h"
#include "Staff.h"

#include <iostream>
#include <string>

int main() {
    std::cout << "Cafe Management System\n";
    std::cout << "======================\n";

    Menu menu;
    menu.loadFromFile("data/menu.txt");
    menu.showMenu();

    StaffManager staffManager;
    staffManager.addStaff({1, "John", "Barista", 1200.00});
    staffManager.addStaff({2, "Anna", "Cashier", 1100.00});
    staffManager.showStaff();

    FinanceManager financeManager;
    financeManager.addSale({1, "Espresso", 2.50});
    financeManager.addSale({2, "Cappuccino", 3.50});
    financeManager.showSales();

    std::cout << "Project ready for development.\n";
    return 0;
}
