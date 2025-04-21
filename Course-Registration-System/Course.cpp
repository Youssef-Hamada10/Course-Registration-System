#include "Course.h"
#include <iostream>

Course::Course(string ID, string title, string syllabus, forward_list<Course> prerequisites, int creditHours, forward_list<Instructor> instructors) {
    this->ID = ID;
    this->title = title;
    this->syllabus = syllabus;
    this->prerequisites = prerequisites;
    this->creditHours = creditHours;
    this->instructors = instructors;
    //this->numOfInstructor = 0; // was added
    //this->numOfPrerequisite = 0; // was added
}

Course::Course() {
    // default constructor
}

void Course::setID(string ID) {
    this->ID = ID;
}

string Course::getID() {
    return ID;
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

//void Course::setNumOfPrerequisite(int num) {
//    this->numOfPrerequisite = num;
//}
//
//int Course::getNumOfPrerequisite() {
//    return numOfPrerequisite;
//}

forward_list<Course> Course::getPrerequisite() {
    return prerequisites;
}

//void Course::setNumOfInstructor(int num) {
//    this->numOfInstructor = num;
//}
//
//int Course::getNumOfInstructor() {
//    return numOfInstructor;
//}

forward_list<Instructor> Course::getInstructors() {
    return instructors;
}

void Course::addPrerequisite(Course course) {
    prerequisites.push_front(course);
    //numOfPrerequisite++;
}

void Course::removePrerequisite(Course course) {
    prerequisites.remove(course);
    //numOfPrerequisite--;
}

void Course::addInstructor(Instructor instructor) {
    instructors.push_front(instructor);
    //numOfInstructor++;
}

void Course::removeInstructor(Instructor instructor) {
    instructors.remove(instructor);
    //numOfInstructor--;
}

int Course::getCreditHours() {
    return creditHours;
}

void Course::setCreditHours(int creditHours) {
    this->creditHours = creditHours;
}

void Course::displayCourseInfo() {

}

bool Course::operator==(const Course& other) const {
    return this->ID == other.ID;
}
