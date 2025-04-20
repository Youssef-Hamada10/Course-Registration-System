#include <string>
#include <vector>
#include <list>
#include <forward_list>

using namespace std;

struct Instructor {
	string courseID;  //recently added
	string id;
	string name;
	string department;
	bool operator==(const Instructor& other) const {
		return id == other.id;
	}
};

class Course {
private:
	string id;
	string title;
	string syllabus;
	//int numOfPrerequisite;   //recently added
	forward_list<Course> prerequisites;
	//int numOfInstructor;   //recently added
	forward_list<Instructor> instructors;
	int creditHours;

public:
	Course(string id, string title, string syllabus, forward_list<Course> prerequisite, int creditHours, forward_list<Instructor> instructors);
	Course();     //recently added
	void setID(string); //recently added
	string getID();  //recently added
	string getTitle();
	void setTitle(string title);
	string getSyllabus();
	void setSyllabus(string syllabus);
	//void setNumOfPrerequisite(int);  //recently added
	//int getNumOfPrerequisite();   //recently added
	forward_list<Course> getPrerequisite();
	//void setNumOfInstructor(int);  //recently added
	//int getNumOfInstructor();   //recently added
	forward_list<Instructor> getInstructors(); //recently added
	void addPrerequisite(Course course);
	void removePrerequisite(Course course);
	void addInstructor(Instructor instructor);
	void removeInstructor(Instructor instructor);
	int getCreditHours();
	void setCreditHours(int creditHours);
	void displayCourseInfo();
	bool operator==(const Course& other) const;
};
