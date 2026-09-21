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
    int staffId;

public:
    Order();
    Order(int id, int itemId, const std::string& itemName, int quantity, double unitPrice, double total, const std::string& createdAt, int staffId = 0);

    int getId() const;
    int getItemId() const;
    std::string getItemName() const;
    int getQuantity() const;
    double getUnitPrice() const;
    double getTotal() const;
    std::string getCreatedAt() const;
    int getStaffId() const;

    void setId(int id);
    void setItemId(int itemId);
    void setItemName(const std::string& itemName);
    void setQuantity(int quantity);
    void setUnitPrice(double unitPrice);
    void setTotal(double total);
    void setCreatedAt(const std::string& createdAt);
    void setStaffId(int staffId);

    std::string toFileString() const;
    void display() const;
};

#endif
