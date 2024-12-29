#ifndef STAFF_H
#define STAFF_H

#include <iostream>
#include <string>
#include "Person.h"

using namespace std;

class Staff : public Person
{
protected:
    string department;

public:
    // Constructors
    Staff() = default;
    Staff(const string& name, int ID, 
          const string& gender, 
          const string& emailID, 
          const string& mobileNo,
          const string& department);

    // Virtual destructor
    virtual ~Staff() = default;

    // Getters and Setters
    string getDepartment() const;
    void setDepartment(const string& department);

    // Virtual functions
    virtual string getRole() const override;
};

#endif // STAFF_H
