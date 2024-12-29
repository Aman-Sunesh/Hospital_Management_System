#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include "Entity.h"

class StaffManager;

using namespace std;

class Person : public Entity
{
    protected:
        string gender;
        string email;
        string mobile;
        string password;

    public:
        // Constructors
        Person() = default; // Default constructor
        Person(const string& name, int ID, const string& gender, const string& emailID, const string&mobileNo);

        int getID() const;

        // If you want a getter for password:
        string getPassword() const;

        void setContactInfo(const string& emailID, const string& mobileNo);
        void setPassword(const string& password);

        // Setters
        void setName(const std::string& newName);
        void setGender(const std::string& newGender);
        void setEmail(const std::string& newEmail);
        void setMobile(const std::string& newMobile);

        // Getters
        string getName() const;
        string getGender() const;
        string getEmail() const;
        string getMobile() const;

        virtual string getRole() const = 0;

        ~Person();

};

#endif // PERSON_H