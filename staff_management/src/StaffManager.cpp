// ============================================================
// StaffManager.cpp
//
// This file manages all staff operations:
//   - Loading and saving staff data from/to file
//   - CRUD operations (Create, View, Search, Update, Delete)
//   - Staff login
//   - Staff management menu
//
// File format (pipe-delimited, one staff per line):
//   id|name|gender|dob|pob|address|phone|email|position|username|password|salary|status
// ============================================================

#include "../include/StaffManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;


// ============================================================
// HELPER FUNCTION (local to this file)
// ============================================================
// Prompts the user for a field update.
// If the user presses Enter (empty input), keeps the current value.
// Otherwise, returns the new value entered by the user.

static string updateField(const string& prompt, const string& currentValue)
{
    cout << prompt << " (Press Enter to keep '" << currentValue << "'): ";

    string input;
    getline(cin, input);

    return input.empty() ? currentValue : input;
}


// ============================================================
// CONSTRUCTOR
// ============================================================
// Initializes nextId to 1, then loads existing staff from file.

StaffManager::StaffManager()
{
    nextId = 1;
    loadFromFile();
}


// ============================================================
// SECTION 1: FILE I/O
// ============================================================

// ------------------------------------
// loadFromFile
// ------------------------------------
// Reads staff_management/data/staff.txt line by line.
// Each line is pipe-delimited and creates a Staff object.
// If the file doesn't exist, starts with empty data.
// Also calculates nextId as the highest existing ID + 1.

void StaffManager::loadFromFile()
{
    ifstream file(fileName);

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

        string id, name, gender, date_of_birth, place_of_birth;
        string current_address, phone_number, email, position;
        string username, password, salary, status;

        getline(ss, id,              '|');
        getline(ss, name,            '|');
        getline(ss, gender,          '|');
        getline(ss, date_of_birth,   '|');
        getline(ss, place_of_birth,  '|');
        getline(ss, current_address, '|');
        getline(ss, phone_number,    '|');
        getline(ss, email,           '|');
        getline(ss, position,        '|');
        getline(ss, username,        '|');
        getline(ss, password,        '|');
        getline(ss, salary,          '|');
        getline(ss, status,          '|');

        try
        {
            int staffId = stoi(id);

            Staff staff(
                staffId, name, gender, date_of_birth,
                place_of_birth, current_address, phone_number,
                email, position, username, password,
                salary, status
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


// ------------------------------------
// saveToFile
// ------------------------------------
// Writes all staff data back to staff.txt.
// Overwrites the entire file with current vector contents.

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
        file << staff.getId()            << "|"
             << staff.getName()          << "|"
             << staff.getGender()        << "|"
             << staff.getDateOfBirth()   << "|"
             << staff.getPlaceOfBirth()  << "|"
             << staff.getCurrentAddress() << "|"
             << staff.getPhoneNumber()   << "|"
             << staff.getEmail()         << "|"
             << staff.getPosition()      << "|"
             << staff.getUsername()      << "|"
             << staff.getPassword()      << "|"
             << staff.getSalary()        << "|"
             << staff.getStatus()
             << "\n";
    }

    file.close();
}


// ============================================================
// SECTION 2: FIND STAFF
// ============================================================

// ------------------------------------
// findStaffById
// ------------------------------------
// Searches staffData for a staff member with the given ID.
// Returns a pointer to the Staff object if found, nullptr otherwise.
// This is a private helper used by updateStaff and deleteStaff.

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


// ============================================================
// SECTION 3: CRUD OPERATIONS
// ============================================================

// ------------------------------------
// viewStaff
// ------------------------------------
// Displays all staff members in the system.

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


// ------------------------------------
// createStaff
// ------------------------------------
// Prompts the user for all staff fields, validates input,
// checks for duplicate username, creates the Staff object,
// adds it to the vector, and saves to file.

void StaffManager::createStaff()
{
    cout << "\n==========================================\n";
    cout << "              CREATE STAFF\n";
    cout << "==========================================\n";

    string name, gender, date_of_birth, place_of_birth;
    string current_address, phone_number, email, position;
    string username, password, salary, status;

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


    // --- Validation: all fields required ---

    if (
        name.empty()            || gender.empty()       ||
        date_of_birth.empty()   || place_of_birth.empty()||
        current_address.empty() || phone_number.empty()  ||
        email.empty()           || position.empty()      ||
        username.empty()        || password.empty()      ||
        salary.empty()          || status.empty()
    )
    {
        cout << "\nInvalid input!\n";
        cout << "All fields are required.\n";
        return;
    }


    // --- Validation: username must be unique ---

    for (const auto& staff : staffData)
    {
        if (staff.getUsername() == username)
        {
            cout << "\nUsername already exists!\n";
            cout << "Please use another username.\n";
            return;
        }
    }


    // --- Create Staff and save ---

    Staff newStaff(
        nextId, name, gender, date_of_birth,
        place_of_birth, current_address, phone_number,
        email, position, username, password,
        salary, status
    );

    staffData.push_back(newStaff);
    nextId++;

    saveToFile();

    cout << "\nStaff created successfully!\n";
    cout << "Staff ID: " << newStaff.getId() << endl;
    cout << "Data saved to staff.txt\n";
}


// ------------------------------------
// updateStaff
// ------------------------------------
// Finds a staff member by ID, shows current info,
// then lets the user update each field (press Enter to skip).
// Uses the updateField() helper to avoid repeating code.

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


    // --- Update each field (Enter to keep current value) ---

    string name            = updateField("Enter new Name",            staff->getName());
    string gender          = updateField("Enter new Gender",          staff->getGender());
    string date_of_birth   = updateField("Enter new Date of Birth",   staff->getDateOfBirth());
    string place_of_birth  = updateField("Enter new Place of Birth",  staff->getPlaceOfBirth());
    string current_address = updateField("Enter new Current Address", staff->getCurrentAddress());
    string phone_number    = updateField("Enter new Phone Number",    staff->getPhoneNumber());
    string email           = updateField("Enter new Email",           staff->getEmail());
    string position        = updateField("Enter new Position",        staff->getPosition());
    string username        = updateField("Enter new Username",        staff->getUsername());
    string password        = updateField("Enter new Password",        staff->getPassword());
    string salary          = updateField("Enter new Salary",          staff->getSalary());
    string status          = updateField("Enter new Status",          staff->getStatus());


    // --- Apply updates to the staff object ---

    staff->setName(name);
    staff->setGender(gender);
    staff->setDateOfBirth(date_of_birth);
    staff->setPlaceOfBirth(place_of_birth);
    staff->setCurrentAddress(current_address);
    staff->setPhoneNumber(phone_number);
    staff->setEmail(email);
    staff->setPosition(position);
    staff->setUsername(username);
    staff->setPassword(password);
    staff->setSalary(salary);
    staff->setStatus(status);


    // --- Save ---

    saveToFile();

    cout << "\nStaff updated successfully!\n";
    cout << "Data updated in staff.txt\n";
}


