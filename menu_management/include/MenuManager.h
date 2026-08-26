#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <vector>
#include <string>
#include "MenuItem.h"

class MenuManager {
private:
    std::vector<MenuItem> items;
    const std::string filename = "data/menu.txt";
    const std::string excelFilename = "data/menu_export.csv";

    void loadFromFile();
    void saveToFile();
    void addItem();
    void viewItems();
    void updateItem();
    void deleteItem();
    void exportToExcel();

public:
    void run();
};

#endif
