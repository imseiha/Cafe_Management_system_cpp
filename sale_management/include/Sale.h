#ifndef SALE_H
#define SALE_H

#include <string>
#include <Receipt.h>
#include "Order.h"

class Sale {
public:
    static void searchReceiptById();
    static void searchReceiptByOrderId();
    static void searchReceiptByDate();
    static void searchSaleById();
    static void searchSaleByDate();
    static void viewSalesFromFile(const std::string& filepath);
};

#endif
