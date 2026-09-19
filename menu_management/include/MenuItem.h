#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>

class MenuItem {
private:
    int id;
    std::string name;
    std::string category;
    double price;
    int stock;

public:
    MenuItem();
    MenuItem(int id, const std::string& name, const std::string& category, double price, int stock);

    int getId() const;
    std::string getName() const;
    std::string getCategory() const;
    double getPrice() const;
    int getStock() const;

    void setId(int id);
    void setName(const std::string& name);
    void setCategory(const std::string& category);
    void setPrice(double price);
    void setStock(int stock);

    std::string toFileString() const;
    void display() const;
};

#endif
