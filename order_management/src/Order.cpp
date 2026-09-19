#include <iostream>
#include <sstream>
#include <iomanip>
#include "Order.h"

Order::Order() : id(0), itemId(0), itemName(""), quantity(0), unitPrice(0.0), total(0.0), createdAt("") {}

Order::Order(int id, int itemId, const std::string& itemName, int quantity, double unitPrice, double total, const std::string& createdAt)
    : id(id), itemId(itemId), itemName(itemName), quantity(quantity), unitPrice(unitPrice), total(total), createdAt(createdAt) {}

int Order::getId() const {
    return id;
}

int Order::getItemId() const {
    return itemId;
}

std::string Order::getItemName() const {
    return itemName;
}

int Order::getQuantity() const {
    return quantity;
}

double Order::getUnitPrice() const {
    return unitPrice;
}

double Order::getTotal() const {
    return total;
}

std::string Order::getCreatedAt() const {
    return createdAt;
}

void Order::setId(int id) {
    this->id = id;
}

void Order::setItemId(int itemId) {
    this->itemId = itemId;
}

void Order::setItemName(const std::string& itemName) {
    this->itemName = itemName;
}

void Order::setQuantity(int quantity) {
    this->quantity = quantity;
}

void Order::setUnitPrice(double unitPrice) {
    this->unitPrice = unitPrice;
}

void Order::setTotal(double total) {
    this->total = total;
}

void Order::setCreatedAt(const std::string& createdAt) {
    this->createdAt = createdAt;
}

std::string Order::toFileString() const {
    std::ostringstream oss;
    oss << id << "|" << itemId << "|" << itemName << "|" << quantity << "|" << unitPrice << "|" << total << "|" << createdAt;
    return oss.str();
}

void Order::display() const {
    std::cout << std::setfill('0') << std::setw(4) << id << std::setfill(' ')
              << "\t" << itemName << "\t" << quantity << "\t"
              << std::fixed << std::setprecision(2) << unitPrice << "\t" << total << "\t" << createdAt << std::endl;
}