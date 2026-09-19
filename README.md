PLANNED FOLDER STRUCTURE

//To run my staff Management
 g++ -std=c++17 main.cpp staff_management/src/Auth.cpp staff_management/src/Staff.cpp staff_management/src/StaffManager.cpp -Istaff_management/include -o cafe_app.exe

 or you can
 
 You can shorten your compile command to g++ -std=c++17 main.cpp staff_management/src/*.cpp -Istaff_management/include -o cafe_app.exe

 ./cafe_app.exe


Cafe_Management_system_cpp/
    README.md                      this file
    Makefile                       build rules for mingw32 make
    .gitignore                     hides exe and build from git
    main.cpp                       program entry point stays here at root
    shared/                        code used by every module
        include/                   header h files
            Utils.h
            FileHandler.h
            Constants.h
        src/                       cpp implementation files
            Utils.cpp
            FileHandler.cpp
    menu_management/
        include/
        src/
    staff_management/
        include/
        src/
    sale_management/
        include/
        src/
    financial_management/
        include/
        src/
    data/                          only data files like menu.txt staff.txt sales.txt
    build/                         compiled exe output goes here


RULES WE AGREED ON

1  Every module folder has two subfolders. include for h files and src for cpp files
2  main.cpp always stays at the project root outside every module
3  The shared folder holds common code such as utils file handler and constants
4  The data folder holds only text data files. Never put code or exe there
5  All compiled exe files go into build so nothing pollutes the project root


HOW TO COMPILE AND RUN

You need g++ and mingw32 make installed. We use MSYS2 so both are already there

To compile run this command inside the project root folder

    -mingw32-make

The exe is created at build cafe_system.exe

To compile and then run the program use this command instead

    mingw32-make run

Extra command to delete the exe if you want a clean state

    -mingw32-make clean

Note. New cpp files added inside any module src folder are compiled
automatically because the Makefile uses wildcards



hii