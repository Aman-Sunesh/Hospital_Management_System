#include "PatientManager.h"
#include "PersonManager.h"
#include <iostream>
#include <limits>

using namespace std;


void PatientManager::addPatient(Patient* patient)
{
    patientList.push_back(patient);
}

Patient* PatientManager::findPatientByID(const int ID) const
{
    for (size_t i = 0 ; i < patientList.size() ; i++)
    {
        if (patientList[i]->getID() == ID)
        {
            return patientList[i];
        }
    }

    return nullptr;
}


void PatientManager::registerPatient(PersonManager* personManager, const string& name, int ID, const string& password)
{

    // Prompt for gender
    cout << "Enter patient gender (optional, press Enter to skip): ";
    string gender;
    getline(cin, gender);

    // If empty, default to "N/A"
    if (gender.empty()) {
        gender = "N/A";
    }

    // Prompt for email
    cout << "Enter patient email (optional, press Enter to skip): ";
    string email;
    getline(cin, email);

    // If empty, default to "unknown@patient.com"
    if (email.empty()) {
        email = "unknown@patient.com";
    }

    // Prompt for mobile
    cout << "Enter patient mobile number (optional, press Enter to skip): ";
    string mobile;
    getline(cin, mobile);

    // If empty, default to "000-000-0000"
    if (mobile.empty()) {
        mobile = "000-000-0000";
    }

    // Now create a new Patient with all these fields
    Patient* newPatient = new Patient(
        name,      // from Administrator
        ID,        // from Administrator (GenerateAccount)
        gender,
        email,
        mobile
    );


    // Set the password if your Patient class has a setter:
    newPatient->setPassword(password);

    patientList.push_back(newPatient);

    // Register with PersonManager for authentication
    personManager->addPerson(newPatient);

}

// 2) Delete a patient by ID
bool PatientManager::deletePatient(int ID)
{
    for (size_t i = 0; i < patientList.size(); i++)
    {
        if (patientList[i]->getID() == ID)
        {
            // Found the patient -> erase from vector and delete
            Patient* toDelete = patientList[i];
            patientList.erase(patientList.begin() + i);
            delete toDelete;
            return true;
        }
    }
    return false;
}

// 3) List all patients
void PatientManager::listAllPatients() const
{
    if (patientList.empty()) {
        cout << "No patients available.\n";
        return;
    }

    cout << "List of all patients:\n";
    for (auto* p : patientList)
    {
        // You can print name/ID, etc.
        cout << "  ID: " << p->getID() 
             << " | Name: " << p->getName()<< "\n";
    }
}



PatientManager::~PatientManager() {
    for (size_t i = 0; i < patientList.size(); i++) {
        delete patientList[i]; // Clean up dynamically allocated patients
    }
    patientList.clear();       // Not strictly required but keeps the vector empty
}