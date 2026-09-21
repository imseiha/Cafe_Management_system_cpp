
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <limits>

#include "FinanceManager.h"
#include "Order.h"

FinancialManager::FinancialManager()
    : totalSales(0.0), totalExpense(0.0)
{
}

static double manualIncomeTotal()
{
    std::ifstream file("data/income.txt");

    if (!file.is_open())
    {
        return 0.0;
    }

    std::string line;
    double total = 0.0;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);

        std::string token;

        std::getline(ss, token, '|');
        std::getline(ss, token, '|');
        std::getline(ss, token, '|');

        try
        {
            total += std::stod(token);
        }
        catch (...)
        {
        }
    }

    file.close();
    return total;
}

static int nextIdFromFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        return 1;
    }

    int nextId = 1;
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);
        std::string token;
        std::getline(ss, token, '|');

        try
        {
            int id = std::stoi(token);
            if (id >= nextId)
            {
                nextId = id + 1;
            }
        }
        catch (...)
        {
        }
    }

    file.close();
    return nextId;
}

struct StaffSummary
{
    int count = 0;
    double totalSalary = 0.0;
};

static StaffSummary readStaffSummary()
{
    StaffSummary summary;

    std::ifstream file("data/staff.txt");

    if (!file.is_open())
    {
        return summary;
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);
        std::string token;
        int field = 0;

        while (std::getline(ss, token, '|'))
        {
            ++field;

            if (field == 12)
            {
                try
                {
                    summary.totalSalary += std::stod(token);
                }
                catch (...)
                {
                }
                break;
            }
        }

        ++summary.count;
    }

    file.close();
    return summary;
}

static double expenseTotalFromFile()
{
    std::ifstream file("data/expense.txt");

    if (!file.is_open())
    {
        return 0.0;
    }

    std::string line;
    double total = 0.0;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, '|');
        std::getline(ss, token, '|');
        std::getline(ss, token, '|');

        try
        {
            total += std::stod(token);
        }
        catch (...)
        {
        }
    }

    file.close();
    return total;
}

void FinancialManager::calculateSales()
{
    totalSales = 0.0;

    std::ifstream file("data/orders.txt");

    if (!file.is_open())
    {
        std::cout << "Error: Could not open orders.txt" << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);

        std::string token;

        // ID
        std::getline(ss, token, '|');

        // Item ID
        std::getline(ss, token, '|');

        // Item Name
        std::getline(ss, token, '|');

        // Quantity
        std::getline(ss, token, '|');

        // Unit Price
        std::getline(ss, token, '|');

        // Total
        std::getline(ss, token, '|');

        try
        {
            double orderTotal = std::stod(token);
            totalSales += orderTotal;
        }
        catch (...)
        {
            std::cout << "Warning: Invalid order data." << std::endl;
        }
    }

    file.close();
}

