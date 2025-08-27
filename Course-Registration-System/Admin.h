#pragma once
#include "Person.h"
#include "Student.h"
#include "Course.h"
#include <queue>

class Admin : public Person
{
public:
	static Semester currentSemester;
	Admin(string username, string password);
	Admin(const Admin& other);
	Admin();

	void menu(map<string, Student>& students, unordered_map<string, Course>& courses, unordered_map<string, Instructor>& instructors);

	void manageStudents(map<string, Student>& students);
	void editStudentInfo(map<string, Student>& students);
	void EditStudentGrades(map<string, Student>& students);
	void manualUpload(map<string, Student>& students);
	void fileUpload(map<string, Student>& students);
	void displayAllStudents(map<string, Student>& students);


	void manageCourses(unordered_map<string, Course>& courses, unordered_map<string, Instructor>& Instructors);
	void addCourse(unordered_map<string, Course>& courses, unordered_map<string, Instructor>& Instructors);
	void editCourse(unordered_map<string, Course>& courses, unordered_map<string, Instructor>& instructors);
	void manageCoursePrerequisites(unordered_map<string, Course>& courses);
	void manageInstructors(unordered_map<string, Course>& courses, unordered_map<string, Instructor>& instructors);
	void addInstructorInCourse(unordered_map<string, Course>& courses, unordered_map<string, Instructor>& instructors);
	void removeInstructorFromCourse(unordered_map<string, Course>& courses, unordered_map<string, Instructor>& instructors);
	void manageCourseMajors(unordered_map<string, Course>& courses);
	void addMajor(unordered_map<string, Course>& courses);
	void removeMajor(unordered_map<string, Course>& courses);


	void addInstructorToSystem(unordered_map<string, Instructor>& instructors);


	void generateCourseReport(map<string, Student>& students, unordered_map<string, Course>& courses);



	bool isValidGrade(string grade);
	queue<string> split(string line, char ch);
};