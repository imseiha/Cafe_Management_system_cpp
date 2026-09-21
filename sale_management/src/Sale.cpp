#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include "SaleManager.h"
#include "Sale.h"

#ifdef _WIN32
#include <windows.h>
#endif


const std::string ordersFilename = "data/orders.txt";
const std::string receiptsFilename = "data/receipts.txt";

namespace
{
    bool isDigits(const std::string &value)
    {
        if (value.empty())
        {
            return false;
        }

        for (char character : value)
        {
            if (character < '0' || character > '9')
            {
                return false;
            }
        }
        return true;
    }

    bool isValidReceiptId(const std::string &receiptId)
    {
        return receiptId.size() == 5 && isDigits(receiptId);
    }

    bool isValidOrderId(const std::string &orderId)
    {
        return orderId.size() == 15 && isDigits(orderId);
    }

    std::string extractStaffId(const std::string &receiptText)
    {
        size_t position = receiptText.find("Staff ID:");
        if (position == std::string::npos)
        {
            return "";
        }

        position += 9;

        std::string digits;
        for (; position < receiptText.size(); ++position)
        {
            char character = receiptText[position];
            if (character >= '0' && character <= '9')
            {
                digits += character;
            }
            else if (character == '\n')
            {
                break;
            }
        }
        return digits;
    }

    void printMatchingReceipts(const std::string &searchText, bool searchDate, bool searchStaffId)
    {
#ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
#endif
        std::ifstream file(receiptsFilename);
        if (!file.is_open())
        {
            std::cout << "No receipts found in " << receiptsFilename << "." << std::endl;
            return;
        }

        std::string line;
        std::string receipt;
        std::string sale;
        bool found = false;

        auto printReceiptIfMatched = [&]()
        {
            if (receipt.empty())
            {
                return;
            }

            bool matches = false;
            if (searchStaffId)
            {
                matches = !extractStaffId(receipt).empty() && extractStaffId(receipt) == searchText;
            }
            else if (searchDate)
            {
                matches = receipt.find("Date:") != std::string::npos && receipt.find(searchText) != std::string::npos;
            }
            else
            {
                matches = receipt.find(searchText) != std::string::npos;
            }

            if (matches)
            {
                std::cout << receipt << std::endl;
                found = true;
            }
            receipt.clear();
        };

        while (std::getline(file, line))
        {
            if (line.empty())
            {
                printReceiptIfMatched();
            }
            else
            {
                if (!receipt.empty())
                {
                    receipt += "\n";
                }
                receipt += line;
            }
        }
        printReceiptIfMatched();

        if (!found)
        {
            std::cout << "No matching receipt found." << std::endl;
        }
    }

}

void Sale::searchReceiptById()
    {
        std::string receiptId;
        std::cout << "Enter receipt ID (5 digits): ";
        std::cin >> receiptId;

        if (!isValidReceiptId(receiptId))
        {
            std::cout << "Invalid receipt ID. Enter exactly 5 digits, for example 00011." << std::endl;
            return;
        }

        printMatchingReceipts("#" + receiptId, false, false);
    }

void Sale::searchReceiptByOrderId()
    {
        std::string orderId;
        std::cout << "Enter order ID (15 digits): ";
        std::cin >> orderId;

        if (!isValidOrderId(orderId))
        {
            std::cout << "Invalid order ID. Enter exactly 15 digits, for example 200926174834011." << std::endl;
            return;
        }

        printMatchingReceipts(orderId, false, false);
    }

void Sale::searchReceiptByDate()
    {
        std::string date;
        std::cout << "Enter date (YYYY-MM-DD): ";
        std::cin >> date;
        printMatchingReceipts(date, true, false);
    }

