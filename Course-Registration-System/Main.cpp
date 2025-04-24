#include <iostream>
#include <map>
#include <fstream>
#include <queue>
#include <deque>
#include <string>
#include <forward_list>
#include "Student.h"

using namespace std;

queue<string> split(string line, char ch);
void readStudents(map<string, Student>& students, map<string, Course>& courses);
void readCourses(map<string, Course>& courses);
void readInstructors(map<string, Course>& courses);
void readPrerequisites(map<string, Course>& courses);
void writeStudents(map<string, Student> students);
void writeCourses(map<string, Course> courses);
void writeInstructors(map<string, Course> courses);
void writePrerequisites(map<string, Course> courses);
string encrypt(const string& input, char key);

int main() {

    map<string, Student> students;
    map<string, Course> courses;

    readCourses(courses);
    readStudents(students, courses);

    /*cout << "students..........\n";
    deque<Course> d;
    for (auto it : students) {
        cout << "ID: " << it.first << "\t";
        cout << "tele: " << it.second.getTelephoneNumber() << "\t";
        cout << "SSN: " << it.second.getNationalId() << " \t";
        cout << it.second.getRegisteredCourses().size() << endl;
    }*/


    //cout << "courses......\n";
    /*for (auto it : courses) {
    cout << "ID: " << it.first << " credit hours " << it.second.getCreditHours() << endl;
    }*/


    //cout << "prerequisites........\n";
    /*for (auto it : courses) {
        cout << "ID: " << it.second.getId() << "\t";
        for (auto p : it.second.getPrerequisite()) {
            cout << "pre course " << p.getId() << "\t";
        }
        cout << endl;
    }*/


    //cout << "instructors.....\n";
    /*for (auto it : courses) {
        cout << "ID: " << it.first << "\t";
        for (auto i : it.second.getInstructors()) {
            cout << i.name << "\t";
        }
        cout << endl;
    }*/

    writeCourses(courses);
    writeInstructors(courses);
    writePrerequisites(courses);
    writeStudents(students);
    return 0;
}

