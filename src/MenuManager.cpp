#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <limits>

#include "../includes/MenuManager.h"
#include "../includes/MenuUI.h"
#include "../includes/Order.h"
#include "../includes/Filehandler.h"
#include "../includes/Filehandler.h"
// #include "main.cpp"

//Add items
void addMenuItems(std::vector<Menuitems>& menuItems){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    printSectionHeader("ADD NEW MENU ITEM");
    std::cout << std::endl;

    int id;
    while (true) {
        id = promptInt("Product ID");
        bool exists = false;
        for (const auto& item : menuItems) {
            if (item.getId() == id) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            break;
        }
        std::cout << "  Product ID " << id << " already exists. Please choose another." << std::endl;
    }
    std::string name = promptString("Product Name");
    double price = promptDouble("Price");
    int stock = promptInt("Stock");
    std::string category = chooseCategory(MEN_CATEGORY);

    menuItems.push_back(Menuitems(id, name, price, stock, category));

    std::cout << std::endl;
    printSectionHeader("ITEM ADDED SUCCESSFULLY");
}

//Show items
void showMenuItems(std::vector<Menuitems>& menuItems){

    std::sort(menuItems.begin(), menuItems.end(),[]
    (const Menuitems& a, const Menuitems b){
        return a.getCategory() < b.getCategory();
    });

    int wId = std::string("ID").length();
    int wName = std::string("Name").length();
    int wPrice = std::string("Price").length();
    int wStock = std::string("Stock").length();
    int wCategory = std::string("Category").length();

    for(const auto& item : menuItems){

        // wId = std::max(wId, (int)std::to_string(item.getId()).length());
        // wName = std::max(wName, (int)item.getName().length());
        // wPrice = std::max(wPrice, (int)std::to_string(item.getPrice()).length());
        // wStock = std::max(wStock, (int)std::to_string(item.getStock()).length());
        // wCategory = std::max(wCategory, (int)item.getCategory().length());

        getItemWidths(item, wId, wName, wPrice, wStock, wCategory);
    }
    wId += 2; wName += 2; wPrice += 2; wStock += 2; wCategory += 2;

    std::string lastCategory = "";
    for (const auto& item : menuItems) {
        if(item.getCategory() != lastCategory){

            std::cout << std::endl << "=== " << item.getCategory() << " ===" << std::endl;

            printSeparator(wId, wName, wPrice, wStock, wCategory);
                std::cout << "|" << std::left << std::setw(wId) << "ID"
                << "|" << std::left << std::setw(wName) << "Name"
                << "|" << std::left << std::setw(wPrice) << "Price"
                << "|" << std::left << std::setw(wStock) << "Stock"
                << "|" << std::left << std::setw(wCategory) << "Category"
                << "|" << std::endl;
            printSeparator(wId, wName, wPrice, wStock, wCategory);
            lastCategory = item.getCategory();
        }
        item.display(wId, wName, wPrice, wStock, wCategory);
    }
    // printSeparator(wId, wName, wPrice, wStock, wCategory);

}

//Update items
void updateMenuItem(std::vector<Menuitems>& menuItems){
    int id;
    std::cout << "Enter item ID to update: ";
    std::cin >> id;
    for (auto& item : menuItems) {
        if (id == item.getId()) {
            std::cout << "Current item details:\n";

            int wId, wName, wPrice, wStock, wCategory;
            //To get the length of the character
            getItemWidths(item, wId, wName, wPrice, wStock, wCategory);
            //display product
            item.display(wId, wName, wPrice, wStock, wCategory);

            int stock;
            double price;
            std::string name;

            std::cout << "Enter new name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter new price: ";
            std::cin >> price;
            std::cout << "Enter new stock: ";
            std::cin >> stock;

            item.setName(name);
            item.setPrice(price);
            item.setStock(stock);
            std::cout << "Item updated successfully!\n";
            return;
        }
    }
    std::cout << "Item not found.\n";  // moved outside the loop
}

//Delete items
void deleteMenuItem(std::vector<Menuitems>& menuItems){
    int id;
    std::cout << "Enter item ID to delete: ";
    std::cin >> id;
    for (auto i = menuItems.begin(); i != menuItems.end(); ++i) {
        if (i->getId() == id) {
            std::cout << "Deleting:\n";

            int wId, wName, wPrice, wStock, wCategory;
            
            //because i is a interator we use *i to get a acutuall Menuitems object it points to
            getItemWidths(*i, wId, wName, wPrice, wStock, wCategory);
            i->display(wId, wName, wPrice, wStock, wCategory);

            menuItems.erase(i);
            std::cout << "Item deleted." << std::endl;
            return;
        }
    }
    std::cout << "Item not found.\n";  // moved outside the loop
}

//Order items
void placeOrder(std::vector<Menuitems>& items, std::vector<Order>& orders, int& nextOrderId){
    int itemId, qty;
    std::cout << "Enter item Id to odrder : ";
    std::cin >> itemId;
    std::cout << "Enter quantity : ";
    std::cin >> qty;

    for(auto& item : items){
        if(itemId == item.getId()){
            if(qty > item.getStock()){
                std::cout << "Not enough stock! Only " << item.getStock() << "left" << std::endl; 
                return;
            }
            double total = item.getPrice() * qty;
            item.reduceStock(qty);

            Order newOrder(nextOrderId++, itemId, qty, total);
            orders.push_back(newOrder);
            FileHandler::apppendOrder(ORDER_FILE, newOrder);

            std::cout << "Order placed total $" << total << std::endl;
            
            return;
        }
        std::cout << "Id items not found" << std::endl;
    }
}
//get category
std::string chooseCategory(const std::vector<std::string>& categories){
    std::cout << std::endl;
    for(size_t i = 0; i < categories.size(); i++){
        std::cout << "   " << (i + 1) << ". " << categories[i] << std::endl;
    }
    int choice = promptInt("Category");
    if(choice >= 1 && choice <= static_cast<int>(categories.size())){
        return categories[choice - 1];
    }
    std::cout << "  Invalid choice. Defaulting to Uncategorized." << std::endl;
    return "Uncategorized";
}

std::vector<Menuitems> loadMenuFromCategory(const std::string& category){

    std::vector<Menuitems> items;
    std::ifstream file(category + "txt");
    std::string line;

    while(std::getline(file, line)){
        if(!line.empty()){
            items.push_back(Menuitems::fromfile(line));
        }
    }
    return items;
}