#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "Staff.h"
#include "SharedTypes.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class StaffManager; // Forward declaration for StaffManager class
class PatientManager; // Forward declaration for PatientManager class
class PersonManager; // Forward declatation for PersonManager class

class Administrator : public Staff {
private:
    int ID; // Administrator ID
    string name;
    string password;
    string gender;
    string email;
    string mobile;
    StaffManager* S; // Pointer to StaffManager
    PatientManager* P; // Pointer to PatientManager
    PersonManager* PP; // Pointer to PersonManager

public:
    // Constructors
    Administrator();
    Administrator(const string& name, int ID, const string& gender,
                  const string& email, const string& mobile);


    // Set pointers to other managers
    void setStaffManager(StaffManager* staffManager);
    void setPatientManager(PatientManager* patientManager);
    void setPersonManager(PersonManager* personManager);

    // Override methods from Staff
    virtual string getRole() const override;
    void displayMenu();

    // Additional methods
    void addPatient();
    void addDoctor();
    void addAdministrator();

    void deletePatient();
    void deleteDoctor();
    void deleteAdministrator();

    void modifyPatient();
    void modifyDoctor();
    void modifyAdministrator();

    void findUser();

    void manageDepartments();

    void viewAllPatients() const;
    void viewAllDoctors() const;
    void viewAllAdministrators() const;

    // Destructor
    virtual ~Administrator();
};

#endif // ADMINISTRATOR_H