queue<string> split(string line, char ch) {
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

void readStudents(map<string, Student>& students, map<string, Course>& courses) {
    ifstream file("students.csv");

    if (!file) {
        cout << "Error opening students file!" << endl;
    }

    string line;
    queue<string> data;
    queue<string> IDs;
    Student student;

    getline(file, line); // to ignore header 
    while (getline(file, line)) {
        data = split(line, ',');
        student.setId(data.front()), data.pop();
        student.setUsername(data.front()), data.pop();
        student.setPassword(data.front()), data.pop();
        student.setName(data.front()), data.pop();
        student.setNationality(data.front()), data.pop();
        student.setNationalId(data.front()), data.pop();
        student.setTelephoneNumber(data.front().insert(0, "0")), data.pop();
        student.setAddress(data.front()), data.pop();
        student.setGpa(stof(data.front())), data.pop();
        student.setStudyLvl(stoi(data.front())), data.pop();
        student.setCurrentCreditHours(stoi(data.front())), data.pop();

        students.insert({ student.getId(), student });

        if (!data.empty() && data.front() != "") {
            IDs = split(data.front(), '&'), data.pop();
            while (!IDs.empty() && IDs.front() != "") {  // get registered courses ids
                students[student.getId()].registerCourseInFiles(courses[IDs.front()]), IDs.pop();
            }
        }
    }

    file.close();
}

void writeStudents(map<string, Student> students) {
    ofstream file("students.csv");

    if (!file) {
        cout << "Error opening students file!" << endl;
    }

    file << "Student ID,Username,Password,Name,Nationality,National ID,Telephone Number,Address,GPA,Study Level,Total Credit Hours,Registered Courses IDs\n";  // Header

    deque<Course> registeredCourses;
    string IDs;

    for (auto& it : students) {
        file << it.first << ",";
        file << it.second.getUsername() << ",";
        file << it.second.getPassword() << ",";
        file << it.second.getName() << ",";
        file << it.second.getNationality() << ",";
        file << it.second.getNationalId() << ",";
        file << it.second.getTelephoneNumber() << ",";
        file << it.second.getAddress() << ",";
        file << it.second.getGpa() << ",";
        file << it.second.getStudyLvl() << ",";
        file << it.second.getCurrentCreditHours();

        registeredCourses = it.second.getRegisteredCourses();
        IDs = "";

        for (auto c = registeredCourses.begin(); c != registeredCourses.end(); ++c) {
            IDs.append(c->getId());
            IDs.append("&");
        }

        if (!it.second.getRegisteredCourses().empty())
            file << "," << IDs.substr(0, IDs.size() - 1);

        file << endl;
    }
    file.close();
}

void readCourses(map<string, Course>& courses) {
    ifstream file("courses.csv");
    if (!file) {
        cout << "Error opening courses file!" << endl;
    }

    string line;
    queue<string> data;
    Course course;

    getline(file, line);  // to ignore header

    while (getline(file, line)) {
        data = split(line, ',');
        course.setId(data.front()), data.pop();
        course.setTitle(data.front()), data.pop();
        course.setSyllabus(data.front()), data.pop();
        course.setCreditHours(stoi(data.front())), data.pop();
        courses.insert({ course.getId(), course });
    }

    readInstructors(courses);
    readPrerequisites(courses);

    file.close();
}

void writeCourses(map<string, Course> courses) {
    ofstream file("courses.csv");

    if (!file) {
        cout << "Error opening courses file!" << endl;
        return;
    }

    string instructorsIDs;
    string prerequisitesIDs;

    file << "Course ID,Title,Syllabus,Credit Hours,Instructor ID,Prerequisite ID\n";

    for (auto it : courses) {
        file << it.first << ",";
        file << it.second.getTitle() << ",";
        file << it.second.getSyllabus() << ",";
        file << it.second.getCreditHours();
        instructorsIDs = "";
        prerequisitesIDs = "";

        for (auto inst : it.second.getInstructors()) {
            instructorsIDs.append(inst.id);
            instructorsIDs.append("&");
        }
        file << "," << instructorsIDs.substr(0, instructorsIDs.size() - 1);

        for (auto pre : it.second.getPrerequisite()) {
            prerequisitesIDs.append(pre.getId());
            prerequisitesIDs.append("&");
        }
        if (!it.second.getPrerequisite().empty())
            file << "," << prerequisitesIDs.substr(0, prerequisitesIDs.size() - 1);

        file << endl;
    }

    file.close();
}

void readInstructors(map<string, Course>& courses) {
    ifstream file("instructors.csv");

    if (!file) {
        cout << "Error opening instructors file!" << endl;
    }

    string line;
    queue<string> data;
    Instructor instructor;

    getline(file, line); // to ignore header

    while (getline(file, line)) {
        data = split(line, ',');
        instructor.id = data.front(), data.pop();
        instructor.name = data.front(), data.pop();
        instructor.department = data.front(), data.pop();
        instructor.courseId = data.front(), data.pop();

        if(instructor.courseId != "")
            courses[instructor.courseId].addInstructor(instructor);
    }

    file.close();
}

void writeInstructors(map<string, Course> courses) {
    ofstream file("instructors.csv");

    if (!file) {
        cout << "Error opening instructors file!" << endl;
        return;
    }

    file << "Instructor ID,Name,Department,Course ID\n";  // Header

    for (auto it : courses) {
        for (auto inst : it.second.getInstructors()) {
            file << inst.id << ",";
            file << inst.name << ",";
            file << inst.department << ",";
            file << it.first << endl;
        }
    }

    file.close();
}

void readPrerequisites(map<string, Course>& courses) {
    ifstream file("prerequisites.csv");

    if (!file) {
        cout << "Error opening prerequisites file!" << endl;
    }

    string line;
    queue<string> data;
    queue<string> IDs;
    string courseID;
    string preCourseID;

    getline(file, line);  // to ignore headred

    while (getline(file, line)) {
        data = split(line, ',');

        courseID = data.front(), data.pop();

        if (!data.empty() && data.front() != "") {
            IDs = split(data.front(), '&'), data.pop();

            while (!IDs.empty() && IDs.front() != "") {
                preCourseID = IDs.front(), IDs.pop();
                courses[courseID].addPrerequisite(courses[preCourseID]);
            }
        }
    }
    file.close();
}

void writePrerequisites(map<string, Course> courses) {
    ofstream file("prerequisites.csv");

    if (!file) {
        cout << "Error opening prerequisites file!" << endl;
        return;
    }

    string IDs;

    file << "Course ID,Prerequisite Courses IDs\n";  // Header

    for (auto it : courses) {
        file << it.first;
        IDs = "";
        for (auto pre : it.second.getPrerequisite()) {
            IDs.append(pre.getId());
            IDs.append("&");
        }

        if (!it.second.getPrerequisite().empty())
            file << "," << IDs.substr(0, IDs.size() - 1);

        file << endl;
    }

    file.close();
}

string encrypt(const string& input, char key) {
    string output = input;
    for (int i = 0; i < input.size(); i++) {
        output[i] = input[i] ^ key;
    }
    return output;
}