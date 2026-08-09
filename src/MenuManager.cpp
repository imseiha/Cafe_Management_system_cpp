#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <limits>

#include "../includes/MenuManager.h"
#include "../includes/MenuUI.h"
#include "../includes/Order.h"
#include "../includes/Filehandler.h"
// #include "main.cpp"

//Add items
void addMenuItems(std::vector<Menuitems>& menuItems){
    std::vector<Menuitems> menuitems = FileHandler::loadMenuFromFile(MENU_FILE);
    // std::vector<Order> orders = FileHandler::loadOrder(ORDER_FILE);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    printSectionHeader("ADD NEW MENU ITEM");
    // std::cout << std::endl;

    std::string category = chooseCategory(MEN_CATEGORY);

    int id = 1;
    for (const auto& item : menuitems) {
        if (item.getCategory() == category && item.getId() >= id) {
            id = item.getId() + 1;
        }
    }

    std::string name = promptString("Product Name");
    double price = promptDouble("Price");
    int stock = promptInt("Stock");

    Menuitems newItem(id, name, price, stock, category);
    menuItems.push_back(newItem);
    menuitems.push_back(newItem);

    std::cout << std::endl;
    FileHandler::saveMenuToFile(menuitems, MENU_FILE);
    std::cout << "  New item ID: " << newItem.formattedId() << std::endl;
    printSectionHeader("ITEM ADDED SUCCESSFULLY");
}

//Show items
void showMenuItems(std::vector<Menuitems>& menuItems){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (menuItems.empty()) {
        std::cout << "  No menu items available." << std::endl;
        return;
    }

    std::sort(menuItems.begin(), menuItems.end(),
    [](const Menuitems& a, const Menuitems& b){
        if (a.getCategory() != b.getCategory()) {
            return a.getCategory() < b.getCategory();
        }
        return a.getId() < b.getId();
    });

    std::string lastCategory = "";
    for (const auto& item : menuItems) {
        if (item.getCategory() != lastCategory) {
            if (!lastCategory.empty()) {
                printSeparator();  // close the PREVIOUS group's table
            }

            std::cout << std::endl << "=== " << item.getCategory() << " ===" << std::endl;

            printSeparator();
            std::cout << "|" << centerText("ID", W_ID)
                    << "|" << centerText("Name", W_NAME)
                    << "|" << centerText("Price", W_PRICE)
                    << "|" << centerText("Stock", W_STOCK)
                    << "|" << centerText("Category", W_CATEGORY)
                    << "|" << std::endl;
            printSeparator();

            lastCategory = item.getCategory();
        }
        item.display();
    }
    printSeparator();  // closes the LAST group's table
        std::cout << "<<< END OF TABLE >>>" << std::endl;
}

//Update items
void updateMenuItem(std::vector<Menuitems>& menuItems){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string category = chooseCategory(MEN_CATEGORY);

    int id;
    std::cout << "Enter item ID to update: ";
    std::cin >> id;
    for (auto& item : menuItems) {
        if (id == item.getId() && item.getCategory() == category) {
            std::cout << "Current item details:\n";

            printSeparator();
            std::cout << "|" << centerText("ID", W_ID)
                    << "|" << centerText("Name", W_NAME)
                    << "|" << centerText("Price", W_PRICE)
                    << "|" << centerText("Stock", W_STOCK)
                    << "|" << centerText("Category", W_CATEGORY)
                    << "|" << std::endl;
            printSeparator();
            item.display();
            printSeparator();

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

            FileHandler::saveMenuToFile(menuItems, MENU_FILE);
            std::cout << "Item updated successfully!" << std::endl;
            return;
        }
    }
    std::cout << "Item not found.\n";  // moved outside the loop
}

//Delete items
void deleteMenuItem(std::vector<Menuitems>& menuItems){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string category = chooseCategory(MEN_CATEGORY);

    int id;
    std::cout << "Enter item ID to delete: ";
    std::cin >> id;
    for (auto i = menuItems.begin(); i != menuItems.end(); ++i) {
        if (i->getId() == id && i->getCategory() == category) {
            std::cout << "Deleting:\n";

            printSeparator();
            std::cout << "|" << centerText("ID", W_ID)
                    << "|" << centerText("Name", W_NAME)
                    << "|" << centerText("Price", W_PRICE)
                    << "|" << centerText("Stock", W_STOCK)
                    << "|" << centerText("Category", W_CATEGORY)
                    << "|" << std::endl;
            printSeparator();
            i->display();
            printSeparator();

            std::string confirm;
            std::cout << "Are you sure you want to delete this item? (y/n): ";
            std::cin >> confirm;
            if (confirm != "y" && confirm != "Y") {
                std::cout << "De2letion cancelled." << std::endl;
                return;
            }

            menuItems.erase(i);
            FileHandler::saveMenuToFile(menuItems, MENU_FILE);
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
            FileHandler::saveMenuToFile(items, MENU_FILE);

            std::cout << "Order placed total $" << total << std::endl;
            
            return;
        }
        std::cout << "Id items not found" << std::endl;
    }
}
//get category
std::string chooseCategory(const std::vector<std::string>& categories){
    // std::cout << std::endl;
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