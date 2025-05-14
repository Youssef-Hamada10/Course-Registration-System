#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <conio.h>
#include "Handleable.h"
#include "Admin.h"

using namespace std;

int Admin::numberOfIDs = 0;
Semester Admin::currentSemester = Fall;

unordered_set<string> grades = {
    "A+", "A", "A-",
    "B+", "B", "B-",
    "C+", "C", "C-",
    "D+", "D", "F"
};

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

bool Admin::isValidGrade(string grade) {
    return grades.find(grade) != grades.end();
}

void Admin::editStudentInfo(map<string, Student>& students) {
}

void Admin::editStudentGrades(map<string, Student>& students) {
}

void Admin::addCourse(unordered_map<string, Course>& courses) {
}

void Admin::editCourse(unordered_map<string, Course>& courses) {
}

void Admin::manageInstructors() {
}

void Admin::manageStudents(map<string, Student>& students) {
    int choice = 0;
    
    while (true) {
        cout << "1 : Edit a Student's Personal Info\n2 : Edit Student Grades.\n3 : Upload Students Grades.\n4 : Back.\n\nChoice: ";
        choice = Handleable::handlingChoiceNotFound(4);

        cin.ignore();
        switch (choice) {
        case 1:
            editStudentInfo(students);
            break;
        case 2:
            editStudentGrades(students);
            break;
        case 3:
            uploadGrades(students);
            break;
        case 4:
            return;
        default:
            break;
        }
    }
}

void Admin::manageCourses(unordered_map<string, Course>& courses) {
    int choice = 0;

    while (true) {
        system("cls");
        cout << "1 : Add New Course.\n2 : Edit a Course.\n3 : Manage Prerequisites.\n4 : Manage Instructors.\n5 : Back.\n\nChoice: ";
        choice = Handleable::handlingChoiceNotFound(5);

        switch (choice) {
        case 1:
            addCourse(courses);
            break;
        case 2:
            editCourse(courses);
            break;
        case 3:
            manageCoursePrerequisites(courses);
            break;
        case 4:
            manageInstructors();
            break;
        case 5:
            return;
        default:
            break;
        }
    }
}

