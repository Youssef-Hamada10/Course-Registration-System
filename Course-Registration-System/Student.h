#include "Person.h"
#include "Course.h"
#include <deque>
#include <map>

class Student : public Person {
private:
	string ID;
	string name;
	string nationalID;
	string telephoneNumber;
	string address;
	string nationality;
	deque<Course> registeredCourses;
	float gpa;
	int level;
	int currentCreditHours;

public:
	Student(string userName, string password, string name, string ID, string nationalID, string telephoneNumber, string address, string nationality, float gpa, int level, int currentCreditHours);
	Student();       
	void setID(string);
	string getID();
	string getName(); 
	void setName(string name);
	string getNationalID();
	void setNationalID(string);  
	string getTelephoneNumber();
	void setTelephoneNumber(string telephoneNumber);
	string getAddress();
	void setAddress(string address);
	string getNationality();
	void setNationality(string);  
	float getGpa() const;
	void setGpa(float gpa);
	int getStudyLvl() const;
	void setStudyLvl(int studyLvl);
	int getCurrentCreditHours();
	void setCurrentCreditHours(int currentCreditHours);
	void searchForCourses(map<string,Course> courses);
	void registerCourse(Course course);
	void registerCourseInFiles(Course);
	void displayInfo();
	void displayGrades();
	void report();
	deque<Course>* getRegisteredCourses1();
	deque<Course> getRegisteredCourses();


};



