#include <iostream>
#include <sstream>
#include "MenuItem.h"

MenuItem::MenuItem() : id(0), name(""), category(""), price(0.0) {}

MenuItem::MenuItem(int id, const std::string& name, const std::string& category, double price)
    : id(id), name(name), category(category), price(price) {}

int MenuItem::getId() const {
    return id;
}

std::string MenuItem::getName() const {
    return name;
}

std::string MenuItem::getCategory() const {
    return category;
}

double MenuItem::getPrice() const {
    return price;
}

void MenuItem::setId(int id) {
    this->id = id;
}

void MenuItem::setName(const std::string& name) {
    this->name = name;
}

void MenuItem::setCategory(const std::string& category) {
    this->category = category;
}

void MenuItem::setPrice(double price) {
    this->price = price;
}

std::string MenuItem::toFileString() const {
    std::ostringstream oss;
    oss << id << "|" << name << "|" << category << "|" << price;
    return oss.str();
}

void MenuItem::display() const {
    std::cout << id << "\t" << name << "\t" << category << "\t" << price << std::endl;
}
