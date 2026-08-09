#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "TableFormat.h"
#include "Menu.h"

class Order{
    private:
        int orderId;
        int menuItemsId;
        int quantity;
        double totalPrice;
    
    public:
        Order() : orderId(0), menuItemsId(0), quantity(0), totalPrice(0) {}

        Order(int orderId, int menItemsId, int quantity, double totalPrice) 
            : orderId(orderId), menuItemsId(menuItemsId), quantity(quantity), totalPrice(totalPrice) {}

        int getOrderId() const { return orderId; }
        int getMenuItemsId() const { return menuItemsId; } 
        int getQuantity() const { return quantity; }
        double getTotalPrice() const { return totalPrice; }

        std::string toFile() const{
            std::ostringstream oss;
            oss << orderId << "," << menuItemsId << "," << quantity << "," << totalPrice;
            return oss.str();
        }

        static Order fromFile(const std::string& filename){
            std::stringstream ss(filename);
            std::string orderId, menuId, quantity, totalPrice;

            std::getline(ss, orderId, ',');
            std::getline(ss, menuId, ',');
            std::getline(ss, quantity, ',');
            std::getline(ss, totalPrice, ',');

            return Order(std::stoi(orderId), std::stoi(menuId), std::stoi(quantity), std::stod(totalPrice));
        }

        void display() const {
            std::cout << "|" << std::left  << std::setw(W_ID) << orderId
                    << "|" << std::left  << std::setw(W_NAME) << menuItemsId
                    << "|" << std::right << std::fixed << std::setprecision(2)
                                            << std::setw(W_PRICE - 1) << quantity << " "
                    << "|" << std::right << std::setw(W_STOCK - 1) << totalPrice << " "
                    << "|" << std::endl;
        }
};

#endif