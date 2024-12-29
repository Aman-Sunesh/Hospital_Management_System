#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <limits>
#include <cstdlib>

#include "Administrator.h"   // Must include if we use Administrator
#include "StaffManager.h"
#include "PatientManager.h"
#include "PersonManager.h"
#include "Utility.h"

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    // Prepare managers
    PersonManager* personManager   = new PersonManager();
    StaffManager* staffManager    = new StaffManager();
    PatientManager* patientManager = new PatientManager();

    
    // Register the default admin
    staffManager->registerDefaultAdministrator(personManager, "Admin", 123456, "abcdefgh");

    do {
        cout << "\n--------------------------------------------------\n";
        cout << "|         HOSPITAL MANAGEMENT SYSTEM            |\n";
        cout << "| 1. Login                                      |\n";
        cout << "| 2. Exit                                       |\n";
        cout << "--------------------------------------------------\n";

        int choice;
        cout << "Enter your choice (1-2): ";
        cin >> choice;
        if(!cin || (choice < 1 || choice > 2))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice!\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        clearScreen();

        switch(choice)
        {
            case 1:
            {
                // Attempt login
                Person* loggedInUser = personManager->login();
                if(loggedInUser)
                {
                    string role = loggedInUser->getRole();
                    if(role == "Administrator")
                    {
                        // So admin can manage staff/patient
                        Administrator* adminUser = dynamic_cast<Administrator*>(loggedInUser);

                        if (!adminUser) {
                            cout << "Error: Failed to cast logged-in user to Administrator.\n";
                            break;
                        }

                        adminUser->setStaffManager(staffManager);
                        adminUser->setPatientManager(patientManager);
                        adminUser->setPersonManager(personManager);
                        
                        adminUser->displayMenu();
                    }
                    else if(role == "Doctor")
                    {
                        Doctor* doctorUser = dynamic_cast<Doctor*>(loggedInUser);
                        doctorUser->displayMenu(patientManager);
                    }
                    else if(role == "Patient")
                    {
                        Patient* patientUser = dynamic_cast<Patient*>(loggedInUser);
                        patientUser->displayMenu(staffManager);
                    }
                    else
                    {
                        cout << "Unknown role, cannot proceed.\n";
                    }
                }
                break;
            }
            case 2:
            {
                cout << "Exiting...\n";
                // Cleanup
                delete personManager;
                delete staffManager;
                delete patientManager;
                return 0;
            }
        }
    } while(true);

    // Cleanup (unreachable in this loop, but good practice)
    delete personManager;
    delete staffManager;
    delete patientManager;
    return 0;
}
