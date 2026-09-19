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


// ============================================================
// HELPER FUNCTION (local to this file)
// ============================================================
// Prompts the user for a field update.
// If the user presses Enter (empty input), keeps the current value.
// Otherwise, returns the new value entered by the user.

static std::string updateField(const std::string& prompt, const std::string& currentValue)
{
    std::cout << prompt << " (Press Enter to keep '" << currentValue << "'): ";

    std::string input;
    std::getline(std::cin, input);

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
    std::ifstream file(fileName);

    if (!file.is_open())
    {
        return;
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);

        std::string id, name, gender, date_of_birth, place_of_birth;
        std::string current_address, phone_number, email, position;
        std::string username, password, salary, status;

        std::getline(ss, id,              '|');
        std::getline(ss, name,            '|');
        std::getline(ss, gender,          '|');
        std::getline(ss, date_of_birth,   '|');
        std::getline(ss, place_of_birth,  '|');
        std::getline(ss, current_address, '|');
        std::getline(ss, phone_number,    '|');
        std::getline(ss, email,           '|');
        std::getline(ss, position,        '|');
        std::getline(ss, username,        '|');
        std::getline(ss, password,        '|');
        std::getline(ss, salary,          '|');
        std::getline(ss, status,          '|');

        try
        {
            int staffId = std::stoi(id);

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
            std::cout << "Error reading staff data.\n";
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
    std::ofstream file(fileName);

    if (!file.is_open())
    {
        std::cout << "Error: Cannot open staff file!\n";
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
    std::cout << "\n==========================================\n";
    std::cout << "               STAFF LIST\n";
    std::cout << "==========================================\n";

    if (staffData.empty())
    {
        std::cout << "\nNo staff data found.\n";
        std::cout << "Please create a staff first.\n";
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
    std::cout << "\n==========================================\n";
    std::cout << "              CREATE STAFF\n";
    std::cout << "==========================================\n";

    std::string name, gender, date_of_birth, place_of_birth;
    std::string current_address, phone_number, email, position;
    std::string username, password, salary, status;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter Full Name: ";
    std::getline(std::cin, name);

    std::cout << "Enter Gender (Male/Female): ";
    std::getline(std::cin, gender);

    std::cout << "Enter Date of Birth (DD/MM/YYYY): ";
    std::getline(std::cin, date_of_birth);

    std::cout << "Enter Place of Birth: ";
    std::getline(std::cin, place_of_birth);

    std::cout << "Enter Current Address: ";
    std::getline(std::cin, current_address);

    std::cout << "Enter Phone Number: ";
    std::getline(std::cin, phone_number);

    std::cout << "Enter Email: ";
    std::getline(std::cin, email);

    std::cout << "Enter Position: ";
    std::getline(std::cin, position);

    std::cout << "Enter Username: ";
    std::getline(std::cin, username);

    std::cout << "Enter Password: ";
    std::getline(std::cin, password);

    std::cout << "Enter Salary: ";
    std::getline(std::cin, salary);

    std::cout << "Enter Status (Active/Inactive): ";
    std::getline(std::cin, status);


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
        std::cout << "\nInvalid input!\n";
        std::cout << "All fields are required.\n";
        return;
    }


    // --- Validation: username must be unique ---

    for (const auto& staff : staffData)
    {
        if (staff.getUsername() == username)
        {
            std::cout << "\nUsername already exists!\n";
            std::cout << "Please use another username.\n";
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

    std::cout << "\nStaff created successfully!\n";
    std::cout << "Staff ID: " << newStaff.getId() << std::endl;
    std::cout << "Data saved to staff.txt\n";
}


// ------------------------------------
// updateStaff
// ------------------------------------
// Finds a staff member by ID, shows current info,
// then lets the user update each field (press Enter to skip).
// Uses the updateField() helper to avoid repeating code.

void StaffManager::updateStaff()
{
    std::cout << "\n==========================================\n";
    std::cout << "              UPDATE STAFF\n";
    std::cout << "==========================================\n";

    int id;

    std::cout << "Enter Staff ID: ";
    std::cin >> id;

    Staff* staff = findStaffById(id);

    if (staff == nullptr)
    {
        std::cout << "\nStaff not found!\n";
        return;
    }

    std::cout << "\nCurrent Staff Information:";
    staff->display();

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    // --- Update each field (Enter to keep current value) ---

    std::string name            = updateField("Enter new Name",            staff->getName());
    std::string gender          = updateField("Enter new Gender",          staff->getGender());
    std::string date_of_birth   = updateField("Enter new Date of Birth",   staff->getDateOfBirth());
    std::string place_of_birth  = updateField("Enter new Place of Birth",  staff->getPlaceOfBirth());
    std::string current_address = updateField("Enter new Current Address", staff->getCurrentAddress());
    std::string phone_number    = updateField("Enter new Phone Number",    staff->getPhoneNumber());
    std::string email           = updateField("Enter new Email",           staff->getEmail());
    std::string position        = updateField("Enter new Position",        staff->getPosition());
    std::string username        = updateField("Enter new Username",        staff->getUsername());
    std::string password        = updateField("Enter new Password",        staff->getPassword());
    std::string salary          = updateField("Enter new Salary",          staff->getSalary());
    std::string status          = updateField("Enter new Status",          staff->getStatus());


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

    std::cout << "\nStaff updated successfully!\n";
    std::cout << "Data updated in staff.txt\n";
}


// ------------------------------------
// deleteStaff
// ------------------------------------
// Finds a staff member by ID, shows their info,
// asks for confirmation, then deletes and saves.

void StaffManager::deleteStaff()
{
    std::cout << "\n==========================================\n";
    std::cout << "              DELETE STAFF\n";
    std::cout << "==========================================\n";

    int id;

    std::cout << "Enter Staff ID: ";
    std::cin >> id;


    auto it = std::find_if(
        staffData.begin(),
        staffData.end(),
        [id](const Staff& staff)
        {
            return staff.getId() == id;
        }
    );


    if (it == staffData.end())
    {
        std::cout << "\nStaff not found!\n";
        return;
    }


    std::cout << "\nStaff found:";
    it->display();


    char confirm;

    std::cout << "\nAre you sure you want to delete this staff? (Y/N): ";
    std::cin >> confirm;


    if (confirm == 'Y' || confirm == 'y')
    {
        staffData.erase(it);
        saveToFile();

        std::cout << "\nStaff deleted successfully!\n";
        std::cout << "Data updated in staff.txt\n";
    }
    else
    {
        std::cout << "\nDelete cancelled.\n";
    }
}


// ------------------------------------
// searchStaff
// ------------------------------------
// Searches staff by keyword across multiple fields:
// ID, Name, Gender, Phone, Email, Position.

void StaffManager::searchStaff()
{
    std::cout << "\n==========================================\n";
    std::cout << "              SEARCH STAFF\n";
    std::cout << "==========================================\n";

    if (staffData.empty())
    {
        std::cout << "\nNo staff data found.\n";
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string keyword;

    std::cout << "Enter ID / Name / Position / Phone / Email: ";
    std::getline(std::cin, keyword);


    bool found = false;

    for (const auto& staff : staffData)
    {
        std::string id = std::to_string(staff.getId());

        if (
            id.find(keyword)                   != std::string::npos ||
            staff.getName().find(keyword)       != std::string::npos ||
            staff.getGender().find(keyword)     != std::string::npos ||
            staff.getPhoneNumber().find(keyword) != std::string::npos ||
            staff.getEmail().find(keyword)      != std::string::npos ||
            staff.getPosition().find(keyword)   != std::string::npos
        )
        {
            staff.display();
            found = true;
        }
    }


    if (!found)
    {
        std::cout << "\nStaff not found!\n";
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
    std::cout << "\n==========================================\n";
    std::cout << "              STAFF LOGIN\n";
    std::cout << "==========================================\n";

    if (staffData.empty())
    {
        std::cout << "\nNo staff data found.\n";
        std::cout << "Please create a staff first.\n";
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string inputUsername;
    std::string inputPassword;

    std::cout << "Username: ";
    std::getline(std::cin, inputUsername);

    std::cout << "Password: ";
    std::getline(std::cin, inputPassword);


    bool found = false;

    for (const auto& staff : staffData)
    {
        if (staff.getUsername() == inputUsername && staff.getPassword() == inputPassword)
        {
            std::cout << "\nLogin successfully!\n";

            std::cout << "\n==========================================\n";
            std::cout << "            MY PROFILE\n";
            std::cout << "==========================================\n";

            staff.display();

            found = true;
            break;
        }
    }

    if (!found)
    {
        std::cout << "\nInvalid Username or Password!\n";
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
        std::cout << "\n\n==========================================\n";
        std::cout << "             STAFF MANAGEMENT\n";
        std::cout << "==========================================\n";

        std::cout << "1. Staff Login\n";
        std::cout << "2. View Staff\n";
        std::cout << "3. Create Staff\n";
        std::cout << "4. Update Staff\n";
        std::cout << "5. Delete Staff\n";
        std::cout << "6. Search Staff\n";
        std::cout << "7. Exit\n";

        std::cout << "==========================================\n";

        std::cout << "Choose option: ";
        std::cin >> choice;


        switch (choice)
        {
            case 1: staffLogin();   break;
            case 2: viewStaff();    break;
            case 3: createStaff();  break;
            case 4: updateStaff();  break;
            case 5: deleteStaff();  break;
            case 6: searchStaff();  break;

            case 7:
                std::cout << "\nExiting Staff Management...\n";
                break;

            default:
                std::cout << "\nInvalid option!\n";
        }

    } while (choice != 7);
}
