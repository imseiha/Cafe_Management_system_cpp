
#ifndef FINANCIAL_MANAGER_H
#define FINANCIAL_MANAGER_H

class FinancialManager
{
private:
    double totalSales;
    double totalExpense;
    

public:
    FinancialManager();

    void run();

    void calculateSales();
    void AddIncome();
    void ReadIncome();
    void UpdateIncome();
    void DeleteIncome();
    void addExpense();
    void AddExpense();
    void ReadExpense();
    void UpdateExpense();
    void DeleteExpense();
    void viewSummary();
};

#endif

