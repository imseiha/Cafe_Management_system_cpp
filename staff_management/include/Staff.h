#ifndef STAFF_H
#define STAFF_H

#include <string>

class Staff {
 
    private:
    int id;
    std::string name;
    std::string gender;
    std::string date_of_birth;
    std::string place_of_birth;
    std::string current_address;
    std::string phone_number;
    std::string email;
    std::string position;
    std::string username;
    std::string password;
    std::string salary;
    std::string status;

    public: 

    Staff();

    Staff(
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
    );

    //Getters
    int getId() const;
    std::string getName() const;
    std::string getGender() const;
    std::string getDateOfBirth() const;
    std::string getPlaceOfBirth() const;
    std::string getCurrentAddress() const;
    std::string getPhoneNumber() const;
    std::string getEmail() const;
    std::string getPosition() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getSalary() const;
    std::string getStatus() const;

    // Setters
    void setName(const std::string& name);
    void setGender(const std::string& gender);
    void setDateOfBirth(const std::string& date_of_birth);
    void setPlaceOfBirth(const std::string& place_of_birth);
    void setCurrentAddress(const std::string& current_address);
    void setPhoneNumber(const std::string& phone_number);
    void setEmail(const std::string& email);
    void setPosition(const std::string& position);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setSalary(const std::string& salary);
    void setStatus(const std::string& status);

    void display() const;

};
#endif
