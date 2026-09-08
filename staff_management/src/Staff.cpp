#include "../include/Staff.h"

#include <iostream>

using namespace std;


// ==========================================
// Default Constructor
// ==========================================

Staff::Staff() : id(0)
{
}


// ==========================================
// Parameterized Constructor
// ==========================================

Staff::Staff(
    int id,
    std::string name,
    std::string gender,
    std::string date_of_birth,
    std::string place_of_birth,
    std::string current_address,
    std::string phone_number,
    std::string email,
    std::string position,
    std::string username,
    std::string password,
    std::string salary,
    std::string status
)
    : id(id),
      name(name),
      gender(gender),
      date_of_birth(date_of_birth),
      place_of_birth(place_of_birth),
      current_address(current_address),
      phone_number(phone_number),
      email(email),
      position(position),
      username(username),
      password(password),
      salary(salary),
      status(status)
{
}


// ==========================================
// Getters
// ==========================================

int Staff::getId() const
{
    return id;
}

std::string Staff::getName() const
{
    return name;
}

std::string Staff::getGender() const
{
    return gender;
}

std::string Staff::getDateOfBirth() const
{
    return date_of_birth;
}

std::string Staff::getPlaceOfBirth() const
{
    return place_of_birth;
}

std::string Staff::getCurrentAddress() const
{
    return current_address;
}

std::string Staff::getPhoneNumber() const
{
    return phone_number;
}

std::string Staff::getEmail() const
{
    return email;
}

std::string Staff::getPosition() const
{
    return position;
}

std::string Staff::getUsername() const
{
    return username;
}

std::string Staff::getPassword() const
{
    return password;
}

std::string Staff::getSalary() const
{
    return salary;
}

std::string Staff::getStatus() const
{
    return status;
}


// ==========================================
// Setters
// ==========================================

void Staff::setName(const std::string& name)
{
    this->name = name;
}

void Staff::setGender(const std::string& gender)
{
    this->gender = gender;
}

void Staff::setDateOfBirth(const std::string& date_of_birth)
{
    this->date_of_birth = date_of_birth;
}

void Staff::setPlaceOfBirth(const std::string& place_of_birth)
{
    this->place_of_birth = place_of_birth;
}

void Staff::setCurrentAddress(const std::string& current_address)
{
    this->current_address = current_address;
}

void Staff::setPhoneNumber(const std::string& phone_number)
{
    this->phone_number = phone_number;
}

void Staff::setEmail(const std::string& email)
{
    this->email = email;
}

void Staff::setPosition(const std::string& position)
{
    this->position = position;
}

void Staff::setUsername(const std::string& username)
{
    this->username = username;
}

void Staff::setPassword(const std::string& password)
{
    this->password = password;
}

void Staff::setSalary(const std::string& salary)
{
    this->salary = salary;
}

void Staff::setStatus(const std::string& status)
{
    this->status = status;
}


// ==========================================
// Display
// ==========================================

void Staff::display() const
{
    cout << "\n------------------------------------------\n";
    cout << "Staff ID        : " << id << "\n";
    cout << "Name            : " << name << "\n";
    cout << "Gender          : " << gender << "\n";
    cout << "Date of Birth   : " << date_of_birth << "\n";
    cout << "Place of Birth  : " << place_of_birth << "\n";
    cout << "Address         : " << current_address << "\n";
    cout << "Phone Number    : " << phone_number << "\n";
    cout << "Email           : " << email << "\n";
    cout << "Position        : " << position << "\n";
    cout << "Username        : " << username << "\n";
    cout << "Salary          : " << salary << "\n";
    cout << "Status          : " << status << "\n";
    cout << "------------------------------------------\n";
}
