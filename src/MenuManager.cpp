#include <iostream>
#include <iomanip>
#include "../includes/MenuManager.h"
#include "../includes/MenuUI.h"

void addMenuItems(std::vector<Menuitems>& menuItems){
    int id, stock;
    double price;
    std::string name;

    std::cout << "Enter Product ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "Enter Product Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Product Price: ";
    std::cin >> price;
    std::cout << "Enter Product Stock: ";
    std::cin >> stock;

    menuItems.push_back(Menuitems(id, name, price, stock));
}

void showMenuItems(const std::vector<Menuitems>& menuItems) {
    printSeparator('+', '+', '+');
    std::cout << "|" << std::left << std::setw(W_ID) << "ID"
               << "|" << std::left << std::setw(W_NAME) << "Name"
               << "|" << std::left << std::setw(W_PRICE) << "Price"
               << "|" << std::left << std::setw(W_STOCK) << "Stock"
               << "|" << std::endl;
    printSeparator('+', '+', '+');

    for (const auto& item : menuItems) {
        item.display();
    }

    printSeparator('+', '+', '+');
}

void updateMenuItem(std::vector<Menuitems>& menuItems){
    int id;
    std::cout << "Enter item ID to update: ";
    std::cin >> id;
    for (auto& item : menuItems) {
        if (id == item.getId()) {
            std::cout << "Current item details:\n";
            item.display();

            int stock;
            double price;
            std::string name;

            std::cout << "Enter new name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter new price: ";
            std::cin >> price;
            std::cout << "Enter new stock: ";
            std::cin >> stock;

            item.setName(name);
            item.setPrice(price);
            item.setStock(stock);
            std::cout << "Item updated successfully!\n";
            return;
        }
    }
    std::cout << "Item not found.\n";  // moved outside the loop
}

void deleteMenuItem(std::vector<Menuitems>& menuItems){
    int id;
    std::cout << "Enter item ID to delete: ";
    std::cin >> id;
    for (auto i = menuItems.begin(); i != menuItems.end(); ++i) {
        if (i->getId() == id) {
            std::cout << "Deleting:\n";
            i->display();
            menuItems.erase(i);
            std::cout << "Item deleted.\n";
            return;
        }
    }
    std::cout << "Item not found.\n";  // moved outside the loop
}