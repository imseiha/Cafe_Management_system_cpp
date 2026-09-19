#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include <vector>
#include <string>
#include "Order.h"

class OrderManager {
private:
    std::vector<Order> orders;
    const std::string filename = "data/orders.txt";

    void loadFromFile();
    void saveToFile();
    void placeOrder();
    void viewOrders();
    void deleteOrder();

public:
    void run();
};

#endif