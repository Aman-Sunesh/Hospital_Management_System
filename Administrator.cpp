#include "Administrator.h"
#include "Patient.h"
#include "Doctor.h"
#include "StaffManager.h"
#include "PatientManager.h"
#include "PersonManager.h"
#include "Utility.h"
#include "GenerateAccount.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <thread>

using namespace std;

// Default constructor
Administrator::Administrator() : Staff("DefaultAdmin", 100000, "Female", "admin@demo.com", "9999999999", "AdminDept") {
    password = "abcdefgh";
    S = nullptr;
    P = nullptr;
    PP = nullptr;
}

// Parameterized constructor
Administrator::Administrator(const string& name, int ID, const string& gender,
                             const string& email, const string& mobile)
    : Staff(name, ID, gender, email, mobile, "Admin") {
    password = "abcdefgh";
    S = nullptr;
    P = nullptr;
    PP = nullptr;
}


void Administrator::setStaffManager(StaffManager* staffManager) {
    if (!staffManager) {
        cout << "Error: Attempted to set a null StaffManager.\n";
        return;
    }
    this->S = staffManager;
}

void Administrator::setPatientManager(PatientManager* patientManager) {
    if (!patientManager) {
        cout << "Error: Attempted to set a null PatientManager.\n";
        return;
    }
    this->P = patientManager;
    
}

void Administrator::setPersonManager(PersonManager* personManager) {
    if (!personManager) {
        cout << "Error: Attempted to set a null PersonManager.\n";
        return;
    }
    this->PP = personManager;
}

// Getter for role
string Administrator::getRole() const {
    return "Administrator";
}


