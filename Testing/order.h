#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <sstream>
#include <iostream>

// Represents one customer order for a single menu item
class Order {
private:
    int orderId;
    int menuItemId;
    int quantity;
    double totalPrice;

public:
    Order() : orderId(0), menuItemId(0), quantity(0), totalPrice(0.0) {}

    Order(int orderId, int menuItemId, int quantity, double totalPrice)
        : orderId(orderId), menuItemId(menuItemId), quantity(quantity), totalPrice(totalPrice) {}

    int getOrderId() const { return orderId; }
    int getMenuItemId() const { return menuItemId; }
    int getQuantity() const { return quantity; }
    double getTotalPrice() const { return totalPrice; }

    std::string toCSV() const {
        std::ostringstream oss;
        oss << orderId << "," << menuItemId << "," << quantity << "," << totalPrice;
        return oss.str();
    }

    static Order fromCSV(const std::string& line) {
        std::stringstream ss(line);
        std::string a, b, c, d;

        std::getline(ss, a, ',');
        std::getline(ss, b, ',');
        std::getline(ss, c, ',');
        std::getline(ss, d, ',');

        return Order(std::stoi(a), std::stoi(b), std::stoi(c), std::stod(d));
    }

    void display() const {
        std::cout << "Order #" << orderId << " | Item ID: " << menuItemId
                   << " | Qty: " << quantity << " | Total: $" << totalPrice << "\n";
    }
};

#endif