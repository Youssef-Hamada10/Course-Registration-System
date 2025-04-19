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

forward_list<Course> Course::getPrerequisite() {
    return prerequisites;
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
