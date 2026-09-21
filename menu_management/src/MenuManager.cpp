#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <windows.h>
#include "MenuManager.h"

static std::string csvField(const std::string& value) {
    std::string escaped = value;
    size_t pos = 0;
    while ((pos = escaped.find('"', pos)) != std::string::npos) {
        escaped.replace(pos, 1, "\"\"");
        pos += 2;
    }
    return "\"" + escaped + "\"";
}

MenuManager::MenuManager() {
    loadFromFile();
}

void MenuManager::run() {
    loadFromFile();
    int option = 0;
    do {
        std::cout << std::endl;
        std::cout << "===== Menu Management =====" << std::endl;
        std::cout << "1.Add Item" << std::endl;
        std::cout << "2.View Items" << std::endl;
        std::cout << "3.Update Item" << std::endl;
        std::cout << "4.Delete Item" << std::endl;
        std::cout << "5.Export to Excel" << std::endl;
        std::cout << "6.Back" << std::endl;
        std::cout << "===========================" << std::endl;
        std::cout << "Enter your option : ";
        if (!(std::cin >> option)) {
            if (std::cin.eof()) {
                break;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid option. Please try again." << std::endl;
            continue;
        }

        switch (option) {
            case 1: {
                addItem();
                break;
            }
            case 2: {
                viewItems();
                break;
            }
            case 3: {
                updateItem();
                break;
            }
            case 4: {
                deleteItem();
                break;
            }
            case 5: {
                exportToExcel();
                break;
            }
            case 6: {
                break;
            }
            default: {
                std::cout << "Invalid option. Please try again." << std::endl;
                break;
            }
        }
    } while (option != 6);
}

void MenuManager::loadFromFile() {
    items.clear();
    std::ifstream file(filename);
    if (!file.is_open()) {
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::stringstream ss(line);
        std::string token;
        int id = 0;
        double price = 0.0;
        double productCost = 0.0;
        int stock = 0;
        std::string name;
        std::string category;

        try {
            std::getline(ss, token, '|');
            id = std::stoi(token);
            std::getline(ss, name, '|');
            std::getline(ss, category, '|');
            std::getline(ss, token, '|');
            price = std::stod(token);
            if (std::getline(ss, token, '|')) {
                std::string stockToken;
                if (std::getline(ss, stockToken, '|')) {
                    productCost = std::stod(token);
                    stock = std::stoi(stockToken);
                } else {
                    // Old records used id|name|category|price|stock and have no product cost.
                    stock = std::stoi(token);
                }
            } else {
                throw std::invalid_argument("missing stock");
            }
        } catch (const std::exception&) {
            std::cout << "Warning: skipping corrupted line in " << filename << "." << std::endl;
            continue;
        }

        items.push_back(MenuItem(id, name, category, price, productCost, stock));
    }
    file.close();
}

void MenuManager::saveToFile() {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: could not open " << filename << " for saving." << std::endl;
        return;
    }
    for (const MenuItem& item : items) {
        file << item.toFileString() << std::endl;
    }
    file.close();
}

void MenuManager::addItem() {
    std::string name;
    std::string category;
    double price = 0.0;
    double productCost = 0.0;
    int stock = 0;

    int nextId = 0;
    for (const MenuItem& item : items) {
        if (item.getId() > nextId) {
            nextId = item.getId();
        }
    }
    nextId++;

    std::cout << "Enter item name : ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter category : ";
    std::getline(std::cin, category);
    std::cout << "Enter product cost : ";
    if (!(std::cin >> productCost)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid product cost. Item not added." << std::endl;
        return;
    }
    std::cout << "Enter price : ";
    if (!(std::cin >> price)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid price. Item not added." << std::endl;
        return;
    }
    std::cout << "Enter stock : ";
    if (!(std::cin >> stock)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid stock. Item not added." << std::endl;
        return;
    }

    items.push_back(MenuItem(nextId, name, category, price, productCost, stock));
    saveToFile();
    std::cout << "Item added successfully with ID " << nextId << "." << std::endl;
}

void MenuManager::viewItems() {
    if (items.empty()) {
        std::cout << "No menu items found." << std::endl;
        return;
    }
    std::cout << "ID\tName\tCategory\tPrice\tProduct Cost\tStock" << std::endl;
    for (const MenuItem& item : items) {
        item.display();
    }
}

