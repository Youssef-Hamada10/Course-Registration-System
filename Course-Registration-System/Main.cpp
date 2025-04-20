#include <iostream>
#include <map>
#include <fstream>
#include <queue>
#include <stack>
#include <string>
#include <forward_list>
#include "Person.h"
#include "Admin.h"
#include "Course.h"
#include "Student.h"

using namespace std;

queue<string> split(string line, char ch);
void readStudents(map<string,Student>& students, map<string,Course>& courses);    // 2
void readCourses(map<string,Course>& courses);     // 1
void readInstructors(map<string,Course>& courses);
void readPrerequisites(map<string,Course>& courses);
void writeStudents(map<string,Student> students);
void writeCourses(map<string,Course> courses);
void writeInstructors(map<string,Course> courses);
void writePrerequisites(map<string,Course> courses);
string encrypt(const string& input, char key);

int main() {

    map<string,Student> students;
    map<string,Course> courses;

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

void readStudents(map<string,Student>& students, map<string,Course>& courses) {
    ifstream file ("students.csv");

    if (!file) {
        cout << "Error opening students file!" << endl;
        return;
    }

    string line;
    queue<string> data;
    Student student;

    getline(file, line); 
    while (getline(file, line)) {    
        data = split(line, ',');
        student.setID(data.front()), data.pop();
        student.setUsername(data.front()), data.pop();
        student.setPassword(encrypt(data.front(), 'M')), data.pop();
        student.setUsername(data.front()), data.pop();
        student.setNationality(data.front()), data.pop();
        student.setNationalID(data.front()), data.pop();
        student.setTelephoneNumber(data.front()), data.pop();
        student.setAddress(data.front()), data.pop();
        student.setGpa(stof(data.front())), data.pop();
        student.setStudyLvl(stoi(data.front())), data.pop();
        student.setCurrentCreditHours(stoi(data.front())), data.pop();
        students.insert({student.getId(), student});
        while(!data.empty()){
            students.at(student.getId()).registerCourse(courses.at(data.front())), data.pop();
        }
    }
    file.close();
}

void writeStudents(map<string,Student> students) {
    ofstream file("students.csv");

    if (!file) {
        cout << "Error opening students file!" << endl;
        return;
    }

    file << "Student ID,Username,Password,Name,Nationality,National ID,Telephone Number,Address,GPA,Study Level,Total Credit Hours,Registered Course ID\n";  // Header
    
    stack<Course> registeredCourses;

    for (auto it : students) {
        file << it.first << ",";
        file << it.second.getUsername() << ",";
        file << encrypt(it.second.getPassword(), 'M') << ",";
        file << it.second.getName() << ",";
        file << it.second.getNationality() << ",";
        file << it.second.getNationalId() << ",";
        file << it.second.getTelephoneNumber() << ",";
        file << it.second.getAddress() << ",";
        file << it.second.getGpa() << ",";
        file << it.second.getStudyLvl() << ",";
        file << it.second.getCurrentCreditHours();
        registeredCourses = it.second.getRegisteredCourses();
        while(!registeredCourses.empty())
             file << "," << registeredCourses.top().getID(), registeredCourses.pop();
        file << endl;
    }
    file.close();
}

void readCourses(map<string,Course>& courses) {
    ifstream file ("courses.csv");
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    string line;
    queue<string> data;
    Course course;
    Course prerequisite;

    getline(file, line);
    while (getline(file, line)) {    
        data = split(line, ',');
        course.setID(data.front()), data.pop();
        course.setTitle(data.front()), data.pop();
        course.setSyllabus(data.front()), data.pop();
        course.setCreditHours(stoi(data.front())), data.pop();
        course.setNumOfInstructor(stoi(data.front())), data.pop();
        course.setNumOfPrerequisite(stoi(data.front())), data.pop();

        courses.insert({course.getID(), course});
    }
    readInstructors(courses);
    readPrerequisites(courses);
    file.close();
}

void writeCourses(map<string,Course> courses) {
    ofstream file("courses.csv");

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    file << "Course ID,Title,Syllabus,Credit Hours,Num Of Instructors,Instructor ID,,Num Of Prerequisites,Prerequisite ID\n";
    for (auto it : courses) {
        file << it.first << ",";
        file << it.second.getTitle() << ",";
        file << it.second.getSyllabus() << ",";
        file << it.second.getCreditHours();
        file << it.second.getNumOfInstructor() << ",";
        for (auto inst : it.second.getInstructors()) {
            file << "," << inst.id;  
        }
        file << "," << it.second.getNumOfPrerequisite();
        for (auto pre : it.second.getPrerequisite()) {
            file << "," << pre.getID();
        }
       file << endl;
    }
    file.close();
}

void readInstructors(map<string,Course>& courses) {
    ifstream file ("instructors.csv"); 

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
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
        instructor.courseID= data.front(), data.pop();

        courses.at(instructor.courseID).addInstructor(instructor);
    }

    file.close();
}

void writeInstructors(map<string,Course> courses) {
    ofstream file("instructors.csv"); 

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    file << "Instructor ID,Name,Department,Course ID\n";  // Header
    for (auto it : courses) {
        for(auto ins : it.second.getInstructors()){
            file << ins.id << ",";
            file << ins.name << ",";
            file << ins.department << ",";
        }
        file << it.first << endl;
    }
    file.close();
}

void readPrerequisites(map<string,Course>& courses) {
    ifstream file ("prerequisites.csv"); 

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }
    string line;
    queue<string> data;

    string courseID;
    string preCourseID;

    getline(file, line); 

    while (getline(file, line)) {    
        data = split(line, ',');
        courseID = data.front(), data.pop();
        while (!data.empty()) {
            preCourseID= data.front(), data.pop();
            courses.at(courseID).addPrerequisite(courses.at(preCourseID));
        }
    }
    file.close();
}

void writePrerequisites(map<string,Course> courses) {
    ofstream file("prerequisites.csv"); 

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    file << "Course ID,Prerequisite Course ID\n";  // Header
    for (auto it : courses) {
        file << it.first;
        for (auto pre : it.second.getPrerequisite()) {
            file << "," << pre.getID();
        }
        file << endl;
    }

    file.close(); 
}

string encrypt(const string& input, char key) {
    string output = input;
    for (int i = 0; i < input.size(); i++){
        output[i] = input[i] ^ key;
    }
    return output;
}
