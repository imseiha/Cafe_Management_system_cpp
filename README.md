PLANNED FOLDER STRUCTURE

Cafe_Management_system_cpp/
    README.md                      this file
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


SETUP STEPS TO DO LATER

1  Create include and src subfolders inside all five module folders
   shared menu_management staff_management sale_management financial_management

2  Add a .gitignore file containing exactly these two lines

*.exe
build/

3  Delete the stray exe files
   FetchDataFromFile.exe
   main.exe
   MenuManagement.exe inside the data folder

4  Do not rename anything and do not change any code on the other file (you can change it if nescessary)
