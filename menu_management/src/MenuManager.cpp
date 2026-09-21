#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cctype>
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

static std::string money(double value) {
    std::ostringstream out;
    out << "$" << std::fixed << std::setprecision(2) << value;
    return out.str();
}

static std::string stockStatus(int stock) {
    if (stock == 0) return "OUT OF STOCK";
    if (stock <= 5) return "LOW STOCK";
    return "IN STOCK";
}

static void printBorder() {
    std::cout << "=================================================================================================\n";
}

static void printTableHeader() {
    printBorder();
    std::cout << std::left
              << std::setw(6) << "ID"
              << std::setw(24) << "NAME"
              << std::setw(18) << "CATEGORY"
              << std::setw(12) << "PRICE"
              << std::setw(15) << "PRODUCT COST"
              << std::setw(8) << "STOCK"
              << "STATUS\n";
    printBorder();
}

static void printItemRow(const MenuItem& item) {
    std::cout << std::left
              << std::setw(6) << item.getId()
              << std::setw(24) << item.getName().substr(0, 23)
              << std::setw(18) << item.getCategory().substr(0, 17)
              << std::setw(12) << money(item.getPrice())
              << std::setw(15) << money(item.getProductCost())
              << std::setw(8) << item.getStock()
              << stockStatus(item.getStock()) << "\n";
}

static void printProductDetails(const MenuItem& item) {
    std::cout << "\n===============================================================\n";
    std::cout << "PRODUCT DETAILS\n";
    std::cout << "===============================================================\n";
    std::cout << "ID           : " << item.getId() << "\n";
    std::cout << "Name         : " << item.getName() << "\n";
    std::cout << "Category     : " << item.getCategory() << "\n";
    std::cout << "Selling Price: " << money(item.getPrice()) << "\n";
    std::cout << "Product Cost : " << money(item.getProductCost()) << "\n";
    std::cout << "Stock        : " << item.getStock() << "\n";
    std::cout << "Status       : " << stockStatus(item.getStock()) << "\n";
    std::cout << "===============================================================\n";
}

MenuManager::MenuManager() {
    loadFromFile();
}

void MenuManager::run() {
    loadFromFile();
    int option = 0;
    do {
        std::cout << "\n===============================================================\n";
        std::cout << "MENU MANAGEMENT\n";
        std::cout << "===============================================================\n";
        viewItems();
        std::cout << "Total Products: " << items.size() << "\n\n";
        std::cout << "[1] Add Product\n[2] Edit Product\n[3] Delete Product\n";
        std::cout << "[4] Search Product\n[5] View Product\n[6] Export to Excel\n[7] Back\n";
        std::cout << "Enter your choice: ";
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
                updateItem();
                break;
            }
            case 3: {
                deleteItem();
                break;
            }
            case 4: {
                searchItems();
                break;
            }
            case 5: {
                viewProduct();
                break;
            }
            case 6: {
                exportToExcel();
                break;
            }
            case 7: {
                break;
            }
            default: {
                std::cout << "Invalid option. Please try again." << std::endl;
                break;
            }
        }
    } while (option != 7);
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

    std::cout << "\n===============================================================\nADD NEW PRODUCT\n===============================================================\n";
    std::cout << "Name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);
    if (name.empty()) {
        std::cout << "Product name cannot be empty.\n";
        return;
    }
    std::cout << "Category: ";
    std::getline(std::cin, category);
    std::cout << "Price: ";
    if (!(std::cin >> price)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid price. Product not added.\n";
        return;
    }
    std::cout << "Product Cost: ";
    if (!(std::cin >> productCost)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid product cost. Product not added.\n";
        return;
    }
    std::cout << "Stock: ";
    if (!(std::cin >> stock)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid stock. Product not added.\n";
        return;
    }
    if (price < 0 || productCost < 0 || stock < 0) {
        std::cout << "Price, product cost, and stock cannot be negative.\n";
        return;
    }

    int saveChoice = 0;
    std::cout << "\n[1] Save\n[2] Cancel\nEnter your choice: ";
    if (!(std::cin >> saveChoice) || (saveChoice != 1 && saveChoice != 2)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Product not added.\n";
        return;
    }
    if (saveChoice == 2) {
        std::cout << "Product creation cancelled.\n";
        return;
    }

    items.push_back(MenuItem(nextId, name, category, price, productCost, stock));
    saveToFile();
    std::cout << "Product added successfully with ID " << nextId << ".\n";
}

