#ifndef STAFF_MANAGER_H
#define STAFF_MANAGER_H

#include "Staff.h"
#include <vector>
#include <string>

class StaffManager{
private:
    std::vector<Staff> staffData;

    int nextId;

    const std::string fileName = "staff_management/data/staff.txt";

    void loadFromFile();
    void saveToFile();

    Staff* findStaffById(int id);

public:
    StaffManager();

    void staffLogin();
    void viewStaff();
    void createStaff();
    void updateStaff();
    void deleteStaff();
    void searchStaff();

    void staffMenu();
};

#endif