// Display menu
void Administrator::displayMenu() {
    do {
        cout << "----------------------------------\n";
        cout << "|      Administrator Menu        |\n";
        cout << "----------------------------------\n";
        cout << "| 1. Add Patient                 |\n";
        cout << "| 2. Add Doctor                  |\n";
        cout << "| 3. Add Administrator           |\n";
        cout << "| 4. Delete Patient              |\n";
        cout << "| 5. Delete Doctor               |\n";
        cout << "| 6. Delete Administrator        |\n";
        cout << "| 7. Modify Patient              |\n";
        cout << "| 8. Modify Doctor               |\n";
        cout << "| 9. Modify Administrator        |\n";
        cout << "| 10. Find User                  |\n";
        cout << "| 11. View All Patients          |\n";
        cout << "| 12. View All Doctors           |\n";
        cout << "| 13. View All Administrators    |\n";
        cout << "| 14. Exit                       |\n";
        cout << "----------------------------------\n";

        int choice;
        do {
            cout << "Enter your choice (1-14): ";
            if (isInvalidInput(choice)) continue;
            if (choice < 1 || choice > 14) {
                cout << "Error! Invalid choice. Please try again.\n";
            }
        } while (choice < 1 || choice > 14);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: addDoctor(); break;
            case 3: addAdministrator(); break;
            case 4: deletePatient(); break;
            case 5: deleteDoctor(); break;
            case 6: deleteAdministrator(); break;
            case 7: modifyPatient(); break;
            case 8: modifyDoctor(); break;
            case 9: modifyAdministrator(); break;
            case 10: findUser(); break;
            case 11: viewAllPatients(); break;
            case 12: viewAllDoctors(); break;
            case 13: viewAllAdministrators(); break;
            case 14: cout << "Exiting...\n"; return;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (true);
}

// Add patient
void Administrator::addPatient() {

    if (!P || !PP) {
        cout << "Error: PatientManager or PersonManager is not initialized. Cannot add patient.\n";
        return;
    }

    // Clear any leftover characters in the input buffer to prevent them from being consumed by getline
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    
    string name;
    do {
        cout << "Enter patient name: ";
    } while (isInvalidInput(name));

    int ID = GenerateAccount::generateUniqueID();
    string password = GenerateAccount::generatePassword();

    P->registerPatient(PP, name, ID, password);

    cout << "Patient added successfully!\n";
    cout << "ID: " << ID << " | Password: " << password << endl;

    // Prompt the user to press enter to continue
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Wait for Enter key

    clearScreen();
}

// Add doctor
void Administrator::addDoctor() {

    if (!S || !PP) {
        cout << "Error: StaffManager or PersonManager is not initialized. Cannot add patient.\n";
        return;
    }

    if (cin.peek() == '\n') {
        cin.ignore();
    }

    string name;
    do {
        cout << "Enter doctor name: ";
    } while (isInvalidInput(name));

    int ID = GenerateAccount::generateUniqueID();
    string password = GenerateAccount::generatePassword();

    S->registerDoctor(PP, name, ID, password);

    cout << "Doctor added successfully!\n";
    cout << "ID: " << ID << " | Password: " << password << endl;

    // Prompt the user to press enter to continue
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Wait for Enter key

    clearScreen();
}

// Add administrator
void Administrator::addAdministrator() {

    if (!S || !PP) {
        cout << "Error: StaffManager or PersonManager is not initialized. Cannot add patient.\n";
        return;
    }

    if (cin.peek() == '\n') {
        cin.ignore();
    }

    string name;
    do {
        cout << "Enter administrator name: ";
    } while (isInvalidInput(name));

    int ID = GenerateAccount::generateUniqueID();
    string password = GenerateAccount::generatePassword();

    S->registerAdministrator(PP, name, ID, password);

    cout << "Administrator added successfully!\n";
    cout << "ID: " << ID << " | Password: " << password << endl;

    // Prompt the user to press enter to continue
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Wait for Enter key

    clearScreen();
}

// Delete patient
void Administrator::deletePatient() {
    int ID;
    cout << "Enter Patient ID to delete: ";
    cin >> ID;

    if (P->deletePatient(ID)) {
        cout << "Patient deleted successfully.\n";
    } else {
        cout << "Patient not found.\n";
    }
}

// Delete doctor
void Administrator::deleteDoctor() {
    int ID;
    cout << "Enter Doctor ID to delete: ";
    cin >> ID;

    if (S->deleteDoctor(ID)) {
        cout << "Doctor deleted successfully.\n";
    } else {
        cout << "Doctor not found.\n";
    }
}

// Delete administrator
void Administrator::deleteAdministrator() {
    int ID;
    cout << "Enter Administrator ID to delete: ";
    cin >> ID;

    if (S->deleteAdministrator(ID)) {
        cout << "Administrator deleted successfully.\n";
    } else {
        cout << "Administrator not found.\n";
    }
}

void Administrator::modifyPatient()
{
    cout << "\n=== Modify Patient ===" << endl;
    cout << "Enter Patient ID to modify: ";
    int patientID;
    cin >> patientID;

    Patient* patient = P->findPatientByID(patientID);
    if (!patient)
    {
        cout << "Patient with ID " << patientID << " not found.\n";
        return;
    }

    // Show current details
    cout << "\nCurrent Details:\n";
    cout << "  Name:   " << patient->getName()   << "\n";
    cout << "  Gender: " << patient->getGender() << "\n";
    cout << "  Email:  " << patient->getEmail()  << "\n";
    cout << "  Mobile: " << patient->getMobile() << "\n";

    // Prompt for new info; skip if Enter is pressed
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush leftover newline

    // ====== NAME ======
    cout << "\nEnter new name (press Enter to skip): ";
    string newName;
    getline(cin, newName);

    if (!newName.empty()) {
        patient->setName(newName);  // In Person
        cout << "Name updated to: " << newName << endl;
    } else {
        cout << "No changes made to name.\n";
    }

    // ====== GENDER ======
    cout << "Enter new gender [Male/Female/Other] (press Enter to skip): ";
    string newGender;
    getline(cin, newGender);

    if (!newGender.empty()) {
        patient->setGender(newGender);  // In Person (validates "Male","Female","Other")
    } else {
        cout << "No changes made to gender.\n";
    }

    // ====== EMAIL ======
    cout << "Enter new email (press Enter to skip): ";
    string newEmail;
    getline(cin, newEmail);

    if (!newEmail.empty()) {
        patient->setEmail(newEmail);    // In Person (validates '@','.')
    } else {
        cout << "No changes made to email.\n";
    }

    // ====== MOBILE ======
    cout << "Enter new mobile (10 digits) (press Enter to skip): ";
    string newMobile;
    getline(cin, newMobile);

    if (!newMobile.empty()) {
        patient->setMobile(newMobile);  // In Person (validates length=10, all digits)
    } else {
        cout << "No changes made to mobile.\n";
    }

    cout << "\nPatient modification completed.\n";
}


void Administrator::modifyDoctor()
{
    cout << "\n=== Modify Doctor ===" << endl;
    cout << "Enter Doctor ID to modify: ";
    int doctorID;
    cin >> doctorID;

    Doctor* doctor = S->findDoctorByID(doctorID);
    if (!doctor)
    {
        cout << "Doctor with ID " << doctorID << " not found.\n";
        return;
    }

    // Show current details
    cout << "\nCurrent Details:\n";
    cout << "  Name:       " << doctor->getName()   << "\n";
    cout << "  Gender:     " << doctor->getGender() << "\n";
    cout << "  Email:      " << doctor->getEmail()  << "\n";
    cout << "  Mobile:     " << doctor->getMobile() << "\n";
    cout << "  Department: " << doctor->getDepartment() << "\n";

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // ====== NAME ======
    cout << "\nEnter new name (press Enter to skip): ";
    string newName;
    getline(cin, newName);
    if (!newName.empty()) {
        doctor->setName(newName);
    }

    // ====== GENDER ======
    cout << "Enter new gender [Male/Female/Other] (press Enter to skip): ";
    string newGender;
    getline(cin, newGender);
    if (!newGender.empty()) {
        doctor->setGender(newGender);
    }

    // ====== EMAIL ======
    cout << "Enter new email (press Enter to skip): ";
    string newEmail;
    getline(cin, newEmail);
    if (!newEmail.empty()) {
        doctor->setEmail(newEmail);
    }

    // ====== MOBILE ======
    cout << "Enter new mobile (10 digits) (press Enter to skip): ";
    string newMobile;
    getline(cin, newMobile);
    if (!newMobile.empty()) {
        doctor->setMobile(newMobile);
    }

    // ====== DEPARTMENT ======
    cout << "Enter new department (press Enter to skip): ";
    string newDept;
    getline(cin, newDept);
    if (!newDept.empty()) {
        doctor->setDepartment(newDept);
    }

    cout << "\nDoctor modification completed.\n";
}

void Administrator::modifyAdministrator()
{
    cout << "\n=== Modify Administrator ===" << endl;
    cout << "Enter Administrator ID to modify: ";
    int adminID;
    cin >> adminID;

    // We'll assume StaffManager can find administrators by ID:
    Administrator* adminToModify = S->findAdministratorByID(adminID);
    if (!adminToModify)
    {
        cout << "Administrator with ID " << adminID << " not found.\n";
        return;
    }

    // Show current details
    cout << "\nCurrent Details:\n";
    cout << "  Name:   "   << adminToModify->getName()   << "\n";
    cout << "  Gender: "   << adminToModify->getGender() << "\n";
    cout << "  Email:  "   << adminToModify->getEmail()  << "\n";
    cout << "  Mobile: "   << adminToModify->getMobile() << "\n";
    // If there's a special "department" for admins, also show that

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // ====== NAME ======
    cout << "\nEnter new name (press Enter to skip): ";
    string newName;
    getline(cin, newName);
    if (!newName.empty()) {
        adminToModify->setName(newName);
    }

    // ====== GENDER ======
    cout << "Enter new gender [Male/Female/Other] (press Enter to skip): ";
    string newGender;
    getline(cin, newGender);
    if (!newGender.empty()) {
        adminToModify->setGender(newGender);
    }

    // ====== EMAIL ======
    cout << "Enter new email (press Enter to skip): ";
    string newEmail;
    getline(cin, newEmail);
    if (!newEmail.empty()) {
        adminToModify->setEmail(newEmail);
    }

    // ====== MOBILE ======
    cout << "Enter new mobile (10 digits) (press Enter to skip): ";
    string newMobile;
    getline(cin, newMobile);
    if (!newMobile.empty()) {
        adminToModify->setMobile(newMobile);
    }

    cout << "\nAdministrator modification completed.\n";
}

void Administrator::findUser()
{
    cout << "=== Find User ===" << endl;
    cout << "Select user type to find:\n";
    cout << "  1. Patient\n";
    cout << "  2. Doctor\n";
    cout << "  3. Administrator\n";
    cout << "Enter choice: ";
    int choice;
    cin >> choice;

    cout << "Enter ID to search: ";
    int searchID;
    cin >> searchID;

    switch (choice)
    {
    case 1: {
        Patient* pat = P->findPatientByID(searchID);
        if (!pat) {
            cout << "Patient not found.\n";
            return;
        }
        // Display patient details
        cout << "\nPatient found:\n";
        cout << "  ID:   " << pat->getID()   << "\n";
        cout << "  Name: " << pat->getName() << "\n";
        // etc.
        break;
    }
    case 2: {
        // If you have S->findDoctorByID(...)
        Doctor* doc = S->findDoctorByID(searchID);
        if (!doc) {
            cout << "Doctor not found.\n";
            return;
        }
        // Display doctor details
        cout << "\nDoctor found:\n";
        cout << "  ID:   " << doc->getID()   << "\n";
        cout << "  Name: " << doc->getName() << "\n";
        // etc.
        break;
    }
    case 3: {
        // If you have S->findAdministratorByID(...)
        Administrator* adminUser = S->findAdministratorByID(searchID);
        if (!adminUser) {
            cout << "Administrator not found.\n";
            return;
        }
        cout << "\nAdministrator found:\n";
        cout << "  ID:   " << adminUser->getID()   << "\n";
        cout << "  Name: " << adminUser->getName() << "\n";
        // etc.
        break;
    }
    default:
        cout << "Invalid choice.\n";
        break;
    }
}


// View all patients
void Administrator::viewAllPatients() const {
    P->listAllPatients();
}

// View all doctors
void Administrator::viewAllDoctors() const {
    S->listAllDoctors();
}

// View all doctors
void Administrator::viewAllAdministrators() const {
    S->listAllAdministrators();
}

// Destructor
Administrator::~Administrator() {}
