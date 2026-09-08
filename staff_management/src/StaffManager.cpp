#include "../include/StaffManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;


// ==========================================
// Constructor
// ==========================================

StaffManager::StaffManager()
{
    nextId = 1;

    // Load existing staff from file
    loadFromFile();
}


// ==========================================
// LOAD STAFF FROM FILE
// ==========================================

void StaffManager::loadFromFile()
{
    ifstream file(fileName);

    // If file does not exist,
    // simply start with empty staff data.
    if (!file.is_open())
    {
        return;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);

        string id;
        string name;
        string gender;
        string date_of_birth;
        string place_of_birth;
        string current_address;
        string phone_number;
        string email;
        string position;
        string username;
        string password;
        string salary;
        string status;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, gender, '|');
        getline(ss, date_of_birth, '|');
        getline(ss, place_of_birth, '|');
        getline(ss, current_address, '|');
        getline(ss, phone_number, '|');
        getline(ss, email, '|');
        getline(ss, position, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, salary, '|');
        getline(ss, status, '|');

        try
        {
            int staffId = stoi(id);

            Staff staff(
                staffId,
                name,
                gender,
                date_of_birth,
                place_of_birth,
                current_address,
                phone_number,
                email,
                position,
                username,
                password,
                salary,
                status
            );

            staffData.push_back(staff);

            if (staffId >= nextId)
            {
                nextId = staffId + 1;
            }
        }
        catch (...)
        {
            cout << "Error reading staff data.\n";
        }
    }

    file.close();
}


// ==========================================
// SAVE STAFF TO FILE
// ==========================================

void StaffManager::saveToFile()
{
    ofstream file(fileName);

    if (!file.is_open())
    {
        cout << "Error: Cannot open staff file!\n";
        return;
    }

    for (const auto& staff : staffData)
    {
        file << staff.getId() << "|"
             << staff.getName() << "|"
             << staff.getGender() << "|"
             << staff.getDateOfBirth() << "|"
             << staff.getPlaceOfBirth() << "|"
             << staff.getCurrentAddress() << "|"
             << staff.getPhoneNumber() << "|"
             << staff.getEmail() << "|"
             << staff.getPosition() << "|"
             << staff.getUsername() << "|"
             << staff.getPassword() << "|"
             << staff.getSalary() << "|"
             << staff.getStatus()
             << "\n";
    }

    file.close();
}


// ==========================================
// FIND STAFF BY ID
// ==========================================

Staff* StaffManager::findStaffById(int id)
{
    for (auto& staff : staffData)
    {
        if (staff.getId() == id)
        {
            return &staff;
        }
    }

    return nullptr;
}


// ==========================================
// 1. VIEW STAFF
// ==========================================

void StaffManager::viewStaff()
{
    cout << "\n==========================================\n";
    cout << "               STAFF LIST\n";
    cout << "==========================================\n";

    if (staffData.empty())
    {
        cout << "\nNo staff data found.\n";
        cout << "Please create a staff first.\n";
        return;
    }

    for (const auto& staff : staffData)
    {
        staff.display();
    }
}


// ==========================================
// 2. CREATE STAFF
// ==========================================

