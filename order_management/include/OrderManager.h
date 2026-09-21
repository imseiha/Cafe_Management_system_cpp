#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include <vector>
#include <string>
#include "Order.h"

class OrderManager {
private:
    std::vector<Order> orders;
    const std::string filename = "data/orders.txt";
    const std::string receiptsFilename = "data/receipts.txt";

    void loadFromFile();
    void saveToFile();
    bool placeOrder(int staffId = 0);
    void viewOrders();
    void deleteOrder();
    void viewAllReceipts();

public:
    // Staff mode opens the order form directly.
    void run(bool staffMode = false, int staffId = 0);
};

#endif