void Sale::searchReceiptByStaffId()
    {
        std::string staffId;
        std::cout << "Enter staff ID: ";
        std::cin >> staffId;

        if (!isDigits(staffId))
        {
            std::cout << "Invalid staff ID. Enter a number." << std::endl;
            return;
        }

        printMatchingReceipts(staffId, false, true);
    }

    void printMatchingSales(const std::string &searchText, bool searchDate)
    {
        std::ifstream file(ordersFilename);
        if (!file.is_open())
        {
            std::cout << "No sales found in " << ordersFilename << "." << std::endl;
            return;
        }

        bool foundSale = false;
        std::string line;

        struct ItemSummary
        {
            int customerCount = 0;
            int quantity = 0;
            double totalPrice = 0.0;
        };
        std::map<std::string, ItemSummary> itemSummaries;

        std::cout << "\n========== DETAILED SALES ==========" << std::endl;
        std::cout << std::left << std::setw(8) << "Order ID"
              << std::setw(20) << "Item"
              << std::right << std::setw(8) << "Qty"
              << std::setw(14) << "Unit Price ($)"
              << std::setw(14) << "Total ($)"
              << "  Date" << std::endl;
        std::cout << std::string(82, '-') << std::endl;

        while (std::getline(file, line))
        {
            if (line.empty())
            {
                continue;
            }

            std::stringstream stream(line);
            std::string token;
            int id = 0;
            int itemId = 0;
            int quantity = 0;
            double unitPrice = 0.0;
            double total = 0.0;
            std::string itemName;
            std::string createdAt;

            try
            {
                std::getline(stream, token, '|');
                id = std::stoi(token);
                std::getline(stream, token, '|');
                itemId = std::stoi(token);
                (void)itemId;
                std::getline(stream, itemName, '|');
                std::getline(stream, token, '|');
                quantity = std::stoi(token);
                std::getline(stream, token, '|');
                unitPrice = std::stod(token);
                std::getline(stream, token, '|');
                total = std::stod(token);
                std::getline(stream, createdAt, '|');
            }
            catch (const std::exception&)
            {
                std::cout << "Warning: skipping corrupted line in " << ordersFilename << "." << std::endl;
                continue;
            }

            bool matches = searchDate ? createdAt.compare(0, searchText.size(), searchText) == 0
                                      : std::to_string(id) == searchText;
            if (!matches)
            {
                continue;
            }

            std::cout << std::left << std::setw(8) << id
                      << std::setw(20) << itemName.substr(0, 19)
                      << std::right << std::setw(8) << quantity
                      << std::setw(14) << std::fixed << std::setprecision(2) << unitPrice
                      << std::setw(14) << total
                      << "  " << createdAt << std::endl;

            ItemSummary &summary = itemSummaries[itemName];
            ++summary.customerCount;
            summary.quantity += quantity;
            summary.totalPrice += total;
            foundSale = true;
        }

        if (!foundSale)
        {
            std::cout << "No matching sale found." << std::endl;
            return;
        }

        std::cout << "\n========== ITEM SUMMARY ==========" << std::endl;
        std::cout << std::left << std::setw(24) << "Item"
                  << std::right << std::setw(12) << "Customers"
                  << std::setw(12) << "Quantity"
                  << std::setw(16) << "Price ($)" << std::endl;
        std::cout << std::string(64, '-') << std::endl;

        int customerCount = 0;
        int itemCount = 0;
        double totalPrice = 0.0;
        for (const auto &entry : itemSummaries)
        {
            const ItemSummary &summary = entry.second;
            std::cout << std::left << std::setw(24) << entry.first.substr(0, 23)
                      << std::right << std::setw(12) << summary.customerCount
                      << std::setw(12) << summary.quantity
                      << std::setw(16) << std::fixed << std::setprecision(2)
                      << summary.totalPrice << std::endl;

            customerCount += summary.customerCount;
            itemCount += summary.quantity;
            totalPrice += summary.totalPrice;
        }

        std::cout << std::string(64, '-') << std::endl;
    std::cout << "========== TOTALS ==========" << std::endl;
        std::cout << "Customer count: " << customerCount << std::endl;
    std::cout << "Total quantity: " << itemCount << std::endl;
        std::cout << "Total price: $" << std::fixed << std::setprecision(2) << totalPrice << std::endl;
    }