void FinancialManager::AddIncome()
{
    int id = nextIdFromFile("data/income.txt");
    std::string description;
    double amount;

    std::cout << "\n========== ADD INCOME ==========\n";

    std::cin.ignore();

    std::cout << "Enter Description: ";
    std::getline(std::cin, description);

    std::cout << "Enter Amount: $";
    std::cin >> amount;

    std::ofstream file("data/income.txt", std::ios::app);

    if (!file.is_open())
    {
        std::cout << "Error: Could not open income.txt\n";
        return;
    }

    file << id << "|"
         << description << "|"
         << amount << "\n";

    file.close();

    std::cout << "Income added successfully! (ID: " << id << ")\n";
}
void FinancialManager::ReadIncome()
{
    std::ifstream file("data/income.txt");

    if (!file.is_open())
    {
        std::cout << "Error: Could not open income.txt\n";
        return;
    }

    int id;
    std::string description;
    double amount;
    std::string line;

    std::cout << "\n========== INCOME LIST ==========\n";

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, '|');
        id = std::stoi(token);

        std::getline(ss, description, '|');

        std::getline(ss, token, '|');
        amount = std::stod(token);

        std::cout << "ID: " << id << "\n";
        std::cout << "Description: " << description << "\n";
        std::cout << "Amount: $" << amount << "\n";
        std::cout << "-----------------------------\n";
    }

    file.close();
}
void FinancialManager::UpdateIncome()
{
    int updateID;

    std::cout << "\n========== UPDATE INCOME ==========\n";
    std::cout << "Enter Income ID to update: ";
    std::cin >> updateID;

    std::ifstream file("data/income.txt");

    if (!file.is_open())
    {
        std::cout << "Error: Could not open income.txt\n";
        return;
    }

    std::ofstream temp("data/temp.txt");

    int id;
    std::string description;
    double amount;
    std::string line;
    bool found = false;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, '|');
        id = std::stoi(token);

        std::getline(ss, description, '|');

        std::getline(ss, token, '|');
        amount = std::stod(token);

        if (id == updateID)
        {
            found = true;

            std::cin.ignore();

            std::cout << "Enter new Description: ";
            std::getline(std::cin, description);

            std::cout << "Enter new Amount: $";
            std::cin >> amount;
        }

        temp << id << "|" << description << "|" << amount << "\n";
    }

    file.close();
    temp.close();

    std::remove("data/income.txt");
    std::rename("data/temp.txt", "data/income.txt");

    if (found)
        std::cout << "Income updated successfully!\n";
    else
        std::cout << "Income ID not found!\n";
}
void FinancialManager::DeleteIncome()
{
    int deleteID;

    std::cout << "\n========== DELETE INCOME ==========\n";
    std::cout << "Enter Income ID to delete: ";
    std::cin >> deleteID;

    std::ifstream file("data/income.txt");

    if (!file.is_open())
    {
        std::cout << "Error: Could not open income.txt\n";
        return;
    }

    std::ofstream temp("data/temp.txt");

    int id;
    std::string description;
    double amount;
    std::string line;
    bool found = false;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, '|');
        id = std::stoi(token);

        std::getline(ss, description, '|');

        std::getline(ss, token, '|');
        amount = std::stod(token);

        if (id == deleteID)
        {
            found = true;
            continue;
        }

        temp << id << "|" << description << "|" << amount << "\n";
    }

    file.close();
    temp.close();

    std::remove("data/income.txt");
    std::rename("data/temp.txt", "data/income.txt");

    if (found)
        std::cout << "Income deleted successfully!\n";
    else
        std::cout << "Income ID not found!\n";
}

void FinancialManager::addExpense() // Spending
{
    double expense;

    std::cout << "\nEnter Expense Amount: $";
    std::cin >> expense;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');

        std::cout << "Invalid expense amount." << std::endl;
        return;
    }

    if (expense <= 0)
    {
        std::cout << "Expense must be Bigger than 0." << std::endl;
        return;
    }

    totalExpense += expense;

    std::cout << "Expense added successfully." << std::endl;
}
void FinancialManager::AddExpense()
{
    int id = nextIdFromFile("data/expense.txt");
    std::string description;
    double amount;

    std::cout << "\n========== ADD EXPENSE ==========\n";

    std::cin.ignore();

    std::cout << "Enter Description: ";
    std::getline(std::cin, description);

    std::cout << "Enter Amount: $";
    std::cin >> amount;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');

        std::cout << "Invalid expense amount.\n";
        return;
    }

    if (amount <= 0)
    {
        std::cout << "Expense must be bigger than 0.\n";
        return;
    }

    std::ofstream file("data/expense.txt", std::ios::app);

    if (!file.is_open())
    {
        std::cout << "Error: Could not open expense.txt\n";
        return;
    }

    file << id << "|"
         << description << "|"
         << amount << "\n";

    file.close();

    totalExpense += amount;

    std::cout << "Expense added successfully! (ID: " << id << ")\n";
}

void FinancialManager::ReadExpense()
{
    std::ifstream file("data/expense.txt");

    if (!file.is_open())
    {
        std::cout << "Error: Could not open expense.txt\n";
        return;
    }

    std::string line;

    std::cout << "\n========== EXPENSE LIST ==========\n";

    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        std::string token;
        int id;
        std::string description;
        double amount;

        std::getline(ss, token, '|');
        id = std::stoi(token);

        std::getline(ss, description, '|');

        std::getline(ss, token, '|');
        amount = std::stod(token);

        std::cout << "ID: " << id << "\n";
        std::cout << "Description: " << description << "\n";
        std::cout << "Amount: $" << amount << "\n";
        std::cout << "-----------------------------\n";
    }

    file.close();
}

