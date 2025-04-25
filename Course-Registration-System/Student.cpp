#include "Student.h"
#include <map>

Student::Student(string ID, string username, string password, string name, string nationalID, string telephoneNumber, string address, string nationality, float gpa, int level, int currentCreditHours)
    :Person(ID, username, password) {
    this->name = name;
    this->nationalID = nationalID;
    this->telephoneNumber = telephoneNumber;
    this->address = address;
    this->nationality = nationality;
    this->gpa = gpa;
    this->level = level;
    this->currentCreditHours = currentCreditHours;
}

Student::Student(const Student& other)
    :Person(other.ID, other.username, other.password) {
    this->name = other.name;
    this->nationalID = other.nationalID;
    this->telephoneNumber = other.telephoneNumber;
    this->address = other.address;
    this->nationality = other.nationality;
    this->registeredCourses = other.registeredCourses;
    this->gpa = other.gpa;
    this->level = other.level;
    this->currentCreditHours = other.currentCreditHours;
}

Student::Student() {
    level = 1;
    gpa = 0.0;
    currentCreditHours = 0;
}

string Student::getName() {
    return name;
}

void Student::setName(string name) {
    this->name = name;
}

string Student::getNationalID() {
    return nationalID;
}

void Student::setNationalID(string nationalID) {
    this->nationalID = nationalID;
}

string Student::getTelephoneNumber() {
    return telephoneNumber;
}

void Student::setTelephoneNumber(string telephoneNumber) {
    this->telephoneNumber = telephoneNumber;
}

string Student::getAddress() {
    return address;
}

void Student::setAddress(string address) {
    this->address = address;
}

string Student::getNationality() {
    return nationality;
}

void Student::setNationality(string nationality) {
    this->nationality = nationality;
}

float Student::getGpa() const {
    return gpa;
}

void Student::setGpa(float gpa) {
    this->gpa = gpa;
}

int Student::getStudyLvl() const {
    return level;
}

void Student::setStudyLvl(int level) {
    this->level = level;
}

int Student::getCurrentCreditHours() {
    return currentCreditHours;
}

void Student::setCurrentCreditHours(int currentCreditHours) {
    this->currentCreditHours = currentCreditHours;
}

void Student::searchForCourses(map<string, Course> courses) {
}

void Student::registerCourse(Course course) {
    this->registeredCourses.push_front(course);
}

void Student::registerCourseInFiles(Course course) {
    this->registeredCourses.push_back(course);
}

void Student::displayInfo() {
}

void Student::displayGrades() {
}

void Student::report() {
}

deque<Course> Student::getRegisteredCourses() {
    return registeredCourses;
}