void StaffManager::createStaff()
{
    cout << "\n==========================================\n";
    cout << "              CREATE STAFF\n";
    cout << "==========================================\n";

    string name;
    string gender;
    string date_of_birth;
    string place_of_birth;
    string current_address;
    string phone_number;
    string email;
    string position;
    string username;
    string password;
    string salary;
    string status;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Full Name: ";
    getline(cin, name);

    cout << "Enter Gender (Male/Female): ";
    getline(cin, gender);

    cout << "Enter Date of Birth (DD/MM/YYYY): ";
    getline(cin, date_of_birth);

    cout << "Enter Place of Birth: ";
    getline(cin, place_of_birth);

    cout << "Enter Current Address: ";
    getline(cin, current_address);

    cout << "Enter Phone Number: ";
    getline(cin, phone_number);

    cout << "Enter Email: ";
    getline(cin, email);

    cout << "Enter Position: ";
    getline(cin, position);

    cout << "Enter Username: ";
    getline(cin, username);

    cout << "Enter Password: ";
    getline(cin, password);

    cout << "Enter Salary: ";
    getline(cin, salary);

    cout << "Enter Status (Active/Inactive): ";
    getline(cin, status);


    // ======================================
    // VALIDATION
    // ======================================

    if (
        name.empty() ||
        gender.empty() ||
        date_of_birth.empty() ||
        place_of_birth.empty() ||
        current_address.empty() ||
        phone_number.empty() ||
        email.empty() ||
        position.empty() ||
        username.empty() ||
        password.empty() ||
        salary.empty() ||
        status.empty()
    )
    {
        cout << "\nInvalid input!\n";
        cout << "All fields are required.\n";
        return;
    }


    // ======================================
    // CHECK DUPLICATE USERNAME
    // ======================================

    for (const auto& staff : staffData)
    {
        if (staff.getUsername() == username)
        {
            cout << "\nUsername already exists!\n";
            cout << "Please use another username.\n";
            return;
        }
    }


    // ======================================
    // CREATE STAFF OBJECT
    // ======================================

    Staff newStaff(
        nextId,
        name,
        gender,
        date_of_birth,
        place_of_birth,
        current_address,
        phone_number,
        email,
        position,
        username,
        password,
        salary,
        status
    );

    staffData.push_back(newStaff);

    nextId++;


    // ======================================
    // SAVE TO FILE
    // ======================================

    saveToFile();


    cout << "\nStaff created successfully!\n";
    cout << "Staff ID: " << newStaff.getId() << endl;
    cout << "Data saved to staff.txt\n";
}


// ==========================================
// 3. UPDATE STAFF
// ==========================================

void StaffManager::updateStaff()
{
    cout << "\n==========================================\n";
    cout << "              UPDATE STAFF\n";
    cout << "==========================================\n";

    int id;

    cout << "Enter Staff ID: ";
    cin >> id;

    Staff* staff = findStaffById(id);

    if (staff == nullptr)
    {
        cout << "\nStaff not found!\n";
        return;
    }


    cout << "\nCurrent Staff Information:";
    staff->display();


    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string input;


    cout << "\nEnter new Name";
    cout << " (Press Enter to keep current): ";
    getline(cin, input);

    if (!input.empty())
    {
        staff->setName(input);
    }


    cout << "Enter new Gender";
    cout << " (Press Enter to keep current): ";
    getline(cin, input);

    if (!input.empty())
    {
        staff->setGender(input);
    }


    cout << "Enter new Date of Birth";
    cout << " (Press Enter to keep current): ";
    getline(cin, input);

    if (!input.empty())
    {
        staff->setDateOfBirth(input);
    }


    cout << "Enter new Place of Birth";
    cout << " (Press Enter to keep current): ";
    getline(cin, input);

    if (!input.empty())
    {
        staff->setPlaceOfBirth(input);
    }


    cout << "Enter new Current Address";
    cout << " (Press Enter to keep current): ";
    getline(cin, input);

    if (!input.empty())
    {
        staff->setCurrentAddress(input);
    }


    cout << "Enter new Phone Number";
    cout << " (Press Enter to keep current): ";
    getline(cin, input);

    if (!input.empty())
    {
        staff->setPhoneNumber(input);
    }


    cout << "Enter new Email";
    cout << " (Press Enter to keep current): ";
    getline(cin, input);

    if (!input.empty())
    {
        staff->setEmail(input);
    }


    cout << "Enter new Position";
    cout << " (Press Enter to keep current): ";
    getline(cin, input);

    if (!input.empty())
    {
        staff->setPosition(input);
    }


    cout << "Enter new Username";
    cout << " (Press Enter to keep current): ";
    getline(cin, input);

    if (!input.empty())
    {
        staff->setUsername(input);
    }


    cout << "Enter new Password";
    cout << " (Press Enter to keep current): ";
    getline(cin, input);

    if (!input.empty())
    {
        staff->setPassword(input);
    }


    cout << "Enter new Salary";
    cout << " (Press Enter to keep current): ";
    getline(cin, input);

    if (!input.empty())
    {
        staff->setSalary(input);
    }


    cout << "Enter new Status";
    cout << " (Press Enter to keep current): ";
    getline(cin, input);

    if (!input.empty())
    {
        staff->setStatus(input);
    }


    // Save updated data
    saveToFile();

    cout << "\nStaff updated successfully!\n";
    cout << "Data updated in staff.txt\n";
}


