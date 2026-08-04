#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <sstream>
#include <iostream>

// Represents one item on the café menu (e.g. Cappuccino, Espresso)
class MenuItem {
private:
    int id;
    std::string name;
    double price;
    int stock;

public:
    // Constructors
    MenuItem() : id(0), name(""), price(0.0), stock(0) {}

    MenuItem(int id, const std::string& name, double price, int stock)
        : id(id), name(name), price(price), stock(stock) {}

    // Getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    // Setters
    void setName(const std::string& newName) { name = newName; }
    void setPrice(double newPrice) { price = newPrice; }
    void setStock(int newStock) { stock = newStock; }
    void reduceStock(int qty) { stock -= qty; }

    // Convert this object to a single CSV line: "1001,Cappuccino,3.50,25"
    std::string toCSV() const {
        std::ostringstream oss;
        oss << id << "," << name << "," << price << "," << stock;
        return oss.str();
    }

    // Build a MenuItem from a CSV line
    static MenuItem fromCSV(const std::string& line) {
        std::stringstream ss(line);
        std::string idStr, name, priceStr, stockStr;

        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, priceStr, ',');
        std::getline(ss, stockStr, ',');

        return MenuItem(std::stoi(idStr), name, std::stod(priceStr), std::stoi(stockStr));
    }

    // Nicely print item details
    void display() const {
        std::cout << id << "\t" << name << "\t$" << price << "\t" << stock << " in stock\n";
    }
};

#endif