void MenuManager::viewItems() {
    if (items.empty()) {
        std::cout << "No products found.\n";
        return;
    }
    printTableHeader();
    for (const MenuItem& item : items) {
        printItemRow(item);
    }
    printBorder();
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
    std::cout << "Enter Product ID to edit: ";
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

            std::cout << "\n===============================================================\nEDIT PRODUCT\n===============================================================\n";
            printProductDetails(item);
            std::cout << "Enter the new values.\nName: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, name);
            std::cout << "Category: ";
            std::getline(std::cin, category);
            std::cout << "Price: ";
            if (!(std::cin >> price)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid price. Item not updated." << std::endl;
                return;
            }
            std::cout << "Product Cost: ";
            if (!(std::cin >> productCost)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid product cost. Item not updated." << std::endl;
                return;
            }
            std::cout << "Stock: ";
            if (!(std::cin >> stock)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid stock. Item not updated." << std::endl;
                return;
            }

            if (name.empty() || price < 0 || productCost < 0 || stock < 0) {
                std::cout << "Name cannot be empty and numeric values cannot be negative. Product not updated.\n";
                return;
            }

            item.setName(name);
            item.setCategory(category);
            item.setPrice(price);
            item.setProductCost(productCost);
            item.setStock(stock);
            saveToFile();
            std::cout << "Product updated successfully." << std::endl;
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
    std::cout << "Enter Product ID to delete: ";
    if (!(std::cin >> id)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid ID." << std::endl;
        return;
    }

    for (std::vector<MenuItem>::iterator it = items.begin(); it != items.end(); ++it) {
        if (it->getId() == id) {
            printProductDetails(*it);
            int confirmation = 0;
            std::cout << "Are you sure you want to delete this product?\n[1] Yes\n[2] No\nEnter your choice: ";
            if (!(std::cin >> confirmation) || (confirmation != 1 && confirmation != 2)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid choice. Product was not deleted.\n";
                return;
            }
            if (confirmation == 2) {
                std::cout << "Product deletion cancelled.\n";
                return;
            }
            items.erase(it);
            saveToFile();
            std::cout << "Product deleted successfully." << std::endl;
            return;
        }
    }
    std::cout << "Item with ID " << id << " not found." << std::endl;
}

void MenuManager::searchItems() {
    std::cout << "\n===============================================================\nSEARCH PRODUCT\n===============================================================\n";
    std::cout << "Search by ID, name, or category: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string query;
    std::getline(std::cin, query);
    std::transform(query.begin(), query.end(), query.begin(),
                   [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

    std::vector<MenuItem> results;
    for (const MenuItem& item : items) {
        std::string name = item.getName();
        std::string category = item.getCategory();
        std::transform(name.begin(), name.end(), name.begin(),
                       [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
        std::transform(category.begin(), category.end(), category.begin(),
                       [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
        if (std::to_string(item.getId()).find(query) != std::string::npos ||
            name.find(query) != std::string::npos || category.find(query) != std::string::npos) {
            results.push_back(item);
        }
    }

    if (results.empty()) {
        std::cout << "No products found.\n";
        return;
    }
    printTableHeader();
    for (const MenuItem& item : results) printItemRow(item);
    printBorder();
}

void MenuManager::viewProduct() {
    int id = 0;
    std::cout << "Enter Product ID to view: ";
    if (!(std::cin >> id)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid ID.\n";
        return;
    }
    MenuItem item;
    if (!getItemById(id, item)) {
        std::cout << "Product with ID " << id << " not found.\n";
        return;
    }
    printProductDetails(item);
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
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
