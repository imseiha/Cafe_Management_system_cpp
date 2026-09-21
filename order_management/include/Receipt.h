#ifndef RECEIPT_H
#define RECEIPT_H

#include <string>
#include <vector>
#include "Order.h"

class Receipt {
public:
    static double billTotal(const std::vector<Order>& orders);
    static void print(const std::vector<Order>& orders);
    static void saveToFile(const std::vector<Order>& orders, const std::string& filepath);
    static void viewFromFile(const std::string& filepath);
};

#endif