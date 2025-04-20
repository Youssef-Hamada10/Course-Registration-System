#include "Student.h"

Student::Student(string username, string password, string name, string id, string nationalId, string telephoneNumber, string address, string nationality, float gpa, int level, int currentCreditHours):Person(username, password) {
	this->id = id;
	this->name = name;
	this->nationalId = nationalId;
	this->telephoneNumber = telephoneNumber;
	this->address = address;
	this->nationality = nationality;
	this->gpa = gpa;
	this->level = level;
	this->currentCreditHours = currentCreditHours;
}

string Student::getName() {  //recently added
    return name;
}

string Student::getId() {
	return id;
}

string Student::getNationalId() {
	return nationalId;
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

void Student::searchForCourses(vector<Course> Courses) {
}

void Student::registerCourse() {
}

void Student::displayInfo() {
}

void Student::displayGrades() {
}

void Student::report() {
}

stack<Course> Student::getRegisteredCourses() {
    return registeredCourses;
}
