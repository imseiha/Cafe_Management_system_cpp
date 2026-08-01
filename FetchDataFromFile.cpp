#include<iostream>
#include<fstream>
using namespace std;
int main(){

    ifstream read("menu.txt");

    if(!read){
        cout << "Can not open file" << endl;
        return 0;
    }

    string readfile;

    while (getline(read, readfile))
    {
        cout << readfile << endl;
        
    }
    



    return 0;
}