#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <vector>
#include "menu.h"
#include "Order.h"

void addMenuItems(std::vector<Menuitems>& menuItems);
void showMenuItems(const std::vector<Menuitems>& menuItems);
void updateMenuItem(std::vector<Menuitems>& menuItems);
void deleteMenuItem(std::vector<Menuitems>& menuItems);
void placeOrder(std::vector<Menuitems>& items, std::vector<Order>& orders, int& nextOrderId);

#endif