#include "StaffManager.h"
#include "PersonManager.h" 
#include "Doctor.h"
#include "Administrator.h"
#include <iostream>


using namespace std;

void StaffManager::addDoctor(Doctor* doctor)
{
    doctorList.push_back(doctor);
}

Doctor* StaffManager::findDoctorByName(const string& name) const 
{
    for (size_t i = 0 ; i < doctorList.size() ; i++)
    {
        if (doctorList[i]->getName() == name)
        {
            return doctorList[i];
        }
    }

    return nullptr;
}

Doctor* StaffManager::findDoctorByID(int ID) const
{
    for (auto* doc : doctorList) {
        if (doc->getID() == ID) {
            return doc;
        }
    }
    return nullptr;
}

Administrator* StaffManager::findAdministratorByID(int ID) const
{
    for (auto* admin : adminList) {
        if (admin->getID() == ID) {
            return admin;
        }
    }
    return nullptr;
}

vector<string> StaffManager::displayDepartments() const
{
    vector<string> departments;

    for (size_t i = 0 ; i < doctorList.size() ; i++)
    {
        string dept = doctorList[i]->getDepartment();

        if (find(departments.begin(), departments.end(), dept) == departments.end())
        {
            departments.push_back(dept); // Add if not already present
        }
    }

    return departments;

}


// 1) Register doctor
void StaffManager::registerDoctor(PersonManager* personManager, const std::string& name, int ID, const std::string& password)
{

    // Prompt for gender
    cout << "Enter doctor's gender (optional, press Enter to skip): ";
    string gender;
    getline(cin, gender);

    // If empty, default to "N/A"
    if (gender.empty()) {
        gender = "N/A";
    }

    // Prompt for email
    cout << "Enter doctor's email (optional, press Enter to skip): ";
    string email;
    getline(cin, email);

    // If empty, default to "unknown@patient.com"
    if (email.empty()) {
        email = "unknown@patient.com";
    }

    // Prompt for mobile
    cout << "Enter doctor's mobile number (optional, press Enter to skip): ";
    string mobile;
    getline(cin, mobile);

    // If empty, default to "000-000-0000"
    if (mobile.empty()) {
        mobile = "000-000-0000";
    }

    // Prompt for department
    cout << "Enter doctor's department (optional, press Enter to skip): ";
    string department;
    getline(cin, department);

    // If empty, default to "000-000-0000"
    if (department.empty()) {
        department = "General";
    }
    
    // Now create a new Doctor with all these fields
    Doctor* newDoc  = new Doctor(
        name,      // from Administrator
        ID,        // from Administrator (GenerateAccount)
        gender,
        email,
        mobile, 
        department
    );

    // Possibly set password if your Doctor or Staff class has setPassword() 
    newDoc->setPassword(password);

    doctorList.push_back(newDoc);

    personManager->addPerson(newDoc); // Ensure PersonManager has addPerson()
}

// 2) Delete doctor
bool StaffManager::deleteDoctor(int ID)
{
    for (size_t i = 0; i < doctorList.size(); i++)
    {
        if (doctorList[i]->getID() == ID)
        {
            Doctor* toDelete = doctorList[i];
            doctorList.erase(doctorList.begin() + i);
            delete toDelete;
            return true;
        }
    }
    return false;
}

// 3) List all doctors
void StaffManager::listAllDoctors() const
{
    if (doctorList.empty()) {
        cout << "No doctors available.\n";
        return;
    }
    cout << "List of all Doctors:\n";
    for (auto* d : doctorList)
    {
        cout << "  ID: " << d->getID() 
             << " | Name: " << d->getName() << "\n";
    }
}

void StaffManager::registerDefaultAdministrator(PersonManager* personManager, const string& name, int ID, const string& password)
{
    Administrator* newAdmin = new Administrator(
        name, 
        ID, 
        "M",
        "defaultadministrator@abc.com",
        "000-0000-0000"
    );

    // If your Administrator inherits setPassword from Person or Staff
    newAdmin->setPassword(password);

    adminList.push_back(newAdmin);

    personManager->addPerson(newAdmin); // Ensure PersonManager has addPerson()
}

// 1) Register Administrator
void StaffManager::registerAdministrator(PersonManager* personManager, const std::string& name, int ID, const std::string& password)
{
    // Prompt for gender
    cout << "Enter admins's gender (optional, press Enter to skip): ";
    string gender;
    getline(cin, gender);

    // If empty, default to "N/A"
    if (gender.empty()) {
        gender = "N/A";
    }

    // Prompt for email
    cout << "Enter admins's email (optional, press Enter to skip): ";
    string email;
    getline(cin, email);

    // If empty, default to "unknown@patient.com"
    if (email.empty()) {
        email = "unknown@patient.com";
    }

    // Prompt for mobile
    cout << "Enter admins's mobile number (optional, press Enter to skip): ";
    string mobile;
    getline(cin, mobile);

    // If empty, default to "000-000-0000"
    if (mobile.empty()) {
        mobile = "000-000-0000";
    }

    Administrator* newAdmin = new Administrator(
        name, 
        ID, 
        gender,
        email,
        mobile
    );
    // If your Administrator inherits setPassword from Person or Staff
    newAdmin->setPassword(password);

    adminList.push_back(newAdmin);

    // Register with PersonManager for authentication
    personManager->addPerson(newAdmin);
}

// 2) Delete Administrator
bool StaffManager::deleteAdministrator(int ID)
{
    for (size_t i = 0; i < adminList.size(); i++)
    {
        if (adminList[i]->getID() == ID)
        {
            Administrator* toDelete = adminList[i];
            adminList.erase(adminList.begin() + i);
            delete toDelete;
            return true;
        }
    }
    return false;
}

// 3) List all Administrators
void StaffManager::listAllAdministrators() const
{
    if (adminList.empty()) {
        cout << "No administrators available.\n";
        return;
    }
    cout << "List of all Administrators:\n";
    for (auto* a : adminList)
    {
        cout << "  ID: " << a->getID() 
             << " | Name: " << a->getName() << "\n";
    }
}


StaffManager::~StaffManager() {
    // 1) Delete Doctors
    for (size_t i = 0; i < doctorList.size(); i++) {
        delete doctorList[i];
    }
    doctorList.clear();

    // 2) Delete Administrators
    for (size_t i = 0; i < adminList.size(); i++) {
        delete adminList[i];
    }
    adminList.clear();
}

const vector<Doctor*>& StaffManager::getDoctors() const {
    return doctorList;
}