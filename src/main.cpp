#include <iostream>

#include "../includes/menu.h"
#include "../includes/filehandler.h"
#include "../includes/MenuManager.h"
#include "../includes/MenuUI.h"
#include "../includes/TableFormat.h"
#include "../includes/Category.h"

int main(){
    std::vector<Menuitems> menuitems = FileHandler::loadMenuFromFile(MENU_FILE);
    std::vector<Order> orders = FileHandler::loadOrder(ORDER_FILE);

    int nextOrderId = 1;
    for(const auto& order : orders){
        if(order.getOrderId() >= nextOrderId){
            nextOrderId = order.getOrderId() + 1;
        }
    }

    //In one condition that manu has no item
    // if (menuitems.empty()) {
    //     menuitems.push_back(Menuitems(1, "Ice Coffee", 2.50, 10, "Drink"));
    //     menuitems.push_back(Menuitems(2, "Sting", 2.40, 9, "Drink"));
    //     menuitems.push_back(Menuitems(3, "Croissant", 3.75, 4, "Pastries"));
    //     menuitems.push_back(Menuitems(4, "Muffin", 2.25, 12, "Pastries"));
    //     menuitems.push_back(Menuitems(5, "Caca", 1.00, 10, "Drink"));
    // }

    int choice = 0;
    showWelcome();
    while (choice != 5) {
        showMenuFeature();
        std::cin >> choice;

        switch (choice) {
            case 1: addMenuItems(menuitems); break;
            case 2: showMenuItems(menuitems); break;
            // case 2: loadMenuFromCategory();
            case 3: updateMenuItem(menuitems); break;
            case 4: deleteMenuItem(menuitems); break;
            case 5:
                std::cout << "Exit Program! Gook luck" << std::endl;
                break;
            default:
                std::cout << "Invalid Option!!" << std::endl;
                break;
        }
    }

    return 0;
}