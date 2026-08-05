#include "Menu.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

Menu::Menu() = default;

void Menu::addItem(const MenuItem& item) {
    items_.push_back(item);
}

void Menu::showMenu() const {
    std::cout << "\n=== Cafe Menu ===\n";
    for (const auto& item : items_) {
        std::cout << item.id << ". " << item.name << " - $"
                  << std::fixed << std::setprecision(2) << item.price
                  << " [" << item.category << "]\n";
    }
    std::cout << "================\n";
}

void Menu::loadFromFile(const std::string& filePath) {
    std::ifstream input(filePath);
    if (!input) {
        std::cerr << "Unable to open menu file: " << filePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> values;

        while (std::getline(ss, token, ',')) {
            values.push_back(token);
        }

        if (values.size() < 4) {
            continue;
        }

        MenuItem item;
        item.id = std::stoi(values[0]);
        item.name = values[1];
        item.price = std::stod(values[2]);
        item.category = values[3];
        items_.push_back(item);
    }
}

const std::vector<MenuItem>& Menu::getItems() const {
    return items_;
}