bool MenuManager::getItemById(int id, MenuItem& item) const {
    for (const MenuItem& candidate : items) {
        if (candidate.getId() == id) {
            item = candidate;
            return true;
        }
    }
    return false;
}

bool MenuManager::reduceStock(int itemId, int quantity) {
    for (MenuItem& item : items) {
        if (item.getId() == itemId) {
            if (quantity > item.getStock()) {
                return false;
            }
            item.setStock(item.getStock() - quantity);
            saveToFile();
            return true;
        }
    }
    return false;
}

void MenuManager::updateItem() {
    if (items.empty()) {
        std::cout << "No menu items to update." << std::endl;
        return;
    }
    viewItems();
    int id = 0;
    std::cout << "Enter item ID to update : ";
    if (!(std::cin >> id)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid ID." << std::endl;
        return;
    }

    for (MenuItem& item : items) {
        if (item.getId() == id) {
            std::string name;
            std::string category;
            double price = 0.0;
            double productCost = 0.0;
            int stock = 0;

            std::cout << "Enter new name : ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter new category : ";
            std::getline(std::cin, category);
            std::cout << "Enter new price : ";
            if (!(std::cin >> price)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid price. Item not updated." << std::endl;
                return;
            }
            std::cout << "Enter new product cost : ";
            if (!(std::cin >> productCost)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid product cost. Item not updated." << std::endl;
                return;
            }
            std::cout << "Enter new stock : ";
            if (!(std::cin >> stock)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid stock. Item not updated." << std::endl;
                return;
            }

            item.setName(name);
            item.setCategory(category);
            item.setPrice(price);
            item.setProductCost(productCost);
            item.setStock(stock);
            saveToFile();
            std::cout << "Item updated successfully." << std::endl;
            return;
        }
    }
    std::cout << "Item with ID " << id << " not found." << std::endl;
}

void MenuManager::deleteItem() {
    if (items.empty()) {
        std::cout << "No menu items to delete." << std::endl;
        return;
    }
    viewItems();
    int id = 0;
    std::cout << "Enter item ID to delete : ";
    if (!(std::cin >> id)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid ID." << std::endl;
        return;
    }

    for (std::vector<MenuItem>::iterator it = items.begin(); it != items.end(); ++it) {
        if (it->getId() == id) {
            items.erase(it);
            saveToFile();
            std::cout << "Item deleted successfully." << std::endl;
            return;
        }
    }
    std::cout << "Item with ID " << id << " not found." << std::endl;
}

void MenuManager::exportToExcel() {
    if (items.empty()) {
        std::cout << "No menu items to export." << std::endl;
        return;
    }

    std::ofstream file(excelFilename);
    if (!file.is_open()) {
        std::cout << "Error: could not create " << excelFilename << "." << std::endl;
        return;
    }

    file << "\xEF\xBB\xBF";
    file << "ID,Name,Category,Price,Product Cost,Stock" << std::endl;
    for (const MenuItem& item : items) {
        file << item.getId() << ","
             << csvField(item.getName()) << ","
             << csvField(item.getCategory()) << ","
             << std::fixed << std::setprecision(2) << item.getPrice() << ","
             << std::fixed << std::setprecision(2) << item.getProductCost() << ","
             << item.getStock() << std::endl;
    }
    file.close();

    std::string winPath = excelFilename;
    std::replace(winPath.begin(), winPath.end(), '/', '\\');

    char fullPath[MAX_PATH];
    if (GetFullPathNameA(winPath.c_str(), MAX_PATH, fullPath, NULL)) {
        std::cout << "Exported " << items.size() << " item(s) to " << fullPath << std::endl;
    } else {
        std::cout << "Exported " << items.size() << " item(s) to " << winPath << std::endl;
    }

    HINSTANCE result = ShellExecuteA(NULL, "open", winPath.c_str(), NULL, NULL, SW_SHOWNORMAL);
    if (reinterpret_cast<intptr_t>(result) <= 32) {
        std::cout << "Could not open Excel automatically. Open the file manually from the path above." << std::endl;
    }
}