// ------------------------------------
// deleteStaff
// ------------------------------------
// Finds a staff member by ID, shows their info,
// asks for confirmation, then deletes and saves.

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
        saveToFile();

        cout << "\nStaff deleted successfully!\n";
        cout << "Data updated in staff.txt\n";
    }
    else
    {
        cout << "\nDelete cancelled.\n";
    }
}


// ------------------------------------
// searchStaff
// ------------------------------------
// Searches staff by keyword across multiple fields:
// ID, Name, Gender, Phone, Email, Position.

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
            id.find(keyword)                   != string::npos ||
            staff.getName().find(keyword)       != string::npos ||
            staff.getGender().find(keyword)     != string::npos ||
            staff.getPhoneNumber().find(keyword) != string::npos ||
            staff.getEmail().find(keyword)      != string::npos ||
            staff.getPosition().find(keyword)   != string::npos
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


// ============================================================
// SECTION 4: AUTHENTICATION
// ============================================================

// ------------------------------------
// staffLogin
// ------------------------------------
// Prompts for username and password, searches staffData,
// and displays the matched staff member's profile.

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


// ============================================================
// SECTION 5: MENU
// ============================================================

// ------------------------------------
// staffMenu
// ------------------------------------
// Displays the Staff Management menu and handles user choice.
// This is the main entry point called from main.cpp.

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
            case 1: staffLogin();   break;
            case 2: viewStaff();    break;
            case 3: createStaff();  break;
            case 4: updateStaff();  break;
            case 5: deleteStaff();  break;
            case 6: searchStaff();  break;

            case 7:
                cout << "\nExiting Staff Management...\n";
                break;

            default:
                cout << "\nInvalid option!\n";
        }

    } while (choice != 7);
}