void FinancialManager::UpdateExpense()
{
    int updateID;

    std::cout << "\n========== UPDATE EXPENSE ==========\n";
    std::cout << "Enter Expense ID to update: ";
    std::cin >> updateID;

    std::ifstream file("data/expense.txt");

    if (!file.is_open())
    {
        std::cout << "Error: Could not open expense.txt\n";
        return;
    }

    std::ofstream temp("data/temp.txt");

    int id;
    std::string description;
    double amount;
    std::string line;

    bool found = false;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        std::string token;

        std::getline(ss, token, '|');
        id = std::stoi(token);

        std::getline(ss, description, '|');

        std::getline(ss, token, '|');
        amount = std::stod(token);

        if (id == updateID)
        {
            found = true;

            std::cin.ignore();

            std::cout << "Enter new Description: ";
            std::getline(std::cin, description);

            std::cout << "Enter new Amount: $";
            std::cin >> amount;

            if (std::cin.fail() || amount <= 0)
            {
                std::cout << "Invalid amount.\n";

                file.close();
                temp.close();

                std::remove("data/temp.txt");

                return;
            }
        }

        temp << id << "|"
             << description << "|"
             << amount << "\n";
    }

    file.close();
    temp.close();

    std::remove("data/expense.txt");
    std::rename("data/temp.txt", "data/expense.txt");

    if (found)
    {
        std::cout << "Expense updated successfully!\n";
    }
    else
    {
        std::cout << "Expense ID not found!\n";
    }
}

void FinancialManager::DeleteExpense()
{
    int deleteID;

    std::cout << "\n========== DELETE EXPENSE ==========\n";
    std::cout << "Enter Expense ID to delete: ";
    std::cin >> deleteID;

    std::ifstream file("data/expense.txt");

    if (!file.is_open())
    {
        std::cout << "Error: Could not open expense.txt\n";
        return;
    }

    std::ofstream temp("data/temp.txt");

    int id;
    std::string description;
    double amount;
    std::string line;

    bool found = false;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        std::string token;

        std::getline(ss, token, '|');
        id = std::stoi(token);

        std::getline(ss, description, '|');

        std::getline(ss, token, '|');
        amount = std::stod(token);

        if (id == deleteID)
        {
            found = true;
            continue;
        }

        temp << id << "|"
             << description << "|"
             << amount << "\n";
    }

    file.close();
    temp.close();

    std::remove("data/expense.txt");
    std::rename("data/temp.txt", "data/expense.txt");

    if (found)
    {
        std::cout << "Expense deleted successfully!\n";
    }
    else
    {
        std::cout << "Expense ID not found!\n";
    }
}

void FinancialManager::viewStaffSummary()
{
    StaffSummary staffData = readStaffSummary();

    std::cout << "\n========== STAFF SUMMARY ==========\n";
    std::cout << "Total Staff     : " << staffData.count << std::endl;
    std::cout << "Total Salary    : $" << std::fixed << std::setprecision(2)
              << staffData.totalSalary << std::endl;
    std::cout << "===================================\n";
}

void FinancialManager::viewProfit()
{
    calculateSales();

    double manualIncome = manualIncomeTotal();
    double totalIncome = totalSales + manualIncome;

    StaffSummary staffData = readStaffSummary();
    double totalExpense = staffData.totalSalary + expenseTotalFromFile();

    double profit = totalIncome - totalExpense;

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "\n========== PROFIT ==========\n";
    std::cout << "Total Income    : $" << totalIncome << std::endl;
    std::cout << "Total Expenses  : $" << totalExpense << std::endl;
    std::cout << "Profit          : $" << profit << std::endl;
    std::cout << "============================\n";
}

void FinancialManager::viewSummary()
{
    calculateSales();

    double manualIncome = manualIncomeTotal();
    double totalIncome = totalSales + manualIncome;

    StaffSummary staffData = readStaffSummary();
    double otherExpense = expenseTotalFromFile();
    double totalExpense = staffData.totalSalary + otherExpense;

    double profit = totalIncome - totalExpense;

    std::cout << "\n========== FINANCIAL SUMMARY ==========\n";

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Revenue         : $" << totalSales << std::endl;
    std::cout << "Manual Income   : $" << manualIncome << std::endl;
    std::cout << "Total Income    : $" << totalIncome << std::endl;
    std::cout << "Staff Salary    : $" << staffData.totalSalary << std::endl;
    std::cout << "Other Expenses  : $" << otherExpense << std::endl;
    std::cout << "Total Expenses  : $" << totalExpense << std::endl;
    std::cout << "Profit          : $" << profit << std::endl;

    std::cout << "=======================================\n";
}

