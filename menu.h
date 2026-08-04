#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

const int W_ID = 6, W_NAME = 20, W_PRICE = 10, W_STOCK = 8;

class Menuitems{
    private:
        int id;
        int stock;
        float price;
        std::string name;
    public:
        Menuitems() : id(0), stock(0), price(0.0f), name("") {}

        Menuitems(int id, const std::string& name, double price, int stock)
            : id(id), stock(stock), price(price), name(name) {}

        // Getters
        int getId() const { return id; }
        int getStock() const { return stock; }
        float getPrice() const { return price; }
        std::string getName() const { return name; }

        // Setters
        void setId(int newId){
            this->id = newId;
        }
        void setStock(int newStock){
            this->stock = newStock; 
        }
        void setPrice(float newPrice){ 
            this->price = newPrice; 
        }
        void setName(const std::string& newName){
             this->name = newName; 
        }
        void reduceStock(int quantity) {
            stock -= quantity; 
        }

        std::string tofile() const {
            std::ostringstream oss;
            oss << id << "," << name << "," << price << "," << stock;
            return oss.str();
        }

        // Static method to create a Menuitems object from a string
        static Menuitems fromfile(const std::string& data){
            std::stringstream ss(data);
            std::string idStr, name, priceStr, stockStr;

            std::getline(ss, idStr, ',');
            std::getline(ss, name, ',');
            std::getline(ss, priceStr, ',');
            std::getline(ss, stockStr, ',');

            // Convert the strings to appropriate types and create a Menuitems object
            return Menuitems(std::stoi(idStr), name, std::stof(priceStr), std::stoi(stockStr));
        }

        void display() const {
            std::cout << "|" << std::left  << std::setw(W_ID) << id
                    << "|" << std::left  << std::setw(W_NAME) << name
                    << "|" << std::right << std::fixed << std::setprecision(2)
                                            << std::setw(W_PRICE - 1) << price << " "
                    << "|" << std::right << std::setw(W_STOCK - 1) << stock << " "
                    << "|" << std::endl;
        }
};

#endif