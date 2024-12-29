#include "GenerateAccount.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iostream>


using namespace std;

// Initializing member variables
vector<int> GenerateAccount::IDList = {};
vector<string> GenerateAccount::passwordList = {};

// Function to generate a unique 6-digit integer ID
int GenerateAccount::generateUniqueID() {
    string digits = "0123456789";
    string ID;

    do {
        ID.clear();
        // Generate 6 random digits
        for (int i = 0; i < 6; i++) {
            ID += digits[rand() % 10];
        }
    } while (find(IDList.begin(), IDList.end(), stoi(ID)) != IDList.end()); // Check if ID is already in use

    int uniqueID = stoi(ID); // Convert string to integer
    IDList.push_back(uniqueID); // Add ID to the IDList vector
    return uniqueID; // Return the generated ID
}

// Function to generate a unique password
string GenerateAccount::generatePassword() {
    string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*";
    string password;
    const int passwordLength = 8;

    do {
        password.clear();

        // Generate password by randomly selecting characters from chars string
        for (int i = 0; i < passwordLength; i++) {
            password += chars[rand() % chars.size()];
        }
    } while (find(passwordList.begin(), passwordList.end(), password) != passwordList.end()); // Check if password is already in use

    passwordList.push_back(password); // Add password to the passwordList vector
    return password; // Return generated password
}