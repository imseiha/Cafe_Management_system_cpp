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

    // Authenticates against the existing staff data file. Admin access is
    // granted only to staff whose position is "Admin".
    bool authenticate(Staff& authenticatedStaff, bool requireAdmin);
    void viewStaff();
    // A non-empty role creates the account with that role without prompting.
    void createStaff(const std::string& role = "");
    void updateStaff();
    void deleteStaff();
    void searchStaff();

    void staffMenu();
};

#endif
