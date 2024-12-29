#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>

using namespace std;

class Entity
{
    protected:
        string name;
        int ID;
        string type;

    public:
        // Constructors
        Entity() = default; // Default constructor
        Entity(const string& name, int ID, const string& type);

        // Virtual destructor to support polymorphic deletion
        virtual ~Entity() = default;

        // Member functions
        void setType(const string& newType);

};

#endif // ENTITY_H