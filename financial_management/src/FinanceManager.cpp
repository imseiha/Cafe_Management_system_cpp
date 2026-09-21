
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
    int id; 
    std::string description; 
    double amount; 
 
    std::cout << "\n========== ADD INCOME ==========\n"; 
 
    std::cout << "Enter Income ID: "; 
    std::cin >> id; 
 
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
 
    std::cout << "Income added successfully!\n"; 
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
            '\n'
        );

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
void FinancialManager::AddExpense ()
{
    int id;
    std::string description;
    double amount;

    std::cout << "\n========== ADD EXPENSE ==========\n";

    std::cout << "Enter Expense ID: ";
    std::cin >> id;

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
            '\n'
        );

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

    std::cout << "Expense added successfully!\n";
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

void FinancialManager::viewSummary()
{
    calculateSales();

    double profit = totalSales - totalExpense;

    std::cout << "\n========== FINANCIAL SUMMARY ==========\n";

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "INcome    : $" << totalSales << std::endl;
    std::cout << "Total Expenses : $" << totalExpense << std::endl;
    std::cout << "Profit         : $" << profit << std::endl;

    std::cout << "=======================================\n";
}

void FinancialManager::run()
{
    int option;

    do
    {
        std::cout << "\n========== FINANCIAL MANAGEMENT ==========\n";
        std::cout << "1. View INcome\n";
        std::cout << "2. Add Expense\n";
        std::cout << "3. View Financial Summary\n";
        std::cout << "4. Back\n";
        std::cout << "==========================================\n";

        std::cout << "Enter your option : ";
        std::cin >> option;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            std::cout << "Invalid option." << std::endl;
            continue;
        }

        switch (option)
        {
            case 1:
            {
                calculateSales();

                std::cout << std::fixed
                          << std::setprecision(2);

                std::cout << "\nINcome : $"
                          << totalSales
                          << std::endl;

                break;
            }

            case 2:
            {
                addExpense();
                break;
            }

            case 3:
            {
                viewSummary();
                break;
            }

    
            case 4 : {
                AddIncome();
                break;
            }
            case 5: {
                 ReadIncome();
                break;
            }
             case 6: {
                 UpdateIncome();
                break;
            }
            case 7: {
                 DeleteIncome();
                break;
            }


            case 8:
            {
                std::cout << "Back to Main Menu..." << std::endl;
                break;
            default:
            {
                std::cout << "Invalid option. Please try again."
                          << std::endl;
                break;
            }
        }
    }

        }while (option != 8);
    }