void FinancialManager::run()
{
    int option = 0;

    auto incomeMenu = [this]() {
        int sub = 0;

        do
        {
            std::cout << "\n========== INCOME MANAGEMENT ==========\n";
            std::cout << "1. View Revenue\n";
            std::cout << "2. Add Income\n";
            std::cout << "3. View Income\n";
            std::cout << "4. Update Income\n";
            std::cout << "5. Delete Income\n";
            std::cout << "6. Back\n";
            std::cout << "======================================\n";
            std::cout << "Enter your option : ";

            std::cin >> sub;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(),
                    '\n');
                std::cout << "Invalid option.\n";
                continue;
            }

            switch (sub)
            {
            case 1:
            {
                calculateSales();

                double manualIncome = manualIncomeTotal();
                double totalIncome = totalSales + manualIncome;

                std::cout << std::fixed << std::setprecision(2);
                std::cout << "\nRevenue         : $" << totalSales << std::endl;
                std::cout << "Manual Income   : $" << manualIncome << std::endl;
                std::cout << "Total Income    : $" << totalIncome << std::endl;
                std::cout << "\nPress Enter to return...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 2:
                AddIncome();
                break;
            case 3:
                ReadIncome();
                break;
            case 4:
                UpdateIncome();
                break;
            case 5:
                DeleteIncome();
                break;
            case 6:
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
                break;
            }
        } while (sub != 6);
    };

    auto expenseMenu = [this]() {
        int sub = 0;

        do
        {
            std::cout << "\n========== EXPENSE MANAGEMENT ==========\n";
            std::cout << "1. Add Expense\n";
            std::cout << "2. View Expense\n";
            std::cout << "3. Update Expense\n";
            std::cout << "4. Delete Expense\n";
            std::cout << "5. Back\n";
            std::cout << "=======================================\n";
            std::cout << "Enter your option : ";

            std::cin >> sub;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(),
                    '\n');
                std::cout << "Invalid option.\n";
                continue;
            }

            switch (sub)
            {
            case 1:
                AddExpense();
                break;
            case 2:
                ReadExpense();
                break;
            case 3:
                UpdateExpense();
                break;
            case 4:
                DeleteExpense();
                break;
            case 5:
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
                break;
            }
        } while (sub != 5);
    };

    auto reportMenu = [this]() {
        int sub = 0;

        do
        {
            std::cout << "\n========== FINANCIAL REPORTS ==========\n";
            std::cout << "1. View Staff Summary\n";
            std::cout << "2. View Profit\n";
            std::cout << "3. View Financial Summary\n";
            std::cout << "4. Back\n";
            std::cout << "=======================================\n";
            std::cout << "Enter your option : ";

            std::cin >> sub;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(),
                    '\n');
                std::cout << "Invalid option.\n";
                continue;
            }

            switch (sub)
            {
            case 1:
                viewStaffSummary();
                break;
            case 2:
                viewProfit();
                break;
            case 3:
                viewSummary();
                break;
            case 4:
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
                break;
            }
        } while (sub != 4);
    };

    do
    {
        std::cout << "\n========== FINANCIAL MANAGEMENT ==========\n";
        std::cout << "1. Income Management\n";
        std::cout << "2. Expense Management\n";
        std::cout << "3. Financial Reports\n";
        std::cout << "4. Back\n";
        std::cout << "==========================================\n";
        std::cout << "Enter your option : ";

        std::cin >> option;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n');

            std::cout << "Invalid option.\n";
            continue;
        }

        switch (option)
        {
        case 1:
            incomeMenu();
            break;
        case 2:
            expenseMenu();
            break;
        case 3:
            reportMenu();
            break;
        case 4:
            std::cout << "Back to Main Menu...\n";
            break;
        default:
            std::cout << "Invalid option. Please try again.\n";
            break;
        }
    } while (option != 4);
}
