#ifndef FINANCE_H
#define FINANCE_H

#include <string>
#include <vector>

struct SaleRecord {
    int id;
    std::string itemName;
    double amount;
};

class FinanceManager {
public:
    FinanceManager();
    void addSale(const SaleRecord& record);
    double getTotalRevenue() const;
    void showSales() const;

private:
    std::vector<SaleRecord> sales_;
};

#endif
