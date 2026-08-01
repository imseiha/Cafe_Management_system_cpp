#include <iostream>

class Menu{
    private:
        int id;
        float price;
        std::string name;
    public: 
        Menu(int id, float price, std::string name) : id(id), price(price), name(name) {}
        Menu(){
            id = 0;
            price = 0;
            name = "unkown";
        }

        void showMenu(){
            std::cout << "Hi from menu" << std::endl;
        }

        //getdata
        int getId(){
            return id;
        }
        float getPrice(){
            return price;
        }
        std::string getName(){
            return name;
        }

};

int main(){
    
    int choice;


    Menu data;

    do{
        std::cout << std::endl;
        std::cout << "1.Create Menu" << std::endl;
        std::cout << "2.Show Menu" << std::endl;
        std::cout << "3.Update Menu" << std::endl;
        std::cout << "4.Delete Menu" << std::endl;
        std::cout << "5.Exit Program" << std::endl;
        std::cout << "Enter your choice : ";
        std::cin >> choice;

        switch(choice){
            case 1:{
                data.showMenu();
            }
        }

    }while(choice);


    return 0;
}