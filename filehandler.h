#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "menu.h"
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
        
};
#endif