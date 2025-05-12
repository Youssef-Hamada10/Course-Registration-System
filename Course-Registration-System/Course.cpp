#include "Course.h"
#include <iostream>
#include <algorithm>

Course::Course(string ID, string title, string syllabus, vector<Course*> prerequisites, int creditHours, vector<Instructor*> instructors, Semester semester) {
    this->ID = ID;
    this->title = title;
    this->syllabus = syllabus;
    this->prerequisites = prerequisites;
    this->creditHours = creditHours;
    this->instructors = instructors;
    this->semester = semester;
}

Course::Course(const Course& other) {
    this->ID = other.ID;
    this->title = other.title;
    this->syllabus = other.syllabus;
    this->prerequisites = other.prerequisites;
    this->creditHours = other.creditHours;
    this->instructors = other.instructors;
    this->semester = other.semester;
    this->reqMajor = other.reqMajor;
}

Course::Course() {
    creditHours = 0;
    semester = Fall;
}

string Course::getID() {
    return ID;
}

void Course::setID(string ID) {
    this->ID = ID;
}

string Course::getTitle() {
    return title;
}

void Course::setTitle(string title) {
    this->title = title;
}

string Course::getSyllabus() {
    return syllabus;
}

void Course::setSyllabus(string syllabus) {
    this->syllabus = syllabus;
}

vector<Course*> Course::getPrerequisite() {
    return prerequisites;
}

void Course::addPrerequisite(Course* course) {
    prerequisites.push_back(course);
}

void Course::removePrerequisite(Course& course) {
    auto it = find(prerequisites.begin(), prerequisites.end(), &course);
    if (it != prerequisites.end()) {
        prerequisites.erase(it);
    } else {
        cout << "Prerequisite Does Not Exist!\n";
    }
}

void Course::addInstructor(Instructor* instructor) {
    instructors.push_back(instructor);
}

void Course::removeInstructor(Instructor& instructor) {
    auto it = find(instructors.begin(), instructors.end(), &instructor);
    if (it != instructors.end()) {
        instructors.erase(it);
    } else {
        cout << "Instructor Does Not Exist!\n";
    }
}

int Course::getCreditHours() {
    return creditHours;
}

void Course::setCreditHours(int creditHours) {
    this->creditHours = creditHours;
}

Semester Course::getSemester() {
    return semester;
}

void Course::setSemester(Semester semester) {
    this->semester = semester;
}

vector<string> Course::getReqMajors() {
    return reqMajor;
}

void Course::addMajor(string major) {
    reqMajor.push_back(major);
}

void Course::removeMajor(string major) {
    auto it = find(reqMajor.begin(), reqMajor.end(), major);

    if (it != reqMajor.end()) {
        reqMajor.erase(it);
    } else {
        cout << "Major Does Not Exist!\n";
    }
}

vector<Instructor*> Course::getInstructors() {
    return instructors;
}

void Course::displayCourseInfo() {
    system("cls");
    cout << "\nCourse ID: " << this->ID << endl;
    cout << "Course Name: " << this->title << endl;
    cout << "Course Syllabus: " << this->syllabus << endl;
    cout << "Course semester: " << (this->semester ? "Spring" : "Fall") << endl;
    cout << "Required Credit Hours: " << this->creditHours << endl;
    cout << "Instructors: [ ";
    for (auto& it : this->instructors) {
        cout << it->name << " ";
    }
    cout << "]\n";
    cout << "Prerequisites: [ ";
    for (auto& it : this->prerequisites) {
        cout << it->getTitle() << " ";
    }
    cout << "]\n";
}

bool Course::operator==(const Course& other) const {
    return this->ID == other.ID;
}