void Sale::searchSaleById()
    {
        int saleId;
        std::cout << "Enter sale ID: ";
        std::cin >> saleId;
        printMatchingSales(std::to_string(saleId), false);
    }

void Sale::searchSaleByDate()
    {
        std::string date;
        std::cout << "Enter date (YYYY-MM-DD): ";
        std::cin >> date;
        printMatchingSales(date, true);
    }
void Sale::viewSalesFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cout << "No sales found in " << filepath << "." << std::endl;
        return;
    }

    bool foundSale = false;
    std::string line;

    struct ItemSummary
    {
        int customerCount = 0;
        int quantity = 0;
        double totalPrice = 0.0;
    };
    std::map<std::string, ItemSummary> itemSummaries;

    std::cout << "\n========== DETAILED SALES ==========" << std::endl;
    std::cout << std::left << std::setw(8) << "Order ID"
              << std::setw(20) << "Item"
              << std::right << std::setw(8) << "Qty"
              << std::setw(14) << "Unit Price ($)"
              << std::setw(14) << "Total ($)"
              << "  Date" << std::endl;
    std::cout << std::string(82, '-') << std::endl;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream stream(line);
        std::string token;
        int id = 0;
        int itemId = 0;
        int quantity = 0;
        double unitPrice = 0.0;
        double total = 0.0;
        std::string itemName;
        std::string createdAt;

        try {
            std::getline(stream, token, '|');
            id = std::stoi(token);
            std::getline(stream, token, '|');
            itemId = std::stoi(token);
            (void)itemId;
            std::getline(stream, itemName, '|');
            std::getline(stream, token, '|');
            quantity = std::stoi(token);
            std::getline(stream, token, '|');
            unitPrice = std::stod(token);
            std::getline(stream, token, '|');
            total = std::stod(token);
            std::getline(stream, createdAt, '|');
        } catch (const std::exception&) {
            std::cout << "Warning: skipping corrupted line in " << filepath << "." << std::endl;
            continue;
        }

        (void)id;
        (void)unitPrice;
        (void)createdAt;
        std::cout << std::left << std::setw(8) << id
              << std::setw(20) << itemName.substr(0, 19)
              << std::right << std::setw(8) << quantity
              << std::setw(14) << std::fixed << std::setprecision(2) << unitPrice
              << std::setw(14) << total
              << "  " << createdAt << std::endl;

        ItemSummary &summary = itemSummaries[itemName];
        ++summary.customerCount;
        summary.quantity += quantity;
        summary.totalPrice += total;
        foundSale = true;
    }

    if (!foundSale) {
        std::cout << "No sales found in " << filepath << "." << std::endl;
        return;
    }

    std::cout << "\n========== ITEM SUMMARY ==========" << std::endl;
    std::cout << std::left << std::setw(24) << "Item"
              << std::right << std::setw(12) << "Customers"
              << std::setw(12) << "Quantity"
              << std::setw(16) << "Price ($)" << std::endl;
    std::cout << std::string(64, '-') << std::endl;

    int customerCount = 0;
    int itemCount = 0;
    double totalPrice = 0.0;
    for (const auto &entry : itemSummaries)
    {
        const ItemSummary &summary = entry.second;
        std::cout << std::left << std::setw(24) << entry.first.substr(0, 23)
                  << std::right << std::setw(12) << summary.customerCount
                  << std::setw(12) << summary.quantity
                  << std::setw(16) << std::fixed << std::setprecision(2)
                  << summary.totalPrice << std::endl;

        customerCount += summary.customerCount;
        itemCount += summary.quantity;
        totalPrice += summary.totalPrice;
    }

    std::cout << std::string(64, '-') << std::endl;
    std::cout << "Different items: " << itemSummaries.size() << std::endl;
    std::cout << "Customer count: " << customerCount << std::endl;
    std::cout << "Total quantity: " << itemCount << std::endl;
    std::cout << "Total price: $" << std::fixed << std::setprecision(2) << totalPrice << std::endl;
}