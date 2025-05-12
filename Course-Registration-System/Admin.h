#pragma once
#include "Person.h"
#include "Student.h"
#include "Course.h"
#include <queue>

class Admin : public Person
{
public:
	static int numberOfIDs;
	static Semester currentSemester;
	Admin(string username, string password);
	Admin(const Admin& other);
	Admin();
	bool isValidGrade(string grade);
	void editStudentInfo(map<string, Student>& students);
	void editStudentGrades(map<string, Student>& students);
	void addCourse(unordered_map<string, Course>& courses);
	void editCourse(unordered_map<string, Course>& courses);
	void manageInstructors();
	void manageGrades();
	void manualUpload(map<string, Student>& students);
	void fileUpload(map<string, Student>& students);
	void uploadGrades(map<string, Student>& students);
	void manageCoursePrerequisites(unordered_map<string, Course>& courses);
	void menu(map<string, Student>& students, unordered_map<string, Course>& courses, unordered_map<string, Instructor>& instructors);
	void setPrerequisites(string courseID, vector<string> prerequisiteIDs, unordered_map<string, Course>& courses);
	void uploadCourseDescription(string courseID, string description, unordered_map<string, Course>& courses);
	void manageStudents(map<string, Student>& students);
	void manageCourses(unordered_map<string, Course>& courses);
	queue<string> split(string line, char ch);
};