#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

struct MenuItem {
    int id;
    std::string name;
    double price;
    std::string category;
};

class Menu {
public:
    Menu();
    void addItem(const MenuItem& item);
    void showMenu() const;
    void loadFromFile(const std::string& filePath);
    const std::vector<MenuItem>& getItems() const;

private:
    std::vector<MenuItem> items_;
};

#endif
