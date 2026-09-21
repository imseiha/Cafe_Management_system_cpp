#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <limits>
#include "OrderManager.h"
#include "MenuManager.h"
#include "Receipt.h"

static std::string currentTimestamp() {
    std::time_t now = std::time(nullptr);
    std::tm localTime = {};
#ifdef _WIN32
    localtime_s(&localTime, &now);
#else
    localTime = *std::localtime(&now);
#endif
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void OrderManager::run(bool staffMode, int staffId) {
    loadFromFile();
    if (staffMode) {
        std::vector<Order> bill;
        char anotherOrder = 'N';
        do {
            if (!placeOrder(staffId)) return;
            bill.push_back(orders.back());
            std::cout << "\nDo you want to make another order? (Y/N): ";
            if (!(std::cin >> anotherOrder)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                anotherOrder = 'N';
            }
        } while (anotherOrder == 'Y' || anotherOrder == 'y');

        Receipt::print(bill);
        Receipt::saveToFile(bill, receiptsFilename);
        std::cout << "Receipt saved to " << receiptsFilename << std::endl;
        return;
    }

    int option = 0;
    do {
        std::cout << std::endl;
        std::cout << "===== Order Management =====" << std::endl;
        std::cout << "1.Place Order" << std::endl;
        std::cout << "2.View Orders" << std::endl;
        std::cout << "3.Delete Order" << std::endl;
        std::cout << "4.View All Receipts" << std::endl;
        std::cout << "5.Back" << std::endl;
        std::cout << "============================" << std::endl;
        std::cout << "Enter your option : ";
        if (!(std::cin >> option)) {
            if (std::cin.eof()) {
                break;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid option. Please try again." << std::endl;
            continue;
        }

        switch (option) {
            case 1: {
                if (placeOrder(staffId)) {
                    std::vector<Order> bill(1, orders.back());
                    Receipt::print(bill);
                    Receipt::saveToFile(bill, receiptsFilename);
                    std::cout << "Receipt saved to " << receiptsFilename << std::endl;
                }
                break;
            }
            case 2: {
                viewOrders();
                break;
            }
            case 3: {
                deleteOrder();
                break;
            }
            case 4: {
                viewAllReceipts();
                break;
            }
            case 5: {
                break;
            }
            default: {
                std::cout << "Invalid option. Please try again." << std::endl;
                break;
            }
        }
    } while (option != 5);
}

void OrderManager::loadFromFile() {
    orders.clear();
    std::ifstream file(filename);
    if (!file.is_open()) {
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::stringstream ss(line);
        std::string token;
        int id = 0;
        int itemId = 0;
        int quantity = 0;
        double unitPrice = 0.0;
        double total = 0.0;
        int staffId = 0;
        std::string itemName;
        std::string createdAt;

        try {
            std::getline(ss, token, '|');
            id = std::stoi(token);
            std::getline(ss, token, '|');
            itemId = std::stoi(token);
            std::getline(ss, itemName, '|');
            std::getline(ss, token, '|');
            quantity = std::stoi(token);
            std::getline(ss, token, '|');
            unitPrice = std::stod(token);
            std::getline(ss, token, '|');
            total = std::stod(token);
            std::getline(ss, createdAt, '|');
            if (std::getline(ss, token, '|')) {
                staffId = std::stoi(token);
            }
        } catch (const std::exception&) {
            std::cout << "Warning: skipping corrupted line in " << filename << "." << std::endl;
            continue;
        }

        orders.push_back(Order(id, itemId, itemName, quantity, unitPrice, total, createdAt, staffId));
    }
    file.close();
}

void OrderManager::saveToFile() {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: could not open " << filename << " for saving." << std::endl;
        return;
    }
    for (const Order& order : orders) {
        file << order.toFileString() << std::endl;
    }
    file.close();
}

bool OrderManager::placeOrder(int staffId) {
    MenuManager menuManager;
    menuManager.viewItems();

    int itemId = 0;
    std::cout << "Enter item ID to order : ";
    if (!(std::cin >> itemId)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid ID." << std::endl;
        return false;
    }

    MenuItem item;
    if (!menuManager.getItemById(itemId, item)) {
        std::cout << "Item with ID " << itemId << " not found." << std::endl;
        return false;
    }

    int quantity = 0;
    std::cout << "Enter quantity : ";
    if (!(std::cin >> quantity)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid quantity." << std::endl;
        return false;
    }
    if (quantity <= 0) {
        std::cout << "Quantity must be a positive number." << std::endl;
        return false;
    }
    if (quantity > item.getStock()) {
        std::cout << "Not enough stock. Available stock is " << item.getStock() << "." << std::endl;
        return false;
    }

    double total = quantity * item.getPrice();

    int nextId = 0;
    for (const Order& order : orders) {
        if (order.getId() > nextId) {
            nextId = order.getId();
        }
    }
    nextId++;

    std::string createdAt = currentTimestamp();
    orders.push_back(Order(nextId, item.getId(), item.getName(), quantity, item.getPrice(), total, createdAt, staffId));

    if (!menuManager.reduceStock(item.getId(), quantity)) {
        std::cout << "Failed to update stock. Order cancelled." << std::endl;
        orders.pop_back();
        return false;
    }

    saveToFile();
    std::cout << "Order placed successfully with ID " << std::setfill('0') << std::setw(4) << nextId << std::setfill(' ') << ". Total : " << total << std::endl;
    return true;
}

void OrderManager::viewOrders() {
    if (orders.empty()) {
        std::cout << "No orders found." << std::endl;
        return;
    }
    std::cout << "Order ID\tItem Name\tQuantity\tUnit Price\tTotal\tCreated At" << std::endl;
    for (const Order& order : orders) {
        order.display();
    }
}

void OrderManager::deleteOrder() {
    if (orders.empty()) {
        std::cout << "No orders to delete." << std::endl;
        return;
    }
    viewOrders();
    int id = 0;
    std::cout << "Enter order ID to delete : ";
    if (!(std::cin >> id)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid ID." << std::endl;
        return;
    }

    for (std::vector<Order>::iterator it = orders.begin(); it != orders.end(); ++it) {
        if (it->getId() == id) {
            orders.erase(it);
            saveToFile();
            std::cout << "Order deleted successfully." << std::endl;
            return;
        }
    }
    std::cout << "Order with ID " << id << " not found." << std::endl;
}

void OrderManager::viewAllReceipts() {
    std::cout << std::endl;
    std::cout << "===== All Receipts =====" << std::endl;
    Receipt::viewFromFile(receiptsFilename);
}
