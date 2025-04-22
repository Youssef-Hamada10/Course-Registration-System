#include "Student.h"
#include <map>

Student::Student(string username, string password, string name, string id, string nationalId, string telephoneNumber, string address, string nationality, float gpa, int level, int currentCreditHours)
	: Person(username, password) {
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

Student::Student(const Student& student)
	: Person(student.username, student.password) {
	this->id = student.id;
	this->name = student.name;
	this->nationalId = student.nationalId;
	this->telephoneNumber = student.telephoneNumber;
	this->address = student.address;
	this->nationality = student.nationality;
	this->gpa = student.gpa;
	this->level = student.level;
	this->currentCreditHours = student.currentCreditHours;
}

Student::Student()
{
}

string Student::getId()
{
	return id;
}

void Student::setId(string id)
{
	this->id = id;
}

string Student::getName()
{
	return name;
}

void Student::setName(string name)
{
	this->name = name;
}

string Student::getNationalId()
{
	return nationalId;
}

void Student::setNationalId(string nationalId)
{
	this->nationalId = nationalId;
}

string Student::getTelephoneNumber()
{
	return telephoneNumber;
}

void Student::setTelephoneNumber(string telephoneNumber)
{
	this->telephoneNumber = telephoneNumber;
}

string Student::getAddress()
{
	return address;
}

void Student::setAddress(string address)
{
	this->address = address;
}

string Student::getNationality()
{
	return nationality;
}

void Student::setNationality(string nationality)
{
	this->nationality = nationality;
}

float Student::getGpa() const
{
	return gpa;
}

void Student::setGpa(float gpa)
{
	this->gpa = gpa;
}

int Student::getStudyLvl() const
{
	return level;
}

void Student::setStudyLvl(int level)
{
	this->level = level;
}

int Student::getCurrentCreditHours()
{
	return currentCreditHours;
}

deque<Course>* Student::getRegisteredCourses()
{
	return &registeredCourses;
}

void Student::setCurrentCreditHours(int currentCreditHours)
{
	this->currentCreditHours = currentCreditHours;
}

void Student::searchForCourses(map<string, Course> Courses)
{
}

void Student::registerCourse(Course course)
{
	this->registeredCourses.push_front(course);
}

void Student::displayInfo()
{
}

void Student::displayGrades()
{
}

void Student::report()
{
}
