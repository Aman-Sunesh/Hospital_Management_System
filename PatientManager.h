#ifndef PATIENTMANAGER_H
#define PATIENTMANAGER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Patient.h"

using namespace std;

class PersonManager;

class PatientManager {
private:
    vector<Patient*> patientList; // List of doctors

public:
    // Constructor
    PatientManager() = default;

    // Destructor to free dynamically allocated memory
    ~PatientManager();

    // Add a new doctor
    void addPatient(Patient* patient);
    void registerPatient(PersonManager* personManager, const string& name, int ID, const string& password);
    bool deletePatient(int ID);
    void listAllPatients() const;

    // Find a doctor by name
    Patient* findPatientByID(const int ID) const;

};

#endif // PATIENTMANAGER_H
