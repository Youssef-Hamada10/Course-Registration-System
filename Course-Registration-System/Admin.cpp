#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include "Handleable.h"
#include "Admin.h"
#include <iomanip>

using namespace std;

Semester Admin::currentSemester = Fall;

unordered_set<string> grades = {
    "A+", "A", "A-",
    "B+", "B", "B-",
    "C+", "C", "C-",
    "D+", "D", "F"
};

Admin::Admin(string username, string password) {
	this->username = username;
	this->password = password;
}

Admin::Admin(const Admin& other) {
	this->ID = other.ID;
	this->username = other.username;
	this->password = other.password;
}

Admin::Admin() {
}

void Admin::menu(map<string, Student>& students, unordered_map<string, Course>& courses, unordered_map<string, Instructor>& instructors) {
    int choice = 0;

    while (true) {
        system("cls");
        cout << "Welcome " << username << endl;
        cout << "_______________________\n\n";
        cout << "1 : Manage Students\n2 : Manage Courses.\n3 : Add Instructor.\n4 : Generate Course Report\n5 : Log Out\n\n\nYour Choice: ";
        choice = Handleable::handlingChoiceNotFound(5);
        cin.ignore();
        switch (choice) {
        case 1:
            manageStudents(students);
            break;
        case 2:
            manageCourses(courses, instructors);
            break;
        case 3:
            addInstructorToSystem(instructors);
            break;
        case 4:
            generateCourseReport(students, courses);
            break;
        case 5:
            return;
        default:
            break;
        }
    }
}

void Admin::manageStudents(map<string, Student>& students) {
    int choice = 0;
    
    while (true) {
        system("cls");
        cout << "\n1 : Edit a Student's Personal Info\n2 : Edit Students Grades.\n3 : Display All Students.\n4 : Back.\n\nChoice: ";
        choice = Handleable::handlingChoiceNotFound(4);

        cin.ignore();
        switch (choice) {
        case 1:
            editStudentInfo(students);
            break;
        case 2:
            EditStudentGrades(students); // by file
            break;
        case 3:
            displayAllStudents(students);
            break;
        case 4:
            return;
        default:
            break;
        }
    }
}

