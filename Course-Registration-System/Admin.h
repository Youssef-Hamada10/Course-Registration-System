#pragma once
#include "Person.h"
#include "Student.h"
#include "Course.h"

class Admin : public Person
{
public:
	static int numberOfIDs;
	Admin(string username, string password);
	Admin(const Admin& other);
	Admin();
	void manageGrades();
	void menu(map<string, Student>& students, unordered_map<string, Course>& courses);
	void setPrerequisites(string courseID, vector<string> prerequisiteIDs, unordered_map<string, Course>& courses);
	void uploadCourseDescription(string courseID, string description, unordered_map<string, Course>& courses);
	void manageStudents(map<string, Student> students);
	void manageCourses(unordered_map<string, Course> courses);
};