// ==========================================
// 4. DELETE STAFF
// ==========================================

void StaffManager::deleteStaff()
{
    cout << "\n==========================================\n";
    cout << "              DELETE STAFF\n";
    cout << "==========================================\n";

    int id;

    cout << "Enter Staff ID: ";
    cin >> id;


    auto it = find_if(
        staffData.begin(),
        staffData.end(),
        [id](const Staff& staff)
        {
            return staff.getId() == id;
        }
    );


    if (it == staffData.end())
    {
        cout << "\nStaff not found!\n";
        return;
    }


    cout << "\nStaff found:";
    it->display();


    char confirm;

    cout << "\nAre you sure you want to delete this staff? (Y/N): ";
    cin >> confirm;


    if (confirm == 'Y' || confirm == 'y')
    {
        staffData.erase(it);

        // Rewrite file after deleting
        saveToFile();

        cout << "\nStaff deleted successfully!\n";
        cout << "Data updated in staff.txt\n";
    }
    else
    {
        cout << "\nDelete cancelled.\n";
    }
}


// ==========================================
// 5. SEARCH STAFF
// ==========================================

void StaffManager::searchStaff()
{
    cout << "\n==========================================\n";
    cout << "              SEARCH STAFF\n";
    cout << "==========================================\n";

    if (staffData.empty())
    {
        cout << "\nNo staff data found.\n";
        return;
    }


    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string keyword;

    cout << "Enter ID / Name / Position / Phone / Email: ";
    getline(cin, keyword);


    bool found = false;


    for (const auto& staff : staffData)
    {
        string id = to_string(staff.getId());


        if (
            id == keyword ||
            staff.getName().find(keyword) != string::npos ||
            staff.getGender().find(keyword) != string::npos ||
            staff.getPhoneNumber().find(keyword) != string::npos ||
            staff.getEmail().find(keyword) != string::npos ||
            staff.getPosition().find(keyword) != string::npos
        )
        {
            staff.display();

            found = true;
        }
    }


    if (!found)
    {
        cout << "\nStaff not found!\n";
    }
}


// ==========================================
// STAFF LOGIN
// ==========================================

void StaffManager::staffLogin()
{
    cout << "\n==========================================\n";
    cout << "              STAFF LOGIN\n";
    cout << "==========================================\n";

    if (staffData.empty())
    {
        cout << "\nNo staff data found.\n";
        cout << "Please create a staff first.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string inputUsername;
    string inputPassword;

    cout << "Username: ";
    getline(cin, inputUsername);

    cout << "Password: ";
    getline(cin, inputPassword);


    bool found = false;

    for (const auto& staff : staffData)
    {
        if (staff.getUsername() == inputUsername && staff.getPassword() == inputPassword)
        {
            cout << "\nLogin successfully!\n";

            cout << "\n==========================================\n";
            cout << "            MY PROFILE\n";
            cout << "==========================================\n";

            staff.display();

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nInvalid Username or Password!\n";
    }
}


// ==========================================
// STAFF MANAGEMENT MENU
// ==========================================

void StaffManager::staffMenu()
{
    int choice;

    do
    {
        cout << "\n\n==========================================\n";
        cout << "             STAFF MANAGEMENT\n";
        cout << "==========================================\n";

        cout << "1. Staff Login\n";
        cout << "2. View Staff\n";
        cout << "3. Create Staff\n";
        cout << "4. Update Staff\n";
        cout << "5. Delete Staff\n";
        cout << "6. Search Staff\n";
        cout << "7. Exit\n";

        cout << "==========================================\n";

        cout << "Choose option: ";
        cin >> choice;


        switch (choice)
        {
            case 1:
                staffLogin();
                break;

            case 2:
                viewStaff();
                break;

            case 3:
                createStaff();
                break;

            case 4:
                updateStaff();
                break;

            case 5:
                deleteStaff();
                break;

            case 6:
                searchStaff();
                break;

            case 7:
                cout << "\nExiting Staff Management...\n";
                break;

            default:
                cout << "\nInvalid option!\n";
        }

    } while (choice != 7);
}
