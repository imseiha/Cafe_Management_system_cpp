#ifndef ORDER_H
#define ORDER_H

#include <string>

class Order {
private:
    int id;
    int itemId;
    std::string itemName;
    int quantity;
    double unitPrice;
    double total;
    std::string createdAt;

public:
    Order();
    Order(int id, int itemId, const std::string& itemName, int quantity, double unitPrice, double total, const std::string& createdAt);

    int getId() const;
    int getItemId() const;
    std::string getItemName() const;
    int getQuantity() const;
    double getUnitPrice() const;
    double getTotal() const;
    std::string getCreatedAt() const;

    void setId(int id);
    void setItemId(int itemId);
    void setItemName(const std::string& itemName);
    void setQuantity(int quantity);
    void setUnitPrice(double unitPrice);
    void setTotal(double total);
    void setCreatedAt(const std::string& createdAt);

    std::string toFileString() const;
    void display() const;
};

#endif