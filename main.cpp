#include <iostream>
#include <limits>
#include "SaleManager.h"
#include "StaffManager.h"
#include "MenuManager.h"
#include "FinanceManager.h"

int main(){
    int option = 0;
    do{
        std::cout << std::endl;
        std::cout << "=======================" << std::endl;
        std::cout << "1.Sale Management" << std::endl;
        std::cout << "2.Staff Manjagement" << std::endl;
        std::cout << "3.Menu Management" << std::endl;
        std::cout << "4.Financial Management" << std::endl;
        std::cout << "5.Exit" << std::endl;
        std::cout << "=======================" << std::endl;
        std::cout << "Enter your option : ";
        if (!(std::cin >> option)) {
            if (std::cin.eof()) {
                break;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid option. Please try again." << std::endl;
            continue;
        }

        // system("cls");
        switch(option){
            case 1:{
                SaleManager saleManager;
                saleManager.run();
                break;
            }
            case 2:{
                StaffManager staffManager;
                staffManager.run();
                break;
            }
            case 3:{
                MenuManager menuManager;
                menuManager.run();
                break;
            }
            case 4:{
                FinanceManager financeManager;
                financeManager.run();
                break;
            }
            case 5:{
                break;
            }
            default:{
                std::cout << "Invalid option. Please try again." << std::endl;
                break;
            }
        }
    }while(option != 5);
    return 0;
}
