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

Course::Course(const Course& course) {
    this->ID = course.ID;
    this->title = course.title;
    this->syllabus = course.syllabus;
    this->prerequisites = course.prerequisites;
    this->creditHours = course.creditHours;
    this->instructors = course.instructors;
    this->semester = course.semester;
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

void Course::removePrerequisite(Course course) {
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

void Course::removeInstructor(Instructor instructor) {
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

vector<Instructor*> Course::getInstructors() {
    return instructors;
}

void Course::displayCourseInfo() {
    cout << "Course ID: " << this->ID << endl;
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

Course::~Course() {
    for (auto& it : this->instructors) {
        if (!it) {
            delete it;
        }
    }
}

