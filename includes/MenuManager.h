#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <vector>
#include <map>

#include "menu.h"
#include "Order.h"

//none return function
void addMenuItems(std::vector<Menuitems>& menuItems);
void showMenuItems(std::vector<Menuitems>& menuItems);
void updateMenuItem(std::vector<Menuitems>& menuItems);
void deleteMenuItem(std::vector<Menuitems>& menuItems);
void placeOrder(std::vector<Menuitems>& items, std::vector<Order>& orders, int& nextOrderId);

//return function
std::string chooseCategory(const std::vector<std::string>& categories);
std::vector<Menuitems> loadMenuFromCategory(const std::string& category);

#endif