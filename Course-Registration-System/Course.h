#include <string>
#include <vector>
#include <list>
#include <forward_list>

using namespace std;

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
	int creditHours;

public:
	Course(string ID, string title, string syllabus, forward_list<Course> prerequisite, int creditHours, forward_list<Instructor> instructors);
	Course();
	void setID(string);
	string getID();
	string getTitle();
	void setTitle(string title);
	string getSyllabus();
	void setSyllabus(string syllabus);
	forward_list<Course> getPrerequisite();
	forward_list<Instructor> getInstructors();
	void addPrerequisite(Course course);
	void removePrerequisite(Course course);
	void addInstructor(Instructor instructor);
	void removeInstructor(Instructor instructor);
	int getCreditHours();
	void setCreditHours(int creditHours);
	void displayCourseInfo();
	bool operator==(const Course& other) const;
};
