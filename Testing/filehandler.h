#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "menu.h"
#include "order.h"

// Handles all reading/writing of data to CSV files.
// Keeping file I/O in one place means the rest of the program
// never has to worry about how data is stored on disk.
class FileHandler {
public:
    // ---------- MENU ITEMS ----------

    static void saveMenu(const std::string& filename, const std::vector<MenuItem>& items) {
        std::ofstream outFile(filename);
        if (!outFile) {
            std::cerr << "Error: could not open " << filename << " for writing.\n";
            return;
        }
        for (const auto& item : items) {
            outFile << item.toCSV() << "\n";
        }
        outFile.close();
    }

    static std::vector<MenuItem> loadMenu(const std::string& filename) {
        std::vector<MenuItem> items;
        std::ifstream inFile(filename);

        if (!inFile) {
            // File doesn't exist yet — that's fine on first run, just return empty list
            std::cerr << "Note: " << filename << " not found. Starting with empty menu.\n";
            return items;
        }

        std::string line;
        while (std::getline(inFile, line)) {
            if (!line.empty()) {
                items.push_back(MenuItem::fromCSV(line));
            }
        }
        inFile.close();
        return items;
    }

    // ---------- ORDERS ----------

    static void saveOrders(const std::string& filename, const std::vector<Order>& orders) {
        std::ofstream outFile(filename);
        if (!outFile) {
            std::cerr << "Error: could not open " << filename << " for writing.\n";
            return;
        }
        for (const auto& order : orders) {
            outFile << order.toCSV() << "\n";
        }
        outFile.close();
    }

    static std::vector<Order> loadOrders(const std::string& filename) {
        std::vector<Order> orders;
        std::ifstream inFile(filename);

        if (!inFile) {
            std::cerr << "Note: " << filename << " not found. Starting with empty order history.\n";
            return orders;
        }

        std::string line;
        while (std::getline(inFile, line)) {
            if (!line.empty()) {
                orders.push_back(Order::fromCSV(line));
            }
        }
        inFile.close();
        return orders;
    }

    // Appends a single order to the file without rewriting everything
    // (handy for saving right after each transaction)
    static void appendOrder(const std::string& filename, const Order& order) {
        std::ofstream outFile(filename, std::ios::app);
        if (!outFile) {
            std::cerr << "Error: could not open " << filename << " for appending.\n";
            return;
        }
        outFile << order.toCSV() << "\n";
        outFile.close();
    }
};

#endif