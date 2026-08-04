#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <vector>
#include "menu.h"

void addMenuItems(std::vector<Menuitems>& menuItems);
void showMenuItems(const std::vector<Menuitems>& menuItems);
void updateMenuItem(std::vector<Menuitems>& menuItems);
void deleteMenuItem(std::vector<Menuitems>& menuItems);

#endif