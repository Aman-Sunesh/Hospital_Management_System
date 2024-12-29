#ifndef STAFFMANAGER_H
#define STAFFMANAGER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Doctor.h"
#include "Administrator.h"


using namespace std;

class StaffManager {
private:
    vector<Doctor*> doctorList; // List of doctors
    vector<Administrator*> adminList; // List of Administrators

public:
    // Constructor
    StaffManager() = default;

    // Destructor to free dynamically allocated memory
    ~StaffManager();

    // Add a new doctor
    void addDoctor(Doctor* doctor);
    void registerDoctor(PersonManager* personManager, const std::string& name, int ID, const std::string& password);
    bool deleteDoctor(int ID);
    void listAllDoctors() const;

    void registerDefaultAdministrator(PersonManager* personManager, const string& name, int ID, const string& password);
    void registerAdministrator(PersonManager* personManager, const string& name, int ID, const string& password);
    bool deleteAdministrator(int ID);
    void listAllAdministrators() const;

    // Find a doctor by name
    Doctor* findDoctorByName(const string& name) const;
    Doctor* findDoctorByID(int ID) const;      
    Administrator* findAdministratorByID(int ID) const;  

    // Display departments
    vector<string> displayDepartments() const;


    // Get all doctors
    const vector<Doctor*>& getDoctors() const;
};

#endif // STAFFMANAGER_H
