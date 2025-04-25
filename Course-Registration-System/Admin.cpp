#include "Admin.h"

int Admin::numberOfIDs = 0;

Admin::Admin(string username, string password) {
	this->ID = to_string(++numberOfIDs);
	this->username = username;
	this->password = password;
}

Admin::Admin(const Admin& other) {
	this->ID = other.ID;
	this->username = other.username;
	this->password = other.password;
}

Admin::Admin() {
	this->ID = to_string(numberOfIDs);
}

void Admin::manageGrades() {
}

void Admin::setPrerequisites() {
}

void Admin::uploadCourseDescription() {
}
