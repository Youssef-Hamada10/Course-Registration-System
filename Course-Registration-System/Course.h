#pragma once
#include <string>
#include <vector>

using namespace std;

enum Semester { Fall = 0, Spring };

struct Instructor {
	string ID;
	string name;
	string department;
	vector<string> courseIDs;  // Assigned Courses

	bool operator==(const Instructor& other) const {
		return ID == other.ID;
	};

};
class Course {
private:
	string ID;
	string title;
	string syllabus;
	Semester semester;
	vector<string> reqMajor;
	vector<const Course*> prerequisites;
	vector<Instructor*> instructors;
	int creditHours;

public:
	Course(string ID, string title, string syllabus, int creditHours, Semester semester);
	Course(const Course& other);
	Course();
	string getID()const;
	void setID(string ID);
	string getTitle() const;
	void setTitle(string title);
	string getSyllabus();
	void setSyllabus(string syllabus);
	vector<const Course*> getPrerequisite() const;
	void addPrerequisite(Course* course);
	void removePrerequisite(Course& course);
	void addInstructor(Instructor* instructor);
	void removeInstructor(Instructor& instructor);
	int getCreditHours() const;
	void setCreditHours(int creditHours);
	Semester getSemester() const;
	void setSemester(Semester semester);
	vector<string> getReqMajors() const;
	void addMajor(string Major);
	void removeMajor(string major);
	vector<Instructor*> getInstructors() const;
	void displayCourseInfo() const;
	bool operator==(const Course& other) const;
};