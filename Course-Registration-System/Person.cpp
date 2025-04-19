#include "Person.h"

Person::Person(string username, string password) {
    this->username = username;
    this->password = password;
}

string Person::getUsername() {
    return username;
}

void Person::setUsername(string username) {
    this->username = username;
}

string Person::getPassword() {
    return password;
}

void Person::setPassword(string password) {
    this->password = password;
}
