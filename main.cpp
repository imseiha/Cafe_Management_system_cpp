#include <iostream>
#include <limits>

#include "staff_management/include/StaffManager.h"

using namespace std;


// ==========================================
// MAIN MENU
// ==========================================

void mainMenu()
{
    int choice;

    // Create Staff Manager
    StaffManager staffManager;

    do
    {
        cout << "\n\n";
        cout << "============================================\n";
        cout << "          CAFE MANAGEMENT SYSTEM\n";
        cout << "============================================\n";

        cout << "1. Sale Management\n";
        cout << "2. Staff Management\n";
        cout << "3. Menu Management\n";
        cout << "4. Financial Management\n";
        cout << "5. Exit\n";

        cout << "============================================\n";

        cout << "Choose option: ";
        cin >> choice;


        // =====================================
        // CHECK INVALID INPUT
        // =====================================

        if (cin.fail())
        {
            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            cout << "\nInvalid input!";
            cout << "\nPlease enter a number from 1 to 5.\n";

            continue;
        }


        // =====================================
        // MAIN MENU OPTIONS
        // =====================================

        switch (choice)
        {

            // =================================
            // 1. SALE MANAGEMENT
            // =================================

            case 1:

                cout << "\n============================================\n";
                cout << "            SALE MANAGEMENT\n";
                cout << "============================================\n";

                cout << "\nThis module is under development.";
                cout << "\nIt will be implemented by the Sale Management team.\n";

                break;


            // =================================
            // 2. STAFF MANAGEMENT
            // =================================

            case 2:

                cout << "\n============================================\n";
                cout << "            STAFF MANAGEMENT\n";
                cout << "============================================\n";

                // Call YOUR Staff Management
                staffManager.staffMenu();

                break;


            // =================================
            // 3. MENU MANAGEMENT
            // =================================

            case 3:

                cout << "\n============================================\n";
                cout << "             MENU MANAGEMENT\n";
                cout << "============================================\n";

                cout << "\nThis module is under development.";
                cout << "\nIt will be implemented by the Menu Management team.\n";

                break;


            // =================================
            // 4. FINANCIAL MANAGEMENT
            // =================================

            case 4:

                cout << "\n============================================\n";
                cout << "          FINANCIAL MANAGEMENT\n";
                cout << "============================================\n";

                cout << "\nThis module is under development.";
                cout << "\nIt will be implemented by the Financial Management team.\n";

                break;


            // =================================
            // 5. EXIT
            // =================================

            case 5:

                cout << "\n============================================\n";
                cout << "       EXIT CAFE MANAGEMENT SYSTEM\n";
                cout << "============================================\n";

                cout << "Thank you for using the system!\n";

                break;


            // =================================
            // INVALID OPTION
            // =================================

            default:

                cout << "\nInvalid option!";
                cout << "\nPlease choose between 1 and 5.\n";

                break;
        }

    } while (choice != 5);
}


// ==========================================
// MAIN FUNCTION
// ==========================================

int main()
{
    cout << "\n";
    cout << "\033[34m================================================="<<endl;
    cout << "|       WELCOME TO CAFE MANAGEMENT SYSTEM       |"<<endl;;
    cout << "=================================================\033[0m"<<endl;;


    // ======================================
    // OPEN MAIN MENU
    // ======================================

    mainMenu();


    return 0;
}