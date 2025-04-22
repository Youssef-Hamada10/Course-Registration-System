#include "Person.h"
#include "Course.h"
#include <map>
#include <deque>

class Student : public Person
{
private:
	string id;
	string name;
	string nationalId;
	string telephoneNumber;
	string address;
	string nationality;
	deque<Course> registeredCourses;
	float gpa;
	int level;
	int currentCreditHours;

public:
	Student(string userName, string password, string name, string id, string nationalId, string telephoneNumber, string address, string nationality, float gpa, int level, int currentCreditHours);
	Student(const Student& student);
	Student();
	string getId();
	void setId(string id);
	string getName();
	void setName(string name);
	string getNationalId();
	void setNationalId(string nationalId);
	string getNationality();
	void setNationality(string nationality);
	string getTelephoneNumber();
	void setTelephoneNumber(string telephoneNumber);
	string getAddress();
	void setAddress(string address);
	float getGpa() const;
	void setGpa(float gpa);
	int getStudyLvl() const;
	void setStudyLvl(int studyLvl);
	int getCurrentCreditHours();
	deque<Course>* getRegisteredCourses();
	void setCurrentCreditHours(int currentCreditHours);
	void searchForCourses(map<string, Course> Courses);
	void registerCourse(Course course);
	void displayInfo();
	void displayGrades();
	void report();
};
