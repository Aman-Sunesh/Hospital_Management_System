#include "Staff.h"
#include <iostream>

using namespace std;

// Constructor
Staff::Staff(const string& name, int ID, 
             const string& gender, 
             const string& emailID,
             const string& mobileNo,
             const string& department)
: Person(name, ID, gender, emailID, mobileNo)
{
    this->department  = department;
}

// Getters
string Staff::getDepartment() const
{
    return department;
}

// Setters
void Staff::setDepartment(const string& department)
{
    this->department = department;
}

// Role description
string Staff::getRole() const
{
    return "Staff";
}
