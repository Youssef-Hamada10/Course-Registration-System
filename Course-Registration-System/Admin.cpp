#pragma once
#include <iostream>
#include "Admin.h"
#include <vector>
#include "Handleable.h"

using namespace std;

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

void Admin::manageStudents(map<string, Student> students) { // to do
}

void Admin::manageCourses(unordered_map<string, Course> courses) {
}

void Admin::menu(map<string, Student>& students, unordered_map<string, Course>& courses) {
    int choice = 0;

    while (true) {
        system("cls");
        cout << "Welcome " << username << endl;
        cout << "_______________________\n\n";
        cout << "1 : Manage Students\n2 : Manage Courses\n3 : Log Out\n\n\nYour Choice: ";
        choice = Handleable::handlingChoiceNotFound(7);
        cin.ignore();
        switch (choice) {
        case 1:
            manageStudents(students);
            break;
        case 2:
            manageCourses(courses);
            break;
        case 3:
            return;
        default:
            break;
        }
    }
}

void Admin::manageGrades() { // to do
   // unordered_set<string> grades = {} // assign grades here
}

void Admin::setPrerequisites(string courseID, vector<string> prerequisiteIDs, unordered_map<string, Course>& courses) {
    auto courseIt = courses.find(courseID);
    if (courseIt == courses.end()) {
        cout << "Course " << courseID << " not found!" << endl;
        return;
    }

    courseIt->second.getPrerequisite().clear();

    for (const auto& prereqID : prerequisiteIDs) {
        auto prereqIt = courses.find(prereqID);
        if (prereqIt != courses.end()) {
            auto prereqVector = courseIt->second.getPrerequisite();
            auto exists = find_if(prereqVector.begin(), prereqVector.end(),
                [&prereqIt](Course* course) { return course->getID() == prereqIt->second.getID(); });
            if (exists == prereqVector.end()) {
                courseIt->second.addPrerequisite(&prereqIt->second);
            }
        }
        else {
            cout << "Prerequisite course " << prereqID << " not found!" << endl;
        }
    }

    cout << "Prerequisites updated for course " << courseID << endl;
}

void Admin::uploadCourseDescription(string courseID, string description, unordered_map<string, Course>& courses) {
    auto it = courses.find(courseID);
    if (it != courses.end()) {
        // Update the syllabus
        it->second.setSyllabus(description);
        cout << "Syllabus updated for course " << courseID << endl;
    }
    else {
        cout << "Course " << courseID << " not found!" << endl;
    }
}
