#include <iostream>
#include <windows.h>
#include <limits>
#include <iomanip>

class Menu{
    private:
        int id;
        float price;
        std::string name;
    public:
        void setId(int id){
            this->id = id;
        }
        void setPrice(float price){
            this->price = price;
        }
        void setName(std::string name){
            this->name = name;
        }

        int getId(){return id;}
        float getPrice(){return price;}
        std::string getName(){return name;}
};

void createMenu(Menu m[], int size);
void showMenu(Menu m[], int size);
void updateMenu(Menu m[], int size);
void deleteMenu(Menu m[], int size);
void showGreeting();

int main(){
    int size;
    showGreeting();
    std::cout << "Enter the size of menu : ";
    std::cin >> size;
    Menu m[size];
    std::string name;
    int id, choice;
    float price;

    do{
        std::cout << std::endl;
        std::cout << "1.Create Menu" << std::endl;
        std::cout << "2.Show Menu" << std::endl;
        std::cout << "3.Update Menu" << std::endl;
        std::cout << "4.Delete Menu" << std::endl;
        std::cout << "Enter your choice : ";
        std::cin >> choice;
        std::cout << std::endl;
        // system("cls");
        switch (choice)
        {
        case 1:{
            std::cout << "Create Menu" << std::endl;
            createMenu(m, size);
            break;
        }
        case 2:{
            std::cout << "Show Menu" << std::endl;
            showMenu(m, size);
            break;
        }
        case 3:{
            int id;
            std::cout << "update Menu" << std::endl;
            updateMenu(m, size);
            break;
        }
        case 4:{
            std::cout << "Delete Menu" << std::endl;
            deleteMenu(m, size);
            break; 
        }
        case 5:{
            std::cout << "Exiting Program....!" << std::endl;
            break;
        }
        default:
            std::cout << "Invalid Option!!" << std::endl;
            break;
        }

    }while(choice != 5);

    return 0;
}
void createMenu(Menu m[], int size){
    std::string name;
    int id;
    float price;
    std::cout << std::endl;
    std::cout << "Enter Menu Details" << std::endl;
    for(int i = 0; i < size; i++){
        bool isDuplicate = false;
        std::cout << "Enter Product ID : ";
        std::cin >> id;
        for(int j = 0; j < i; j++){
            if(id == m[j].getId()){
                isDuplicate = true;
                break;
            }
            
        }
        if(isDuplicate){
            std::cout << "Product ID already exists. Please enter a unique Product ID." << std::endl;
            i--;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        m[i].setId(id);
        // std::cin.ignore();
        std::cout << "Enter Product Name : ";
        std::getline(std::cin, name);
        std::cout << "Enter Product Price : ";
        std::cin >> price;

        m[i].setPrice(price);
        m[i].setName(name);
        std::cout << std::endl;
    }
    std::cout << "Menu created successfully" << std::endl;
}
// void showMenu(Menu m[], int size){
//     std::cout << "ID\tName\tPrice" << std::endl;
//     for(int i = 0; i < size; i++){
//         std::cout << m[i].getId() << "\t" << m[i].getName() << "\t" << m[i].getPrice() << std::endl;
//         // std::cout << std::endl;
//     } 
// }

void showMenu(Menu m[], int size) {
    const int idW = 5;
    const int nameW = 20;
    const int priceW = 10;

    std::cout << std::left
               << std::setw(idW)    << "ID"
               << std::setw(nameW)  << "Name"
               << std::right << std::setw(priceW) << "Price"
               << std::endl;

    std::cout << std::string(idW + nameW + priceW, '-') << std::endl;

    for (int i = 0; i < size; i++) {
        std::cout << std::left
                   << std::setw(idW)   << m[i].getId()
                   << std::setw(nameW) << m[i].getName()
                   << std::right << std::setw(priceW)
                   << std::fixed << std::setprecision(2) << m[i].getPrice()
                   << std::endl;
    }
}

void updateMenu(Menu m[], int size){
    int id;
    std::string name;
    float price;
    std::cout << "Enter Product id to update : ";
            std::cin >> id;
            for(int i = 0; i < size; i++){
                if(id == m[i].getId()){
                    std::cout << "Enter Product ID : ";
                    std::cin >> id;
                    std::cin.ignore();
                    std::cout << "Enter Product Name : ";
                    std::getline(std::cin, name);
                    std::cout << "Enter Product Price : ";
                    std::cin >> price;

                    m[i].setId(id);
                    m[i].setPrice(price);
                    m[i].setName(name);
                }
            }
            std::cout << "Update successfully" << std::endl;
}
void deleteMenu(Menu m[], int size){
    int id;
    std::cout << "Enter id to delete product : ";
    std::cin >> id;
    for(int i = 0; i < size; i++){
        if(id == m[i].getId()){
            for(int j = 0; j < size -1; j++){
                m[j] = m[j + 1];
            }
            size--;
        }

    }
    std::cout << "Delete successfully" << std::endl;
}
void showGreeting() {
    std::cout << std::string(50, '=') << std::endl;
    std::cout << std::setw(38) << "CAFE MANAGEMENT SYSTEM" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << std::endl;
    std::cout << "  Welcome! This Menu System Helps You Manage:" << std::endl;
    std::cout << "    -1. Create Menu items" << std::endl;
    std::cout << "    -2. Show Menu items" << std::endl;
    std::cout << "    -3. Update Menu items" << std::endl;
    std::cout << "    -4. Delete Menu items" << std::endl;
    std::cout << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "  Loading system... please wait." << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << std::endl;
}