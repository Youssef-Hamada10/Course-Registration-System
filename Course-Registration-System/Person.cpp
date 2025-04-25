#include "Person.h"

Person::Person(string ID, string username, string password)
{
    this->ID = ID;
    this->username = username;
    this->password = password;
}

Person::Person() {
}

string Person::getID() {
    return ID;
}

void Person::setID(string ID) {
    this->ID = ID;
}

string Person::getUsername()
{
    return username;
}

void Person::setUsername(string username)
{
    this->username = username;
}

string Person::getPassword()
{
    return password;
}

void Person::setPassword(string password)
{
    this->password = password;
}
