#include "Finance.h"

#include <iomanip>
#include <iostream>

FinanceManager::FinanceManager() = default;

void FinanceManager::addSale(const SaleRecord& record) {
    sales_.push_back(record);
}

double FinanceManager::getTotalRevenue() const {
    double total = 0.0;
    for (const auto& sale : sales_) {
        total += sale.amount;
    }
    return total;
}

void FinanceManager::showSales() const {
    std::cout << "\n=== Sales Summary ===\n";
    for (const auto& sale : sales_) {
        std::cout << sale.id << ". " << sale.itemName
                  << " - $" << std::fixed << std::setprecision(2) << sale.amount << "\n";
    }
    std::cout << "Total Revenue: $" << std::fixed << std::setprecision(2) << getTotalRevenue() << "\n";
    std::cout << "===================\n";
}
