#include "Staff.h"

#include <iomanip>
#include <iostream>

StaffManager::StaffManager() = default;

void StaffManager::addStaff(const StaffMember& member) {
    staffList_.push_back(member);
}

void StaffManager::showStaff() const {
    std::cout << "\n=== Staff List ===\n";
    for (const auto& member : staffList_) {
        std::cout << member.id << ". " << member.name
                  << " - " << member.role
                  << " - $" << std::fixed << std::setprecision(2) << member.salary << "\n";
    }
    std::cout << "=================\n";
}

const std::vector<StaffMember>& StaffManager::getStaffList() const {
    return staffList_;
}
