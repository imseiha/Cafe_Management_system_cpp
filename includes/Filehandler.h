#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <vector>

#include "Menu.h"
#include "Order.h"

class FileHandler {
    public:
        // Static method to save menu items to a file
        static void saveMenuToFile(const std::vector<Menuitems>& menuItems, const std::string& filename){
            std::ofstream outFile(filename);
            if(!outFile){
                std::cerr << "Error cannot open " << filename << std::endl;
                return;
            }
            for(const auto& items : menuItems){
                outFile << items.tofile() << std::endl;
            }
            outFile.close();
        }

        // load menu items from a file
        static std::vector<Menuitems> loadMenuFromFile(const std::string& filename){
           std::vector<Menuitems> items;
           std::ifstream inFile(filename);
           if(!inFile){
                std::cerr << "Error not found " << filename << std::endl;
                return items;
           }

           // Read each line from the file and create Menuitems objects
           std::string line;
           while(std::getline(inFile, line)){
                if(!line.empty()){
                    items.push_back(Menuitems::fromfile(line));
                }
            }
            inFile.close();
            return items;
        }
        
        static void saveOrder(const std::string& filename, const std::vector<Order>& orders){
            std::ofstream outFile(filename);
            if(!outFile){
                std::cerr << "Error can not open " << filename << std::endl;
                return;
            }
            for(const auto& order : orders){
                outFile << order.toFile() << std::endl;
            }
            outFile.close();
        }

        static std::vector<Order> loadOrder(const std::string& filename){
            std::vector<Order> orders;
            std::ifstream inFile(filename);
            if(!inFile){
                std::cerr << "Note : " << filename << "Not found!" << std::endl;
                return orders;
            }

            std::string line;
            while(std::getline(inFile, line)){
                if(!line.empty()){
                    orders.push_back(Order::fromFile(line));
                }
            }
            inFile.close();
            return orders;
        }

        static void apppendOrder(const std::string& filename, const Order& orders){
                std::ofstream outFile(filename, std::ios::app);
                if(!outFile){
                    std::cerr << "Erro can not open " << filename << std::endl;
                    return;
                }
                outFile << orders.toFile() << std::endl;
                outFile.close();
        }
};
#endif