#include "Student.h"
#include <map>

Student::Student(string username, string password, string name, string ID, string nationalID, string telephoneNumber, string address, string nationality, float gpa, int level, int currentCreditHours) :Person(username, password) {
    this->id = ID;
    this->name = name;
    this->nationalId = nationalID;
    this->telephoneNumber = telephoneNumber;
    this->address = address;
    this->nationality = nationality;
    this->gpa = gpa;
    this->level = level;
    this->currentCreditHours = currentCreditHours;
}

Student::Student() {
    // default constructor
}

string Student::getName() {
    return name;
}

void Student::setName(string name) {
    this->name = name;
}

string Student::getId() {
    return id;
}

void Student::setId(string ID) {
    this->id = ID;
}

string Student::getNationalId() {
    return nationalId;
}

void Student::setNationalId(string nationalID) {
    this->nationalId = nationalID;
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

