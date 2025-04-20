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

Student::Student() {
	// default constructor
}

string Student::getName() {  //recently added
    return name;
}

string Student::getId() {
	return id;
}

void Student::setID(string ID){   //was added
	this->id = ID;
}

string Student::getNationalId() {
	return nationalId;
}

void Student::setNationalID(string nationalID) {  //was added
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

void Student::setNationality(string nationality) {   //was added
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

void Student::searchForCourses(vector<Course> Courses) {
}

void Student::registerCourse(Course course) {  // was edited
	this->registeredCourses.push(course);
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