void Admin::menu(map<string, Student>& students, unordered_map<string, Course>& courses, unordered_map<string, Instructor>& instructors) {
    int choice = 0;

    while (true) {
        system("cls");
        cout << "Welcome " << username << endl;
        cout << "_______________________\n\n";
        cout << "1 : Manage Students\n2 : Manage Courses\n3 : Log Out\n\n\nYour Choice: ";
        choice = Handleable::handlingChoiceNotFound(3);
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

void Admin::manageGrades() {
}

void Admin::manualUpload(map<string, Student>& students) {
    string ID;
    cout << "Enter Student ID: ";
    auto read = [](string ID) -> string {
        getline(cin, ID);
        return ID;
    };
    ID = Handleable::emptyString(read(ID), "Student ID");

    map<string, Student>::iterator student = students.find(ID);
    if (student == students.end()) {
        cout << "Student Does Not Exist!\nPress Any Key To Try Again: ";
        _getch();
        return;
    }

    auto& regCourses = student->second.getRegisteredCourses();
    auto isValidCourse = [&ID](const pair<const Course*, string>& course) {
        return course.first->getID() == ID;
    };

    vector<pair<const Course*, string>>::iterator courseIt;
    cout << "Student's Data:\nName: " << student->second.getName() << "\nUsername: " << student->second.getUsername() << "\nTelephone Number: " << student->second.getTelephoneNumber() << endl;
    cout << "\nEnrolled Courses: \n";
    student->second.displayGrades();
    //for (; courseIt != student->second.getRegisteredCourses().end(); ++courseIt) {
    //    if (courseIt->first->getID() == ID) {
    //        break;
    //    }
    //}
    do {
        cout << "\nEnter Course ID To Change Its Grade: ";
        ID = Handleable::emptyString(read(ID), "Course ID");
        courseIt = find_if(regCourses.begin(), regCourses.end(), isValidCourse);
        if (courseIt == regCourses.end()) {
            cout << "Course Does Not Exist!\nPress Any Key To Try Again: ";
            _getch();
        }
    } while (courseIt == regCourses.end());

    string grade;
    cout << "Course's been Found!\nCourse Name: " << courseIt->first->getTitle() << "\nCourse ID: " << courseIt->first->getID() << "\nGrade: " << courseIt->second;
    cout << "\n\nEnter The New Grade: ";
    grade = Handleable::emptyString(read(grade), "Course grade");

    while (!isValidGrade(grade)) {
        cout << "Enter Valid Course Grade: ";
        grade = Handleable::emptyString(read(grade), "Course Grade");
    }

    cout << "Are You Sure You Want To Change " << courseIt->first->getTitle() << " Grade From " << courseIt->second << " To " << grade << " ? (Y || N): ";
    if (Handleable::toContinue()) {
        courseIt->second = grade;
        student->second.updateGPA();
        cout << "Course's Grade has been Updated To " << grade << "\nPress Any Key To Continue: ";
        _getch();
        return;
    }
    cout << "Nothing's Updated!\nPress Any Key To Continue: ";
    _getch();
}

void Admin::fileUpload(map<string, Student>& students) {
    system("cls");
    string fileName;

    cout << "Enter File Name : ";
    fileName = Handleable::emptyString([&]() -> string { getline(cin, fileName); return fileName; }(), "File Name");
    if (fileName == "students" || fileName == "courses" || fileName == "admins" || fileName == "instructors" || fileName == "prerequisites") {
        cout << "File Name Is Not Allowed" << endl;
        return;
    }

    ifstream file(fileName + ".csv");

    if (!file) {
        cout << "Error opening students Grades file!" << endl;
        return;
    }

    int row = 1;
    bool isValid, isExist;
    string line;
    queue<string> data, coursesIDs, coursesGrades;
    string studentID;
    map<string, Student>::iterator student;

    try {
        getline(file, line); // to ignore header

        while (getline(file, line)) {
            data = split(line, ',');
            studentID = data.front(), data.pop();

            student = students.find(studentID);
            if (student == students.end())
                throw runtime_error("");

            coursesIDs = split(data.front(), '&'), data.pop();
            coursesGrades = split(data.front(), '&'), data.pop();

            do {
                if (coursesIDs.empty() || coursesGrades.empty() || coursesIDs.front() == "" || coursesGrades.front() == "")
                    throw runtime_error("");

                isExist = false;
                for (auto& course : student->second.getRegisteredCourses()) {
                    if (course.first->getID() == coursesIDs.front()) {
                        isExist = true;
                        if (!isValidGrade(coursesGrades.front())) {
                            throw runtime_error("");
                        }
                        course.second = coursesGrades.front();
                    }
                }

                if (!isExist)
                    throw runtime_error("");
                coursesIDs.pop(), coursesGrades.pop();
            } while (!coursesIDs.empty() && !coursesGrades.empty() && coursesIDs.front() != "" && coursesGrades.front() != "");
            row++;
        }
        cout << "Grades Have Been Uploaded Successfully" << endl;
    } catch (const runtime_error& e) {
        cout << "Invalid Data At Row " << row << " In File" << endl;
    } catch (...) {
        cout << "Error While Reading The File!" << endl;
    }
    file.close();
}

void Admin::uploadGrades(map<string, Student>& students) {
    int choice = 0;
    while (true) {
        system("cls");
        cout << "1 : Upload Students Grades Manually.\n2 : Upload Students Grades'CSV File.\n3 : Back.\n\nChoice: ";
        choice = Handleable::handlingChoiceNotFound(3);
        cin.ignore();
        switch (choice) {
        case 1:
            manualUpload(students);
            break;
        case 2:
            fileUpload(students);
        case 3:
            return;
        default:
            break;
        }
    }
}

void Admin::manageCoursePrerequisites(unordered_map<string, Course>& courses) {
    int choice = 0;
    string courseID, preID;

    auto read = [](string input) -> string {
        getline(cin, input);
        return input;
    };

    while (true) {
        system("cls");
        cout << "\n1 : Add Prerequisite To A Course.\n2 : Remove Prerequisite From A Course.\n3 : Back.\n\nChoice: ";
        choice = Handleable::handlingChoiceNotFound(3);
        cin.ignore();

        if (choice == 3) {
            return;
        }

        cout << "Enter Course ID : ";
        courseID = Handleable::emptyString(read(courseID), "Course ID");
        auto course = courses.find(courseID);
        if (course == courses.end()) {
            cout << "\nInvalid Course ID\nPress Any Key To Try Again: ";
            _getch();
            continue;
        }

        if (choice == 2 && course->second.getPrerequisite().empty()) {
            cout << course->second.getTitle() << " Does Not Have Prerequisites!\nPress Any Key To Continue: ";
            _getch();
            continue;
        }

        cout << "Enter Prerequisite ID : ";
        preID = Handleable::emptyString(read(preID), "Prerequisite ID");


        if (courses.find(preID) == courses.end()) {
            cout << "Invalid Prerequisite ID\nPress Any Key To Try Again: ";
            _getch();
            continue;
        }

        if (choice == 1) {
            courses[courseID].addPrerequisite(&courses[preID]);
            cout << "Prerequisite Has Been Added Successfully" << endl;
        } else {
            courses[courseID].removePrerequisite(courses[preID]);
            cout << "Prerequisite Has Been Removed Successfully" << endl;
        }
        cout << "Press Any Key To Try Again: ";
        _getch();
    }
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

queue<string> Admin::split(string line, char ch) {
    int initIndex = 0;
    int finalIndex;
    queue<string> q;
    while (true) {
        finalIndex = line.find(ch);
        q.push(line.substr(initIndex, finalIndex));
        line.erase(initIndex, finalIndex + 1);
        if (finalIndex == -1)
            break;
    }
    return q;
}
