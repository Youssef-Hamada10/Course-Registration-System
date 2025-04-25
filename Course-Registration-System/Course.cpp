#include "Course.h"
#include <iostream>

Course::Course(string ID, string title, string syllabus, forward_list<Course> prerequisites, int creditHours, forward_list<Instructor> instructors, Semester semester) {
    this->ID = ID;
    this->title = title;
    this->syllabus = syllabus;
    this->prerequisites = prerequisites;
    this->creditHours = creditHours;
    this->instructors = instructors;
    this->semester = semester;
}

Course::Course(const Course& course)
{
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

Semester Course::getSemester() {
    return semester;
}

void Course::setSemester(Semester semester) {
    this->semester = semester;
}

forward_list<Instructor> Course::getInstructors() {
    return instructors;
}

void Course::displayCourseInfo() {

}

bool Course::operator==(const Course& other) const {
    return this->ID == other.ID;
}

