#include <iostream>
#include <windows.h>
int main(){
    int option;
    do{
        std::cout << std::endl;
        std::cout << "=======================" << std::endl;
        std::cout << "1.Sale Management" << std::endl;
        std::cout << "2.Staff Management" << std::endl;
        std::cout << "3.Menu Management" << std::endl;
        std::cout << "4.Financial Management" << std::endl;
        std::cout << "5.Exit" << std::endl;
        std::cout << "=======================" << std::endl;
        std::cout << "Enter your option : ";
        std::cin >> option;
        system("cls");
        switch(option){
            case 1:{

            }
        }

    }while(option != 5);
}