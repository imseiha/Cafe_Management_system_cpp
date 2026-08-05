#include <iostream>

#include "../includes/menu.h"
#include "../includes/filehandler.h"
#include "../includes/MenuManager.h"
#include "../includes/MenuUI.h"
#include "../includes/TableFormat.h"


int main(){
    std::vector<Menuitems> menuitems = FileHandler::loadMenuFromFile(MENU_FILE);
    std::vector<Order> orders = FileHandler::loadOrder(ORDER_FILE);

    int nextOrderId = 1;
    for(const auto& order : orders){
        if(order.getOrderId() >= nextOrderId){
            nextOrderId = order.getOrderId() + 1;
        }
    }

    if (menuitems.empty()) {
        menuitems.push_back(Menuitems(1, "Ice Coffee", 2.50, 10));
        menuitems.push_back(Menuitems(2, "Sting", 2.4, 9));
        menuitems.push_back(Menuitems(3, "Ice Coffee", 2.0, 6));
    }

    int choice = 0;
    while (choice != 8) {
        showMenuFeature();
        std::cin >> choice;

        switch (choice) {
            case 1: addMenuItems(menuitems); break;
            case 2: showMenuItems(menuitems); break;
            case 3: updateMenuItem(menuitems); break;
            case 4: deleteMenuItem(menuitems); break;
            case 5:
                placeOrder(menuitems, orders, nextOrderId); break;
            case 6:
                FileHandler::saveMenuToFile(menuitems, MENU_FILE);
                FileHandler::saveOrder(ORDER_FILE, orders);
                std::cout << "Data Saved!!" << std::endl;
                break;
            case 7:
                for(const auto& displayOrder : orders){
                    displayOrder.display();
                }
                break;
            case 8:
                std::cout << "Exit Program! Gook luck" << std::endl;
                break;
            default:
                std::cout << "Invalid Option!!" << std::endl;
                break;
        }
    }

    return 0;
}