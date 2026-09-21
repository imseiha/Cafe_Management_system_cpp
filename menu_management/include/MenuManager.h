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
    void updateItem();
    void deleteItem();
    void searchItems();
    void viewProduct();
    void exportToExcel();

public:
    MenuManager();

    void viewItems();
    bool getItemById(int id, MenuItem& item) const;
    bool reduceStock(int itemId, int quantity);
    void run();
};

#endif
