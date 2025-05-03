#pragma once
#include "Person.h"
#include "Course.h"
#include <deque>
#include <map>
#include <unordered_map>

class Student : public Person {
private:
	string name;
	string nationalID;
	string telephoneNumber;
	string address;
	string nationality;
	deque<pair<Course, string>> registeredCourses;
	float gpa;
	int level;
	int totalCreditHours;
	int currentCreditHours;

public:
	Student(string ID, string userName, string password, string name, string nationalID, string telephoneNumber, string address, string nationality, float gpa, int level, int currentCreditHours);
	Student(const Student& other);
	Student();
	string getName();
	void setName(string name);
	string getNationalID();
	void setNationalID(string);
	string getTelephoneNumber();
	void setTelephoneNumber(string telephoneNumber);
	string getAddress();
	void setAddress(string address);
	string getNationality();
	void setNationality(string);
	float getGpa();
	void setGpa(float gpa);
	int getStudyLvl();
	void setStudyLvl(int studyLvl);
	int getCurrentCreditHours();
	void setCurrentCreditHours(int currentCreditHours);
	int getTotalCreditHours() const;
	void setTotatlCreditHours(int totalCreditHours);
	void registerCourse(map<string, Course> courses);
	void addCourseInFiles(pair<Course, string> course);
	void displayInfo();
	void displayGrades();
	void displayPrerequisite(map<string, Course> courses);
	void searchCourse(map<string, Course> courses);
	void report();
	void menu(map<string, Course> courses);
	void updateGPA();
	deque<pair<Course, string>> getRegisteredCourses();
};