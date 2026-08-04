#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "menu.h"
#include "filehandler.h"

const std::string MENU_FILE = "menu.txt";

//Menu System feature
void addMenuItems(std::vector<Menuitems>& menuItems);
void showMenuItems(const std::vector<Menuitems>& menuItems);
void updateMenuItem(std::vector<Menuitems>& menuItems);
void deleteMenuItem(std::vector<Menuitems>& menuItems);
// void showMenuItems(const std::vector<Menuitems>& menuItems);
void printSeparator(char left, char mid, char right);

//Decoration
void showMenuFeature();


int main(){

    std::vector<Menuitems> menuitems = FileHandler::loadMenuFromFile(MENU_FILE);

    if(menuitems.empty()){
        menuitems.push_back(Menuitems(1, "Ice Coffe", 2.50, 10));
        menuitems.push_back(Menuitems(2, "Sting", 2.4, 9));
        menuitems.push_back(Menuitems(3, "Ice Coffe", 2.0, 6));
    }
    
    int choice = 0;
    while(choice != 6){
        // std::cout << std::endl;
        // std::cout << "1. Add Menu" << std::endl;
        // std::cout << "2. Show Menu" << std::endl;
        // std::cout << "3. Update Menu" << std::endl;
        // std::cout << "4. Delete Menu" << std::endl;
        // std::cout << "5. Save Data" << std::endl;
        // std::cout << "6. Exit" << std::endl;
        // std::cout << "Enter your choice : ";
        showMenuFeature();
        std::cin >> choice;
        switch(choice){
            case 1:{
                std::cout << "Add Menu" << std::endl;
                addMenuItems(menuitems);
                break;
            }
            case 2:{
                std::cout << "Show Menu" << std::endl;
                showMenuItems(menuitems);
                break;
            }
            case 3:{
                std::cout << "Update Menu" << std::endl;
                updateMenuItem(menuitems);
                break;
            }
            case 4:{
                std::cout << "Delete Menu" << std::endl;
                deleteMenuItem(menuitems);
                break; 
            }
            case 5:{
                FileHandler::saveMenuToFile(menuitems, MENU_FILE);  
                break;
            }
            case 6:{
                std::cout << "Exiting Program...!" << std::endl;
                break;
            }
            default:
                std::cout << "Invalid Option!!" << std::endl;
                break;
        }
    }

    return 0;
}

void addMenuItems(std::vector<Menuitems>& menuItems){
    int id, stock;
    double price;
    std::string name;

    std::cout << "Enter Product ID: ";
    std::cin >> id;
    std::cin.ignore(); // Ignore the newline character left in the input buffer
    std::cout << "Enter Product Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Product Price: ";   
    std::cin >> price;
    std::cout << "Enter Product Stock: ";
    std::cin >> stock;

    menuItems.push_back(Menuitems(id, name, price, stock));
}

// void showMenuItems(const std::vector<Menuitems>& menuItems){
//     std::cout << "ID\tName\tPrice\tStock" << std::endl;
//     for(const auto& item : menuItems){
//         item.display();
//     }
// }

void showMenuItems(const std::vector<Menuitems>& menuItems) {
    printSeparator('+', '+', '+');
    std::cout << "|" << std::left << std::setw(W_ID) << "ID"
               << "|" << std::left << std::setw(W_NAME) << "Name"
               << "|" << std::left << std::setw(W_PRICE) << "Price"
               << "|" << std::left << std::setw(W_STOCK) << "Stock"
               << "|" << std::endl;
    printSeparator('+', '+', '+');

    for (const auto& item : menuItems) {
        item.display();
    }

    printSeparator('+', '+', '+');
}

void updateMenuItem(std::vector<Menuitems>& menuItems){
    int id;
    std::cout << "Enter items ID to update : ";
    std::cin >> id;
    for(auto& item : menuItems){
        if(id == item.getId()){
            std::cout << "Current items detals" << std::endl;
            item.display();

            int stock;
            double price;
            std::string name;
            
            std::cout << "Enter new name : ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter new price : ";
            std::cin >> price;
            std::cout << "Enter new Stock : ";
            std::cin >> stock;

            item.setName(name);
            item.setPrice(price);
            item.setStock(stock);
            std::cout << "Item update successfully" << std::endl;
            return;
        }
    }
}
void deleteMenuItem(std::vector<Menuitems>& menuItems){
    int id;
    std::cout << "Enter items Id to delete : ";
    std::cin >> id;
    for(auto i = menuItems.begin(); i != menuItems.end(); ++i){
        if(i->getId() == id){
            std::cout << "Deleting" << std::endl;
            i->display();
            menuItems.erase(i);
            std::cout << "Item deleted" << std::endl;
            return;
        }
        std::cout << "Item not found" << std::endl;
    }
}
//design
// const int W_ID = 6, W_NAME = 20, W_PRICE = 10, W_STOCK = 8;

void printSeparator(char left, char mid, char right) {
    std::cout << left
               << std::string(W_ID, '-') << mid
               << std::string(W_NAME, '-') << mid
               << std::string(W_PRICE, '-') << mid
               << std::string(W_STOCK, '-') << right
               << std::endl;
}

void typeEffect(const std::string& text, int delayMs = 15) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
    std::cout << std::endl;
}

void loadingBar() {
    std::cout << "Loading";
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "." << std::flush;
    }
    std::cout << std::endl;
}

void showMenuFeature() {
    const int width = 30;

    loadingBar();
    std::cout << std::endl;

    std::cout << "+" << std::string(width, '-') << "+" << std::endl;
    typeEffect("|         MENU SYSTEM          |");
    std::cout << "+" << std::string(width, '-') << "+" << std::endl;

    typeEffect("| 1. Add Menu                  |");
    typeEffect("| 2. Show Menu                 |");
    typeEffect("| 3. Update Menu               |");
    typeEffect("| 4. Delete Menu               |");
    typeEffect("| 5. Save Data                 |");
    typeEffect("| 6. Exit                      |");

    std::cout << "+" << std::string(width, '-') << "+" << std::endl;
    std::cout << "Enter your choice : ";
}