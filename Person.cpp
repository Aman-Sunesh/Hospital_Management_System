#include "Person.h"
#include <iostream>
#include <algorithm>

using namespace std;

Person::Person(const string& name, int ID, const string& gender, const string& emailID, const string& mobileNo)
{
    this->name = name;
    this->ID = ID;
    this->gender = gender;
    this->email = emailID;
    this->mobile = mobileNo;
}



// Returns the netID of the user
int Person::getID() const
{
    return ID;
}

// Returns the password of the user
string Person::getPassword() const
{
    return password;
}

void Person::setName(const string& newName)
{
    name = newName;
}

// Setter for gender
void Person::setGender(const string& newGender) {
    if (newGender == "Male" || newGender == "Female" || newGender == "Other") {
        gender = newGender;
    } else {
        cerr << "Error: Invalid gender. Please enter 'Male', 'Female', or 'Other'.\n";
    }
}

// Setter for email
void Person::setEmail(const string& newEmail) {
    if (newEmail.find('@') != string::npos && newEmail.find('.') != string::npos) {
        email = newEmail;
    } else {
        cerr << "Error: Invalid email format.\n";
    }
}

// Setter for mobile
void Person::setMobile(const string& newMobile) {
    if (newMobile.length() == 10 && all_of(newMobile.begin(), newMobile.end(), ::isdigit)) {
        mobile = newMobile;
    } else {
        cerr << "Error: Mobile number must be 10 digits.\n";
    }
}

string Person::getName() const { return name; }
string Person::getGender() const { return gender; }
string Person::getEmail() const { return email; }
string Person::getMobile() const { return mobile; }

void Person::setContactInfo(const string& emailID, const string& mobileNo)
{
    this->email = emailID;
    this->mobile = mobileNo;
}

void Person::setPassword(const string& password)
{
    this->password = password;
}


Person::~Person() {
}
