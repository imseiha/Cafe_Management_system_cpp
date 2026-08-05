#ifndef STAFF_H
#define STAFF_H

#include <string>
#include <vector>

struct StaffMember {
    int id;
    std::string name;
    std::string role;
    double salary;
};

class StaffManager {
public:
    StaffManager();
    void addStaff(const StaffMember& member);
    void showStaff() const;
    const std::vector<StaffMember>& getStaffList() const;

private:
    std::vector<StaffMember> staffList_;
};

#endif
