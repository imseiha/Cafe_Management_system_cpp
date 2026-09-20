#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cstdio>
#include "Receipt.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace {

const int INNER_WIDTH = 48;

const std::string BOX_TL = "\xE2\x94\x8C";
const std::string BOX_TR = "\xE2\x94\x90";
const std::string BOX_BL = "\xE2\x94\x94";
const std::string BOX_BR = "\xE2\x94\x98";
const std::string BOX_HZ = "\xE2\x94\x80";
const std::string BOX_VT = "\xE2\x94\x82";
const std::string BOX_ML = "\xE2\x94\x9C";
const std::string BOX_MR = "\xE2\x94\xA4";

const std::string SHOP_NAME = "CAFE AURORA";
const std::string SHOP_TAGLINE = "Taste The Difference";

std::string repeatString(const std::string& text, int count) {
    std::string out;
    for (int i = 0; i < count; ++i) {
        out += text;
    }
    return out;
}

std::string centered(const std::string& text, int width) {
    int pad = (width - static_cast<int>(text.size())) / 2;
    if (pad < 0) {
        pad = 0;
    }
    return std::string(pad, ' ') + text + std::string(width - static_cast<int>(text.size()) - pad, ' ');
}

std::string padRight(const std::string& text, int width) {
    if (static_cast<int>(text.size()) >= width) {
        return text;
    }
    return text + std::string(width - static_cast<int>(text.size()), ' ');
}

std::string padLeft(const std::string& text, int width) {
    if (static_cast<int>(text.size()) >= width) {
        return text;
    }
    return std::string(width - static_cast<int>(text.size()), ' ') + text;
}

std::string money(double amount) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << amount;
    return "$" + oss.str();
}

std::string currentDateTime() {
    std::time_t now = std::time(nullptr);
    std::tm localTime = {};
#ifdef _WIN32
    localtime_s(&localTime, &now);
#else
    localTime = *std::localtime(&now);
#endif
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
                  localTime.tm_year + 1900, localTime.tm_mon + 1, localTime.tm_mday,
                  localTime.tm_hour, localTime.tm_min, localTime.tm_sec);
    return buf;
}

std::string compactDateTime() {
    std::time_t now = std::time(nullptr);
    std::tm localTime = {};
#ifdef _WIN32
    localtime_s(&localTime, &now);
#else
    localTime = *std::localtime(&now);
#endif
    char buf[16];
    std::snprintf(buf, sizeof(buf), "%02d%02d%02d%02d%02d%02d",
                  localTime.tm_mday, localTime.tm_mon + 1, (localTime.tm_year + 1900) % 100,
                  localTime.tm_hour, localTime.tm_min, localTime.tm_sec);
    return buf;
}

std::string topBorder() {
    return BOX_TL + repeatString(BOX_HZ, INNER_WIDTH) + BOX_TR;
}

std::string midBorder() {
    return BOX_ML + repeatString(BOX_HZ, INNER_WIDTH) + BOX_MR;
}

std::string bottomBorder() {
    return BOX_BL + repeatString(BOX_HZ, INNER_WIDTH) + BOX_BR;
}

std::string boxLine(const std::string& content) {
    return BOX_VT + content + BOX_VT;
}

std::string boxCentered(const std::string& text) {
    return boxLine(centered(text, INNER_WIDTH));
}

std::string labelValueLine(const std::string& label, const std::string& value) {
    int padding = INNER_WIDTH - static_cast<int>(label.size()) - static_cast<int>(value.size());
    if (padding < 0) {
        padding = 0;
    }
    return boxLine(label + std::string(padding, ' ') + value);
}

std::string itemRowLine(const std::string& name, int quantity, double amount) {
    std::string item = name;
    if (item.size() > 27) {
        item = item.substr(0, 24) + "...";
    }
    return boxLine(padRight(item, 27)
                   + " " + padLeft(std::to_string(quantity), 6)
                   + "  " + padLeft(money(amount), 12));
}

std::string amountLine(const std::string& label, double amount) {
    return labelValueLine(label, money(amount));
}

std::string buildReceipt(const std::vector<Order>& orders) {
    std::ostringstream out;

    int receiptNo = 0;
    for (const Order& order : orders) {
        if (order.getId() > receiptNo) {
            receiptNo = order.getId();
        }
    }

    double subtotal = Receipt::billTotal(orders);
    double total = subtotal;

    out << topBorder() << "\n";
    out << boxCentered(SHOP_NAME) << "\n";
    out << boxCentered(SHOP_TAGLINE) << "\n";
    out << midBorder() << "\n";

    out << boxCentered("ORDER RECEIPT") << "\n";

    std::ostringstream recNum;
    recNum << "#" << std::setfill('0') << std::setw(5) << receiptNo;
    out << boxCentered(recNum.str()) << "\n";

    std::ostringstream orderId;
    orderId << compactDateTime() << std::setfill('0') << std::setw(3) << (receiptNo % 1000);
    out << labelValueLine("Order ID:", orderId.str()) << "\n";
    out << labelValueLine("Date:", currentDateTime()) << "\n";

    out << midBorder() << "\n";
    out << boxLine(padRight("Item", 27)
                   + " " + padLeft("Qty", 6)
                   + "  " + padLeft("Amount", 12)) << "\n";
    out << midBorder() << "\n";

    for (const Order& order : orders) {
        out << itemRowLine(order.getItemName(), order.getQuantity(), order.getTotal()) << "\n";
        out << midBorder() << "\n";
    }

    out << amountLine("Subtotal:", subtotal) << "\n";
    out << midBorder() << "\n";
    out << amountLine("TOTAL:", total) << "\n";
    out << midBorder() << "\n";

    out << boxCentered("Thank you for visiting!") << "\n";
    out << boxCentered("Please come again.") << "\n";
    out << bottomBorder() << "\n\n";

    return out.str();
}

}

double Receipt::billTotal(const std::vector<Order>& orders) {
    double total = 0.0;
    for (const Order& order : orders) {
        total += order.getTotal();
    }
    return total;
}

void Receipt::print(const std::vector<Order>& orders) {
    if (orders.empty()) {
        std::cout << "No orders to print." << std::endl;
        return;
    }
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    std::cout << buildReceipt(orders);
}

void Receipt::saveToFile(const std::vector<Order>& orders, const std::string& filepath) {
    if (orders.empty()) {
        return;
    }
    std::ofstream file(filepath, std::ios::app);
    if (!file.is_open()) {
        std::cout << "Error: could not open " << filepath << " for saving receipt." << std::endl;
        return;
    }
    file << buildReceipt(orders);
    file.close();
}

void Receipt::viewFromFile(const std::string& filepath) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cout << "No receipts found in " << filepath << "." << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}