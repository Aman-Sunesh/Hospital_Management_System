#ifndef PERSONMANAGER_H
#define PERSONMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include "Entity.h"
#include "Person.h"


using namespace std;

class PersonManager {
private:
    vector<Person*> personList;

public:
    PersonManager() = default;
    ~PersonManager();
    
    void registerPerson(Person* person);
    Person* login();  // Calls the login function and handles user redirection
    vector<Person*>& getPersonList();
    void addPerson(Person* person);
};

#endif // PERSONMANAGER_H