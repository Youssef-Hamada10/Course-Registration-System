#pragma once
#include <string>
#include <vector>
#include <forward_list>

using namespace std;

enum Semester { Fall = 0, Spring };

struct Instructor {
	string courseID;
	string ID;
	string name;
	string department;

	bool operator==(const Instructor& other) const {
		return ID == other.ID;
	}
};

class Course {
private:
	string ID;
	string title;
	string syllabus;
	forward_list<Course> prerequisites;
	forward_list<Instructor> instructors;
	Semester semester;
	int creditHours;

public:
	Course(string ID, string title, string syllabus, forward_list<Course> prerequisite, int creditHours, forward_list<Instructor> instructors, Semester semester);
	Course(const Course& course);
	Course();
	string getID();
	void setID(string ID);
	string getTitle();
	void setTitle(string title);
	string getSyllabus();
	void setSyllabus(string syllabus);
	forward_list<Course> getPrerequisite();
	void addPrerequisite(Course course);
	void removePrerequisite(Course course);
	void addInstructor(Instructor instructor);
	void removeInstructor(Instructor instructor);
	int getCreditHours();
	void setCreditHours(int creditHours);
	Semester getSemester();
	void setSemester(Semester semester);
	forward_list<Instructor> getInstructors();
	void displayCourseInfo();
	bool operator==(const Course& other) const;
};