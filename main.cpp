#include <iostream>
#include <limits>
#include "SaleManager.h"
#include "StaffManager.h"
#include "MenuManager.h"
#include "OrderManager.h"
#include "FinanceManager.h"

namespace {
bool readChoice(int& choice, int first, int last) {
    if (std::cin >> choice && choice >= first && choice <= last) return true;
    if (std::cin.eof()) return false;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid choice. Please enter a number from " << first << " to " << last << ".\n";
    return false;
}

void waitForEnter() {
    std::cout << "\nPress Enter to return...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void viewMyInformation(const Staff& staff) {
    std::cout << "\n========================================\nMY INFORMATION\n========================================\n";
    std::cout << "Staff ID           : " << staff.getId()
              << "\nName               : " << staff.getName()
              << "\nGender             : " << staff.getGender()
              << "\nDate of Birth      : " << staff.getDateOfBirth()
              << "\nPlace of Birth     : " << staff.getPlaceOfBirth()
              << "\nCurrent Address    : " << staff.getCurrentAddress()
              << "\nPhone              : " << staff.getPhoneNumber()
              << "\nEmail              : " << staff.getEmail()
              << "\nPosition           : " << staff.getPosition()
              << "\nUsername           : " << staff.getUsername()
              << "\nPassword           : " << staff.getPassword()
              << "\nSalary             : " << staff.getSalary()
              << "\nStatus             : " << staff.getStatus() << "\n";
    waitForEnter();
}

void staffDashboard(const Staff& staff) {
    for (;;) {
        std::cout << "\n========================================\nSTAFF DASHBOARD\n========================================\n";
        std::cout << "1. Order\n2. View My Information\n3. Exit\nEnter your choice: ";
        int choice;
        if (!readChoice(choice, 1, 3)) { if (std::cin.eof()) return; continue; }
        if (choice == 1) { OrderManager manager; manager.run(true, staff.getId()); }
        else if (choice == 2) viewMyInformation(staff);
        else return;
    }
}

void staffAuthenticationMenu() {
    StaffManager manager;
    for (;;) {
        std::cout << "\n========================================\nSTAFF ACCOUNT\n========================================\n";
        std::cout << "1. Login\n2. Register\n3. Back\nEnter your choice: ";
        int choice;
        if (!readChoice(choice, 1, 3)) { if (std::cin.eof()) return; continue; }
        if (choice == 1) { Staff staff; if (manager.authenticate(staff, false)) staffDashboard(staff); }
        else if (choice == 2) manager.createStaff("Staff");
        else return;
    }
}

void adminDashboard(const Staff& admin) {
    for (;;) {
        std::cout << "\n========================================\nADMIN DASHBOARD\n========================================\n";
        std::cout << "1. Staff Management\n2. Menu Management\n3. Sale Management\n4. Finance Management\n5. My Information\n6. Logout\nEnter your choice: ";
        int choice;
        if (!readChoice(choice, 1, 6)) { if (std::cin.eof()) return; continue; }
        if (choice == 1) { StaffManager manager; manager.staffMenu(); }
        else if (choice == 2) { MenuManager manager; manager.run(); }
        else if (choice == 3) { SaleManager manager; manager.run(); }
        else if (choice == 4) { FinanceManager manager; manager.run(); }
        else if (choice == 5) viewMyInformation(admin);
        else return;
    }
}

void adminLogin() {
    StaffManager manager;
    std::cout << "\n========================================\nADMIN LOGIN\n========================================\n";
    Staff admin;
    if (manager.authenticate(admin, true)) adminDashboard(admin);
}
}

int main() {
    for (;;) {
        std::cout << "\n========================================\nCAFE MANAGEMENT SYSTEM\n========================================\n";
        std::cout << "1. Login As Staff\n2. Login As Admin\n3. Exit Program\nEnter your choice: ";
        int choice;
        if (!readChoice(choice, 1, 3)) { if (std::cin.eof()) break; continue; }
        if (choice == 1) staffAuthenticationMenu();
        else if (choice == 2) adminLogin();
        else break;
    }
    return 0;
}
