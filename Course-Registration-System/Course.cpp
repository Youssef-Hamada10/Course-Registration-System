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

Course::Course(const Course& course)
{
    this->id = course.id;
    this->title = course.title;
    this->syllabus = course.syllabus;
    this->prerequisites = course.prerequisites;
    this->creditHours = course.creditHours;
    this->instructors = course.instructors;
}

Course::Course() {
    creditHours = 0;
}

string Course::getId() {
    return id;
}

void Course::setId(string id) {
    this->id = id;
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

forward_list<Instructor> Course::getInstructors()
{
    return instructors;
}

void Course::displayCourseInfo() {

}

bool Course::operator==(const Course& other) const {
    return this->id == other.id;
}

