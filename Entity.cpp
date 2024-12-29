#include "Entity.h"

using namespace std;

Entity::Entity(const string& name, int ID, const string& type)
{
    this->name = name;
    this->ID = ID;
    this->type = type;
}

void setType(const string& newType)
{
    type = newType;
}