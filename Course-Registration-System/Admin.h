#pragma once
#include "Person.h"

class Admin : public Person
{
public:
	static int numberOfIDs;
	Admin(string username, string password);
	Admin(const Admin& other);
	Admin();
	void manageGrades();
	void setPrerequisites();
	void uploadCourseDescription();
};