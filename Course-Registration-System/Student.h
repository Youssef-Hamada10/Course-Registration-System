#include "Person.h"
#include "Course.h"
#include <stack>
#include <map>

class Student : public Person {
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
	Student();       
	void setID(string); //was added
	string getId();
	string getName(); //was added
	void setName(string name);
	string getNationalId();
	void setNationalID(string);  //was added
	string getTelephoneNumber();
	void setTelephoneNumber(string telephoneNumber);
	string getAddress();
	void setAddress(string address);
	string getNationality();
	void setNationality(string);  //was added
	float getGpa() const;
	void setGpa(float gpa);
	int getStudyLvl() const;
	void setStudyLvl(int studyLvl);
	int getCurrentCreditHours();
	void setCurrentCreditHours(int currentCreditHours);
	void searchForCourses(map<string,Course> courses);
	void registerCourse(Course course);   // was edited
	void displayInfo();
	void displayGrades();
	void report();
	stack<Course> getRegisteredCourses();

};



