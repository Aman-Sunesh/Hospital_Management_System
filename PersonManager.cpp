#include "PersonManager.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "Utility.h"

using namespace std;

Person* PersonManager::login()
{
    cout << "Enter your ID: ";
    int id;
    cin >> id;

    // Clear the input buffer to avoid issues with subsequent inputs
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string pass;
    char ch;

    cout << "Enter Password: ";
    ch = getch();

    // Masking the password input
    while (ch != '\n')
    {
        pass.push_back(ch);
        cout << '*';
        ch = getch();
    }

    // Clear screen using clearScreen() function
    clearScreen();

    // Display loading message
    cout << "\n\n\n\t\t\t\t\tLOADING \n\t\t\t\t\t";
    for (int i = 1; i < 8; i++)
    {
        this_thread::sleep_for(chrono::milliseconds(375));
        cout << "...";
        cout.flush(); // Flush the output to ensure it is displayed immediately
    }

    // Search for the user in the personList
    for (auto* p : personList)
    {
        if (p->getID() == id && p->getPassword() == pass)
        {
            cout << "\n\n\n\t\t\t\t\tAccess Granted!! \n\n\n";

            // Pause using cin.get()
            cout << "Press Enter to continue...";
            cin.get();

            // Clear screen using clearScreen() function
            clearScreen();

            cout << "Login successful. Welcome, " << p->getName() << "!" << endl;
            return p;
        }
    }

    cout << "\nAccess Aborted...\n";
    cout << endl;

    // Pause using cin.get()
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();

    // Clear screen using clearScreen() function
    clearScreen();

    cout << "Invalid credentials." << endl;
    return nullptr;
}


void PersonManager::registerPerson(Person* person) {
    if (person) {
        personList.push_back(person);
        cout << "Registration successful for: " << person->getName() << endl;
    } else {
        cout << "Registration failed. Invalid person object." << endl;
        return;
    }
}

void PersonManager::addPerson(Person* person)
{
    personList.push_back(person);
}

PersonManager::~PersonManager() {
}