void Admin::editStudentInfo(map<string, Student>& students) {
    string ID, value;
    int choice = 0;

    auto read = [&]() {
        getline(cin, ID);
        return ID;
    };

    cout << "\nEnter Student ID: ";
    ID = Handleable::emptyString(read(), "ID");

    auto student = students.find(ID);
    if (student == students.end()) {
        cout << "Student Does Not Exist, Press Any Key To Try Again: ";
        _getch();
        return;
    }
    student->second.displayInfo();

    cout << "\nYour Choice (12 For Exit): ";
    choice = Handleable::handlingChoiceNotFound(12);

    if (choice == 9) {
        int lvl = 0;
        cout << "\nEnter New Level: ";
        lvl = Handleable::handlingInt("Level");

        cout << "\nAre You Sure To Change The Level From " << student->second.getStudyLvl() << " To " << lvl << " (Y || N): ";
        if (Handleable::toContinue()) {
            student->second.setStudyLvl(lvl);
            cout << "\nLevel's Been Updated For Student With ID: " << student->first << "\n";
        }
    }
    else if (choice == 10) {
        string value = "";
        cin.ignore();
        do {
            cout << "\nEnter New Major: ";
            value = Handleable::handlingMinInputs(Handleable::emptyString(read(), "Major"), 2);
        } while (Handleable::trim(value).empty());

        value = Handleable::trim(Handleable::toUpperCase(value));
        cout << "\nAre You Sure To Change The Major From " << student->second.getMajor() << " To " << value << " (Y || N): ";
        if (Handleable::toContinue()) {
            student->second.setMajor(value);
            cout << "\nMajor's Been Updated For Student With ID: " << student->first << "\n";
        }
    }
    else {
        while (!student->second.editInfo(choice)) {
            cout << "\nInvalid Input Data, Press Any Key To Try Again: ";
            _getch();
        }
    }

    cout << "\nPress Any Key To Continue: ";
    _getch();
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
    
    do {
        cout << "\nEnrolled Courses: \n";
        student->second.displayGrades();
        do {
            cin.ignore();
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
            cout << "Course's Grade has been Updated To " << grade << "\nDo You Want to Insert Another Course Grade For That Student(Y || N): ";
        }
    } while (Handleable::toContinue());
    //cout << "Nothing's Updated!\nPress Any Key To Continue: ";
    //_getch();
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

void Admin::EditStudentGrades(map<string, Student>& students) {
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

void Admin::manageCourses(unordered_map<string, Course>& courses, unordered_map<string, Instructor>& instructors) {
    int choice = 0;

    while (true) {
        system("cls");
        cout << "1 : Add New Course.\n2 : Edit a Course.\n3 : Manage Prerequisites.\n4 : Manage Instructors.\n5 : Manage Majors.\n6 : Back.\n\nChoice: ";
        choice = Handleable::handlingChoiceNotFound(6);

        switch (choice) {
        case 1:
            addCourse(courses, instructors);
            break;
        case 2:
            editCourse(courses, instructors);
            break;
        case 3:
            manageCoursePrerequisites(courses);
            break;
        case 4:
            manageInstructors(courses, instructors);
            break;
        case 5:
            manageCourseMajors(courses);
        case 6:
            return;
        default:
            break;
        }
    }
}

void Admin::editCourse(unordered_map<string, Course>& courses, unordered_map<string, Instructor>& instructors) {
    int choice = 0;
    string value;

    auto read = [&]() -> string {
        if (std::cin.rdbuf()->in_avail() > 0 && std::cin.peek() == '\n') { // rdbuf points to input memory
            std::cin.ignore();
        }
        getline(cin, value);
        return value;
    };

    cout << "Enter Course ID: ";
    value = Handleable::toUpperCase(Handleable::emptyString(read(), "Course ID"));

    auto courseIt = courses.find(value);

    if (courseIt == courses.end()) {
        cout << "\nInvalid Course ID\nPress Any Key To Try Again: ";
        _getch();
        return;
    }

    while (true) {
        courseIt->second.displayCourseInfo();
        cout << "\nEnter Choice To Edit (9 To Exit): ";
        choice = Handleable::handlingChoiceNotFound(9);

        switch (choice) {
        case 1:
        {
            cout << "\nID Cannot Be Changed, Press Any Key To Try Again: ";
            _getch();
        }
        return;
        case 2:
        {
            do {
                cout << "Enter New Course Title: ";
                value = Handleable::handlingMinInputs(Handleable::emptyString(read(), "Course Title"), 4);
            } while (value.empty());

            cout << "Are You Sure You Want To Change Course Title From " << courseIt->second.getTitle() << " To " << value << " ?";
            if (Handleable::toContinue()) {
                cout << "Changes've Been Set, Press Any Key To Continue: ";
                courseIt->second.setTitle(value);
                _getch();
                return;
            }
            cout << "Nothing Is Changed, Press Any Key To Continue: ";
            _getch();
        }
        break;
        case 3:
        {
            do {
                cout << "Enter New Course Syllabus: ";
                value = Handleable::handlingMinInputs(Handleable::emptyString(read(), "Course Syllabus"), 10);
            } while (value.empty());

            cout << "Are You Sure You Want To Change Course Syllabus From " << courseIt->second.getSyllabus() << " To " << value << " ?";
            if (Handleable::toContinue()) {
                cout << "Changes've Been Set, Press Any Key To Continue: ";
                courseIt->second.setSyllabus(value);
                _getch();
                return;
            }
            cout << "Nothing Is Changed, Press Any Key To Continue: ";
            _getch();
        }
        break;
        case 4:
        {
            do {
                cout << "Enter New Course Semester: ";
                value = Handleable::trim(Handleable::toLowerCase(Handleable::emptyString(read(), "Course Semester")));
            } while (value.empty() && (value != "spring" || value != "fall"));

            cout << "Are You Sure You Want To Change Course Semester From " << (courseIt->second.getSemester() == 0 ? "Fall" : "Spring") << " To " << value << " ?";
            if (Handleable::toContinue()) {
                cout << "Changes've Been Set, Press Any Key To Continue: ";
                courseIt->second.setSemester(value == "fall" ? Fall : Spring);
                _getch();
                return;
            }
            cout << "Nothing Is Changed, Press Any Key To Continue: ";
            _getch();
        }
        break;
        case 5:
        {
            int hours = 0;
            cout << "Enter New Course Credit Hours: ";
            hours = Handleable::handlingInt("Credit Hours");
            cout << "Are You Sure You Want To Change Credit Hours From " << courseIt->second.getCreditHours() << " To " << hours << " ?";

            if (Handleable::toContinue()) {
                cout << "Changes've Been Set, Press Any Key To Continue: ";
                courseIt->second.setCreditHours(hours);
                _getch();
                return;
            }
            cout << "Nothing Is Changed, Press Any Key To Continue: ";
            _getch();
        }
        break;
        case 6:
            manageInstructors(courses, instructors);
            break;
        case 7:
            manageCoursePrerequisites(courses);
            break;
        case 8:
            manageCourseMajors(courses);
            break;
        case 9:
            return;
        default:
            break;
        }
    }
}

void Admin::addCourse(unordered_map<string, Course>& courses, unordered_map<string, Instructor>& instructors) {
    string ID, title, syllabus, semester, major, instID, preID;
    int creditHours;

    auto read = [](string& value) -> string {
        getline(cin, value);
        return value;
    };

    cin.ignore();
    do {
        cout << "\nEnter Course's ID (Cannot Be Changed After been Set): ";
        ID = Handleable::handlingMinInputs(Handleable::toUpperCase(Handleable::emptyString(read(ID), "Course ID")), 3);
        
        if (!ID.empty()) {
            break;
        }
        cout << "\nInvalid ID Input, Press Any Key To Try Again: ";
        _getch();
    } while (true);

    do {
        cout << "\nEnter Course's Title: ";
        title = Handleable::handlingMinInputs(Handleable::emptyString(read(title), "Course Title"), 4);
        
        if (!title.empty()) {
            break;
        }
        cout << "\nInvalid Title Input, Press Any Key To Try Again: ";
        _getch();
    } while (true);
    
    do {
        cout << "\nEnter Course's Syllabus: ";
        syllabus = Handleable::handlingMinInputs(Handleable::emptyString(read(syllabus), "Course Syllabus"), 10);
        
        if (!syllabus.empty()) {
            break;
        }
        cout << "\nInvalid Syllabus Input, Press Any Key To Try Again: ";
        _getch();
    } while (true);

    do {
        cout << "\nEnter Course's Semester (Fall || Spring): ";
        semester = Handleable::trim(Handleable::toLowerCase(Handleable::emptyString(read(semester), "Course Semester")));
        
        if (!semester.empty() && (semester == "fall" || semester == "spring")) {
            break;
        }
        cout << "\nInvalid Semester Input, Press Any Key To Try Again: ";
        _getch();
    } while (true);

    cout << "\nEnter Course's Credit Hours: ";
    creditHours = Handleable::handlingInt("Credit Hours");

    do {
        cout << "\nEnter Course's Requiered Major: ";
        major = Handleable::emptyString(read(major), "Course Major");
        if (major.empty()) {
            cout << "\nInvalid Input Data, Press Any Key To Try Again: ";
            _getch();
        }
        else
            break;
    } while (true);

    do {
        cout << "\nEnter Course's Instructor ID: ";
        instID = Handleable::toUpperCase(Handleable::emptyString(read(instID), "Instructor ID"));
        auto instIt = instructors.find(instID);
        if (instIt == instructors.end()) {
            cout << "\Instructor Does Not Exist, Press Any Key To Try Again: ";
            _getch();
        }
        else
            break;
    } while (true);

    do {
        cout << "Enter Course's Prerequisite ID To Add: ";
        preID = Handleable::emptyString(read(preID), "Prerequisite ID");
        if (courses.find(preID) == courses.end()) {
            cout << "Invalid Prerequisite ID\nPress Any Key To Try Again: ";
            _getch();
        }
        else
            break;
    } while (true);

    cout << "\nAre you Sure You Want To Create " << title << " (Y || N)?";
    if (Handleable::toContinue()) {
        Course course(ID, title, syllabus, creditHours, semester == "fall" ? Fall : Spring);
        course.addMajor(major);
        course.addInstructor(&instructors.find(instID)->second);
        course.addPrerequisite(&courses[preID]);
        courses.insert({ ID, course });
        cout << "\nCourse's Been Add Successfully With: ";
        course.displayCourseInfo();
        cout << "\nPress Any Key To Continue: ";
        _getch();
        return;
    }

    cout << "\nNothing is Added, Press Any Key To Continue: ";
    _getch();
}

void Admin::addInstructorToSystem(unordered_map<string, Instructor>& instructors) {
    int ID = 0;
    string value;
    Instructor instructor;
    auto read = [&value]() -> string {
        getline(cin, value);
        return value;
    };
    system("cls");
    do {
        cout << "\nEnter Instructor Name: ";
        instructor.name = Handleable::handlingMinInputs(Handleable::emptyString(read(), "Name"), 9);
        cout << "Enter Instructor's Department: ";
        instructor.department = Handleable::handlingMinInputs(Handleable::emptyString(read(), "Department"), 4);

        if (!instructor.name.empty() && !instructor.department.empty()) {
            break;
        }
        cout << "\nInvalid Input Data, Press Any Key To Try Again: ";
        _getch();
    } while (true);
    
    cout << "Are You Sure About Creating New Instructor With Name -> " << instructor.name << " and Department -> " << instructor.department << "(Y || N): ";
    if (Handleable::toContinue()) {
        do {
            srand(static_cast<unsigned int>(time(0)));
            instructor.ID = to_string(rand() % 90000 + 10000);
        } while (instructors.find(instructor.ID) != instructors.end());
        instructors.insert({ instructor.ID, instructor });
        cout << instructor.name << " With ID " << instructor.ID << " Has Been Added To Instructors' List!, Press Any Key To Continue: ";
        _getch();
        return;
    }
    cout << "Nothing Is Updated, Press Any Key To Continue: ";
    _getch();
    return;
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
        if (courses.find(courseID) == courses.end()) {
            cout << "Invalid Course ID\nPress Any Key To Try Again: ";
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
        } else if (choice == 2) {
            courses[courseID].removePrerequisite(courses[preID]);
            cout << "Prerequisite Has Been Removed Successfully" << endl;
        }
        cout << "Press Any Key To Continue: ";
        _getch();
    }
}

void Admin::manageInstructors(unordered_map<string, Course>& courses, unordered_map<string, Instructor>& instructors) {
    int choice = 0;

    while (true) {
        system("cls");
        cout << "\n1 : Add Instructor To Course.\n2 : Remove Instructor From Course.\n3 : Back.\n\nChoice: ";
        choice = Handleable::handlingChoiceNotFound(4);
        cin.ignore();

        switch (choice) {
        case 1:
            addInstructorInCourse(courses, instructors);
            break;
        case 2:
            removeInstructorFromCourse(courses, instructors);
            break;
        case 3:
            return;
        default:
            break;
        }
    }
}

void Admin::manageCourseMajors(unordered_map<string, Course>& courses) {
    int choice = 0;

    while (true) {
        system("cls");
        cout << "1 : Add Major To A Course.\n2 : Remove Major From A Course.\n3 : Back\nChoice: ";
        choice = Handleable::handlingChoiceNotFound(3);
        cin.ignore();
        switch (choice) {
        case 1:
            addMajor(courses);
            break;
        case 2:
            removeMajor(courses);
            break;
        case 3:
            return;
        default:
            break;
        }
    }
}

void Admin::addInstructorInCourse(unordered_map<string, Course>& courses, unordered_map<string, Instructor>& instructors) {
    string courseID, instID;

    auto read = [](string& value) -> string {
        if (std::cin.rdbuf()->in_avail() > 0 && std::cin.peek() == '\n') { // rdbuf points to input memory
            std::cin.ignore();
        }
        getline(cin, value);
        return value;
    };

    cout << "\nEnter Course ID: ";
    courseID = Handleable::toUpperCase(Handleable::emptyString(read(courseID), "Course ID"));
    auto courseIt = courses.find(courseID);

    if (courseIt == courses.end()) {
        cout << "\nCourse Does Not Exist, Press Any Key To Try Again: ";
        _getch();
        return;
    }

    cout << "\nEnter Instructor ID: ";
    instID = Handleable::toUpperCase(Handleable::emptyString(read(instID), "Instructor ID"));
    auto instIt = instructors.find(instID);

    if (instIt == instructors.end()) {
        cout << "\Instructor Does Not Exist, Press Any Key To Try Again: ";
        _getch();
        return;
    }

    cout << "Are You Sure You Want To Add " << instIt->second.name << " To " << courseIt->second.getTitle() << " ? (Y | N)";

    if (Handleable::toContinue()) {
        cout << instIt->second.name << "'s Been Added Successfully To " << courseIt->second.getTitle() << endl;
        courseIt->second.addInstructor(&instIt->second);
        cout << "\nPress Any Key To Continue: ";
        _getch();
        return;
    }

    cout << "\nNothing Is Added, Press Any Key To Continue: ";
    _getch();
}

void Admin::removeInstructorFromCourse(unordered_map<string, Course>& courses, unordered_map<string, Instructor>& instructors) {
    string courseID, instID;

    auto read = [](string& value) -> string {
        if (std::cin.rdbuf()->in_avail() > 0 && std::cin.peek() == '\n') { // rdbuf points to input memory
            std::cin.ignore();
        }
        getline(cin, value);
        return value;
    };

    cout << "\nEnter Course ID: ";
    courseID = Handleable::toUpperCase(Handleable::emptyString(read(courseID), "Course ID"));
    auto courseIt = courses.find(courseID);

    if (courseIt->second.getInstructors().empty()) {
        cout << courseIt->second.getTitle() << " Does Not Have Instructors Yet, Press Any Key To Continue: ";
        _getch();
        return;
    }

    if (courseIt == courses.end()) {
        cout << "\nCourse Does Not Exist, Press Any Key To Try Again: ";
        _getch();
        return;
    }

    cout << "\nEnter Instructor ID: ";
    instID = Handleable::toUpperCase(Handleable::emptyString(read(instID), "Instructor ID"));
    auto instIt = instructors.find(instID);

    if (instIt == instructors.end()) {
        cout << "\Instructor Does Not Exist, Press Any Key To Try Again: ";
        _getch();
        return;
    }

    cout << "Are You Sure You Want To Remove " << instIt->second.name << " From " << courseIt->second.getTitle() << " ? (Y | N)";

    if (Handleable::toContinue()) {
        cout << instIt->second.name << "'s Been Removed Successfully From " << courseIt->second.getTitle() << endl;
        courseIt->second.removeInstructor(instIt->second);
        cout << "\nPress Any Key To Continue: ";
        _getch();
        return;
    }

    cout << "\nNothing Is Removed, Press Any Key To Continue: ";
    _getch();
}

void Admin::addMajor(unordered_map<string, Course>& courses) {
    string ID, major;

    auto read = [](string& value) -> string {
        if (std::cin.rdbuf()->in_avail() > 0 && std::cin.peek() == '\n') { // rdbuf points to input memory
            std::cin.ignore();
        }
        getline(cin, value);
        return value;
    };

    cout << "\nEnter Course ID: ";
    ID = Handleable::toUpperCase(Handleable::emptyString(read(ID), "Course ID"));

    auto courseIt = courses.find(ID);

    if (courseIt == courses.end()) {
        cout << "\nCourse Does Not Exist, Press Any Key To Try Again: ";
        _getch();
        return;
    }

    const auto& majors = courseIt->second.getReqMajors();
    do {
        cout << "\nEnter New Major: ";
        major = Handleable::emptyString(read(major), "Course Major");

        if (find(majors.begin(), majors.end(), major) != majors.end()) {
            cout << "\nMajor Is Already Exist, Try Again? ";
            continue;
        }

        if (major.empty()) {
            cout << "\nInvalid Input Data, Try Again? ";
            continue;
        }
        cout << "Are You Sure You Want To Add " << major << " Major to " << courseIt->second.getTitle() << "? (Y | N)";

        if (Handleable::toContinue()) {
            cout << major << " 's Been Added Successfully To " << courseIt->second.getTitle() << endl;
            courseIt->second.addMajor(major);
        }

        cout << "Add Another Major ? (Y | N)";
    } while (Handleable::toContinue());

    cout << "\nPress Any Key To Continue: ";
    _getch();
}

void Admin::removeMajor(unordered_map<string, Course>& courses) {
    string ID, major;

    auto read = [](string& value) -> string {
        if (std::cin.rdbuf()->in_avail() > 0 && std::cin.peek() == '\n') { // rdbuf points to input memory
            std::cin.ignore();
        }
        getline(cin, value);
        return value;
    };

    cout << "\nEnter Course ID: ";
    ID = Handleable::toUpperCase(Handleable::emptyString(read(ID), "Course ID"));

    auto courseIt = courses.find(ID);

    if (courseIt == courses.end()) {
        cout << "\nCourse Does Not Exist, Press Any Key To Try Again: ";
        _getch();
        return;
    }

    bool isFound = false;
    do {
        cout << "\nEnter Major To Remove: ";
        major = Handleable::trim(Handleable::toUpperCase(Handleable::emptyString(read(major), "Course Major")));

        const auto& majors = courseIt->second.getReqMajors();
        for (const auto& mj : majors) {
            if (major == mj) {
                isFound = true;
                break;
            }
        }

        if (!isFound) {
            cout << "\nMajor Does Not Exist, Press Any Key To Try Again: ";
            _getch();
            continue;
        }
        else {
            cout << "Are You Sure You Want To Remove " << major << " Major From " << courseIt->second.getTitle() << "? (Y | N)";
            if (Handleable::toContinue()) {
                cout << major << "'s Been Removed Successfully From " << courseIt->second.getTitle() << endl;
                courseIt->second.removeMajor(major);
            }
            else {
                cout << "\nNothing Is Removed!\n";
            }
        }
        cout << "\nRemove Another Major ? (Y | N)";
    } while (Handleable::toContinue());

    cout << "\nPress Any Key To Continue: ";
    _getch();
}

void Admin::displayAllStudents(map<string, Student>& students) {
    system("cls");
    cout << left << setw(35) << "\nName" << setw(15) << "ID" << "Level" << endl;
    cout << string(77, '=') << endl;
    for (auto& student : students) {
        cout << left << setw(30) << student.second.getName() << setw(20) << student.second.getID() << student.second.getStudyLvl() << endl;
        Sleep(100);
    }
    cout << string(77, '=') << endl;
    cout << "Press Any Key To Continue: ";
    _getch();
}

void Admin::generateCourseReport(map<string, Student>& students, unordered_map<string, Course>& courses) {
    system("cls");

    string ID = "";
    cout << string(43, '-') << endl;
    cout << "Enter Course ID: ";

    getline(cin, ID);
    ID = Handleable::emptyString(ID, "Course ID");
    
    auto course = courses.find(ID);
    if (course == courses.end()) {
        cout << "Course Does Not Exist, Press Any Key To Continue: ";
        _getch();
        return;
    }

    string htmlFilename = course->second.getTitle() + "_Report.html";
    string pdfFilename = course->second.getTitle() + "_Report.pdf";

    ofstream htmlFile(htmlFilename);
    if (!htmlFile.is_open()) {
        cout << "Error while Creating HTML file\n";
        cout << "\npress any key to continue: ";
        _getch();
        return;
    }

    htmlFile << "<html>\n";
    htmlFile << "<head>\n";
    htmlFile << "<title>Course Report</title>\n";
    htmlFile << "<style>\n";
    htmlFile << "body { font-family: Arial, sans-serif; margin: 20px; }\n";
    htmlFile << "h1 { color: #333; }\n";
    htmlFile << "table { width: 100%; border-collapse: collapse; margin-bottom: 20px; }\n";
    htmlFile << "th, td { padding: 10px; text-align: left; border: 1px solid #ddd; }\n";
    htmlFile << "th { background-color: #f2f2f2; }\n";
    htmlFile << "td { background-color: #fafafa; }\n";
    htmlFile << "h2 { color: #0056b3; margin-top: 20px; }\n";
    htmlFile << "strong { color: #007bff; }\n";
    htmlFile << "</style>\n";
    htmlFile << "</head>\n";
    htmlFile << "<body>\n";
    htmlFile << "<table>\n";
    htmlFile << "<tr><th>Student ID</th><th>Student Name</th><th>Major</th><th>Level</th></tr>\n";
    
    for (auto& s : students)
    {
        for (auto c = s.second.getRegisteredCourses().rbegin(); c != s.second.getRegisteredCourses().rend(); ++c)
        {
            if (c->first->getID() == course->second.getID() && c->second == "N.A")
            {
                htmlFile << "<tr>\n";
                htmlFile << "<td>" << s.first << "</td>\n";
                htmlFile << "<td>" << s.second.getName() << "</td>\n";
                htmlFile << "<td>" << s.second.getMajor() << "</td>\n";
                htmlFile << "<td>" << s.second.getStudyLvl() << "</td>\n";
                htmlFile << "</tr>\n";
                break;
            }
        }
    }

    htmlFile << "</table>\n";
    htmlFile << "</body>\n";
    htmlFile << "</html>\n";
    htmlFile.close();
    string command = "wkhtmltopdf \"" + htmlFilename + "\" \"" + pdfFilename + "\"";
    system(command.c_str());
    cout << "PDF report created successully\n";
    remove(htmlFilename.c_str());
    cout << "\npress any key to continue: ";
    _getch();
}

bool Admin::isValidGrade(string grade) {
    return grades.find(grade) != grades.end();
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
