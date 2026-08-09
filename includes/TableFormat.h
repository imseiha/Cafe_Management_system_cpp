#pragma once

#include <string>

const int W_ID = 6, W_NAME = 16, W_PRICE = 12, W_STOCK = 9, W_CATEGORY = 17;

const std::string MENU_FILE = "data/menu.txt";
const std::string ORDER_FILE = "data/order.txt";

inline std::string centerText(const std::string& text, int width) {
    if ((int)text.length() >= width) {
        return text;
    }
    int leftPad = (width - (int)text.length()) / 2;
    int rightPad = width - (int)text.length() - leftPad;
    return std::string(leftPad, ' ') + text + std::string(rightPad, ' ');
}