#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "TableFormat.h"
#include "Category.h"

class Menuitems{
    private:
        int id;
        int stock;
        float price;
        std::string name;
        std::string category;
    public:  
        Menuitems() : id(0), stock(0), price(0.0f), name(""), category("") {}

        Menuitems(int id, const std::string& name, double price, int stock, std::string category)
            : id(id), stock(stock), price(price), name(name), category(category) {}

        // Getters
        int getId() const {
            return id; 
        }
        int getStock() const {
            return stock; 
        }
        float getPrice() const {
            return price; 
        }
        std::string getName() const {
            return name; 
        }
        std::string getCategory() const {
            return category;
        }

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
        void setCategory(const std::string& newCategory){
            this->category = newCategory;
        }

        //save to file
        std::string tofile() const {
            std::ostringstream oss;
            oss << id << "," << name << "," << price << "," << stock;
            return oss.str();
        }
        // Static method to create a Menuitems object from a string
        static Menuitems fromfile(const std::string& data){
            std::stringstream ss(data);
            std::string idStr, name, priceStr, stockStr, category;

            std::getline(ss, idStr, ',');
            std::getline(ss, name, ',');
            std::getline(ss, priceStr, ',');
            std::getline(ss, stockStr, ',');
            std::getline(ss, category, ',');
            
            if(category.empty()){
                category = "Uncategorized";
            }

            // Convert the strings to appropriate types and create a Menuitems object
            return Menuitems(std::stoi(idStr), name, std::stof(priceStr), std::stoi(stockStr), category);
        }
        //flexible Menu display
        void display(int wId, int wName, int wPrice, int wStock, int wCategory) const {
            std::cout << "|" << std::left << std::setw(wId) << id
                    << "|" << std::left << std::setw(wName) << name
                    << "|" << std::left << std::fixed << std::setprecision(2)
                                        << std::setw(wPrice - 1) << price << " "
                    << "|" << std::left << std::setw(wStock - 1) << stock << " "
                    << "|" << std::left << std::setw(wCategory - 1) << category << " "
                    << "|" << std::endl;
        }
};

#endif