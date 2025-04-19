#include "Person.h"
#include "Course.h"
#include <stack>

class Student : public Person
{
private:
	string id;
	string name;
	string nationalId;
	string telephoneNumber;
	string address;
	string nationality;
	stack<Course> registeredCourses;
	float gpa;
	int level;
	int currentCreditHours;

public:
	Student(string userName, string password, string name, string id, string nationalId, string telephoneNumber, string address, string nationality, float gpa, int level, int currentCreditHours);
	string getId();
	string getNationalId();
	string getTelephoneNumber();
	void setTelephoneNumber(string telephoneNumber);
	string getAddress();
	void setAddress(string address);
	string getNationality();
	float getGpa() const;
	void setGpa(float gpa);
	int getStudyLvl() const;
	void setStudyLvl(int studyLvl);
	int getCurrentCreditHours();
	void setCurrentCreditHours(int currentCreditHours);
	void searchForCourses(vector<Course> Courses);
	void registerCourse();
	void displayInfo();
	void displayGrades();
	void report();
};



