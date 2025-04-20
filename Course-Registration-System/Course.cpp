#include "Course.h"
#include <iostream>

Course::Course(string id, string title, string syllabus, forward_list<Course> prerequisites, int creditHours, forward_list<Instructor> instructors) {
    this->id = id;
    this->title = title;
    this->syllabus = syllabus;
    this->prerequisites = prerequisites;
    this->creditHours = creditHours;
    this->instructors = instructors;
}

Course::Course() {
    // default constructor
}

void Course::setID(string ID) {
    this->id = ID;
}

string Course::getID() {
    return id;
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

void Course::setNumOfPrerequisite(int num) {    //recently added
    this->numOfPrerequisite = num;
}

int Course::getNumOfPrerequisite() {      //recently added
    return numOfPrerequisite;
}

forward_list<Course> Course::getPrerequisite() {
    return prerequisites;
}

void Course::setNumOfInstructor(int num) {    //recently added
    this->numOfInstructor = num;
}

int Course::getNumOfInstructor() {    //recently added
    return numOfInstructor;
}

forward_list<Instructor> Course::getInstructors() {  //recently added
    return instructors;
}

void Course::addPrerequisite(Course course) {
    prerequisites.push_front(course);
}

void Course::removePrerequisite(Course course) {
    prerequisites.remove(course);
}

void Course::addInstructor(Instructor instructor) {
    instructors.push_front(instructor);
}

void Course::removeInstructor(Instructor instructor) {
    instructors.remove(instructor);
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
    return this->id == other.id;
}
