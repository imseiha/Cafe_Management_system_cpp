#include <iostream>
#include <vector>
#include <limits>
#include "menu.h"
#include "order.h"
#include "filehandler.h"

const std::string MENU_FILE = "menu.txt";
const std::string ORDERS_FILE = "orders.csv";

void showMenu(const std::vector<MenuItem>& items) {
    std::cout << "\n--- CAFE MENU ---\n";
    std::cout << "ID\tName\t\tPrice\tStock\n";
    for (const auto& item : items) {
        item.display();
    }
    std::cout << "-----------------\n";
}

void addMenuItem(std::vector<MenuItem>& items) {
    int id, stock;
    double price;
    std::string name;

    std::cout << "Enter item ID: ";
    std::cin >> id;
    std::cout << "Enter item name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter price: ";
    std::cin >> price;
    std::cout << "Enter stock quantity: ";
    std::cin >> stock;

    items.push_back(MenuItem(id, name, price, stock));
    std::cout << "Item added!\n";
}

void updateMenuItem(std::vector<MenuItem>& items) {
    int id;
    std::cout << "Enter item ID to update: ";
    std::cin >> id;

    for (auto& item : items) {
        if (item.getId() == id) {
            std::cout << "Current details: ";
            item.display();

            std::string name;
            double price;
            int stock;

            std::cout << "Enter new name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter new price: ";
            std::cin >> price;
            std::cout << "Enter new stock quantity: ";
            std::cin >> stock;

            item.setName(name);
            item.setPrice(price);
            item.setStock(stock);

            std::cout << "Item updated!\n";
            return;
        }
    }
    std::cout << "Item ID not found.\n";
}

void deleteMenuItem(std::vector<MenuItem>& items) {
    int id;
    std::cout << "Enter item ID to delete: ";
    std::cin >> id;

    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getId() == id) {
            std::cout << "Deleting: ";
            it->display();
            items.erase(it);
            std::cout << "Item deleted!\n";
            return;
        }
    }
    std::cout << "Item ID not found.\n";
}

void placeOrder(std::vector<MenuItem>& items, std::vector<Order>& orders, int& nextOrderId) {
    int itemId, qty;
    std::cout << "Enter item ID to order: ";
    std::cin >> itemId;
    std::cout << "Enter quantity: ";
    std::cin >> qty;

    for (auto& item : items) {
        if (item.getId() == itemId) {
            if (item.getStock() < qty) {
                std::cout << "Not enough stock! Only " << item.getStock() << " left.\n";
                return;
            }
            double total = item.getPrice() * qty;
            item.reduceStock(qty);

            Order newOrder(nextOrderId++, itemId, qty, total);
            orders.push_back(newOrder);
            FileHandler::appendOrder(ORDERS_FILE, newOrder); // save immediately

            std::cout << "Order placed! Total: $" << total << "\n";
            return;
        }
    }
    std::cout << "Item ID not found.\n";
}

int main() {
    // Load existing data at startup
    std::vector<MenuItem> menuItems = FileHandler::loadMenu(MENU_FILE);
    std::vector<Order> orders = FileHandler::loadOrders(ORDERS_FILE);

    // Figure out the next order ID based on saved history
    int nextOrderId = 1;
    for (const auto& o : orders) {
        if (o.getOrderId() >= nextOrderId) nextOrderId = o.getOrderId() + 1;
    }

    // If no menu exists yet, seed with some starter items
    if (menuItems.empty()) {
        menuItems.push_back(MenuItem(1001, "Cappuccino", 3.50, 25));
        menuItems.push_back(MenuItem(1002, "Espresso", 2.50, 40));
        menuItems.push_back(MenuItem(1003, "Latte", 4.00, 18));
    }

    int choice = 0;
    while (choice != 7) {
        std::cout << "\n=== CAFE MANAGEMENT SYSTEM ===\n";
        std::cout << "1. View Menu\n";
        std::cout << "2. Add Menu Item\n";
        std::cout << "3. Update Menu Item\n";
        std::cout << "4. Delete Menu Item\n";
        std::cout << "5. Place Order\n";
        std::cout << "6. View Order History\n";
        std::cout << "7. Save & Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                showMenu(menuItems);
                break;
            case 2:
                addMenuItem(menuItems);
                break;
            case 3:
                updateMenuItem(menuItems);
                break;
            case 4:
                deleteMenuItem(menuItems);
                break;
            case 5:
                placeOrder(menuItems, orders, nextOrderId);
                break;
            case 6:
                std::cout << "\n--- ORDER HISTORY ---\n";
                for (const auto& o : orders) o.display();
                break;
            case 7:
                FileHandler::saveMenu(MENU_FILE, menuItems);
                FileHandler::saveOrders(ORDERS_FILE, orders);
                std::cout << "Data saved. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid option, try again.\n";
        }
    }

    return 0;
}