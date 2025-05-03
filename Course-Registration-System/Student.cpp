#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include "Student.h"
#include "Handleable.h"

using namespace std;

Student::Student(string ID, string username, string password, string name, string nationalID, string telephoneNumber, string address, string nationality, float gpa, int level, int currentCreditHours)
    :Person(ID, username, password) {
    this->name = name;
    this->nationalID = nationalID;
    this->telephoneNumber = telephoneNumber;
    this->address = address;
    this->nationality = nationality;
    this->gpa = gpa;
    this->level = level;
    this->currentCreditHours = currentCreditHours;
    this->totalCreditHours = 0;
}

Student::Student(const Student& other)
    :Person(other.ID, other.username, other.password) {
    this->name = other.name;
    this->nationalID = other.nationalID;
    this->telephoneNumber = other.telephoneNumber;
    this->address = other.address;
    this->nationality = other.nationality;
    this->registeredCourses = other.registeredCourses;
    this->gpa = other.gpa;
    this->level = other.level;
    this->currentCreditHours = other.currentCreditHours;
    this->totalCreditHours = other.totalCreditHours;
}

Student::Student() {
    level = 1;
    gpa = 0.0;
    currentCreditHours = 0;
    totalCreditHours = 0;
}

string Student::getName() {
    return name;
}

void Student::setName(string name) {
    this->name = name;
}

string Student::getNationalID() {
    return nationalID;
}

void Student::setNationalID(string nationalID) {
    this->nationalID = nationalID;
}

string Student::getTelephoneNumber() {
    return telephoneNumber;
}

void Student::setTelephoneNumber(string telephoneNumber) {
    this->telephoneNumber = telephoneNumber;
}

string Student::getAddress() {
    return address;
}

void Student::setAddress(string address) {
    this->address = address;
}

string Student::getNationality() {
    return nationality;
}

void Student::setNationality(string nationality) {
    this->nationality = nationality;
}

float Student::getGpa() {
    return gpa;
}

void Student::setGpa(float gpa) {
    this->gpa = gpa;
}

int Student::getStudyLvl() {
    return level;
}

void Student::setStudyLvl(int level) {
    this->level = level;
}

int Student::getCurrentCreditHours() {
    return currentCreditHours;
}

void Student::setCurrentCreditHours(int currentCreditHours) {
    this->currentCreditHours = currentCreditHours;
}

int Student::getTotalCreditHours() const {
    return totalCreditHours;
}

void Student::setTotatlCreditHours(int totalCreditHours) {
    this->totalCreditHours = totalCreditHours;
}

void Student::registerCourse(map<string, Course> course) {

}

void Student::addCourseInFiles(pair<Course, string> course) {
    this->registeredCourses.push_back(course);
}

void Student::displayInfo() {
    cout << "Personal Information:\n============================================================================\n";
    cout << "Name: " << left << setw(37) << name << "ID: " << ID << endl;
    cout << "Username: " << left << setw(33) << username << "Password: " << password << endl;
    cout << "National ID: " << left << setw(30) << nationalID << "Telephone Number: " << telephoneNumber << endl;
    cout << "Address: " << left << setw(34) << address << "Nationality: " << nationality << endl;
    cout << "Level: " << left << setw(36) << level << "Total Credit Hours: " << totalCreditHours << endl;
    cout << "===========================================================================\n";
    updateGPA();
}

void Student::displayGrades() {
    if (registeredCourses.empty()) {
        cout << "No Grades To View\n";
        return;
    }

    deque<pair<Course, string>> courses = registeredCourses;

    cout << left << setw(10) << "ID" << setw(40) << "Course Title" << setw(12) << "Semester" << setw(5) << "Grade\n";
    cout << "=====================================================================" << endl;
    while (!courses.empty()) {
        cout << left << setw(10) << courses.front().first.getID() << setw(40) << courses.front().first.getTitle() << setw(12) << (courses.front().first.getSemester() ? "Spring" : "Fall") << setw(5) << courses.front().second << endl;
        courses.pop_front();
    }
    cout << "=====================================================================" << endl;
}

void Student::displayPrerequisite(map<string, Course> courses) {
}

void Student::searchCourse(map<string, Course> courses) {
    string id = "";

    cout << "Enter Course ID: ";
    id = Handleable::emptyString([&]() -> string { getline(cin, id); return id; }(), "ID" );

    auto course = courses.find(id);

    if (course != courses.end()) {
        cout << "Course Has Been Found!\n";
        course->second.displayCourseInfo();
    } else {
        cout << "Course Does Not Exist\n";
    }
}

void Student::report() {
}

void Student::menu(map<string, Course> courses) {
    int choice;
    cout << "Welcome " << name << endl;

    while (true) {
        cout << "1 : To Display Info.\n2 : To Register Course.\n3 : To View Your Grades.\n4 : To Check Prerequisites For A Course.\n5 : Search For A Course.\n6 : Make A Report.\n7 : Log Out\n";
        choice = Handleable::handlingChoiceNotFound(7);
        cin.ignore();
        switch (choice) {
        case 1:
            displayInfo();
            break;
        case 2:
            registerCourse(courses);
            break;
        case 3:
            displayGrades();
            break;
        case 4:
            displayPrerequisite(courses);
            break;
        case 5:
            searchCourse(courses);
            break;
        case 6:
            report();
            break;
        case 7:
            return;
        default:
            break;
        }
    }
}

void Student::updateGPA() {
    if (registeredCourses.empty()) {
        return;
    }

    float gpa = 0.0f;
    unordered_map<string, float>::iterator it;
    unordered_map<string, float> grade = {
        {"A+", 4.0f}, {"A", 4.0f}, {"A-", 3.7f}, {"B+", 3.3f}, {"B", 3.0f},
        {"B-", 2.7f}, {"C+", 2.3f}, {"C", 2.0f}, {"C-", 1.7f}, {"D+", 1.4f},
        {"D", 1.0f}, {"D-", 0.7f}, {"F", 0.0f}
    };

    
    for (auto iter = registeredCourses.begin(); iter != registeredCourses.end(); ++iter) {
        it = grade.find(iter->second);
        if (it != grade.end()) {
            gpa += it->second;
        }
    }
    this->gpa = round(gpa / registeredCourses.size() * 100.0) / 100.0f;
}

deque<pair<Course, string>> Student::getRegisteredCourses() {
    return registeredCourses;
}