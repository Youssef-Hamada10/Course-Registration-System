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
	};
};

class Course {
private:
	string ID;
	string title;
	string syllabus;
	vector<Course*> prerequisites;
	vector<Instructor*> instructors;
	Semester semester;
	int creditHours;

public:
	Course(string ID, string title, string syllabus, vector<Course*> prerequisite, int creditHours, vector<Instructor*> instructors, Semester semester);
	Course(const Course& course);
	Course();
	string getID();
	void setID(string ID);
	string getTitle();
	void setTitle(string title);
	string getSyllabus();
	void setSyllabus(string syllabus);
	vector<Course*> getPrerequisite();
	void addPrerequisite(Course* course);
	void removePrerequisite(Course course);
	void addInstructor(Instructor* instructor);
	void removeInstructor(Instructor instructor);
	int getCreditHours();
	void setCreditHours(int creditHours);
	Semester getSemester();
	void setSemester(Semester semester);
	vector<Instructor*> getInstructors();
	void displayCourseInfo();
	bool operator==(const Course& other) const;
	~Course();
};