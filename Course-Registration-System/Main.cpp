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
void readStudents(map<string,Student>& students, map<string,Course>& courses);
void readCourses(map<string,Course>& courses);
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

    readCourses(courses);
    readStudents(students, courses);

    /*Student s;
    s.setID("2023170726");
    s.setUsername("omar123");
    s.setPassword("123");
    s.setName("omar ali");
    s.setAddress("cairo");
    s.setCurrentCreditHours(60);
    s.setGpa(3.44);
    s.setNationalID("30405060");
    s.setNationality("egyption");
    s.setStudyLvl(3);
    s.setTelephoneNumber("01014800479");

    Course c;
    c.setID("course#1");
    c.setCreditHours(4);
    c.setTitle("structure programing");
    c.setSyllabus("10 lectures");
    
    Course c2;
    c2.setCreditHours(3);
    c2.setID("course#2");
    c2.setSyllabus("9 lectures");
    c2.setTitle("intro to computer");

    Instructor i;
    i.ID = "instructor#1";
    i.department = "information system";
    i.name = "naglaa fathy";
    i.courseID = "course#2";

    Instructor i2;
    i2.ID = "instructor#2";
    i2.department = "basic science";
    i2.name = "salsabil amin";
    i2.courseID = "course#1";

    c.addPrerequisite(c2);
    c.addInstructor(i2);
    c2.addInstructor(i);
    s.registerCourse(c2);

    students.insert({ s.getID(), s });
    courses.insert({ c.getID(), c });
    courses.insert({ c2.getID(), c2 });

    students.at("2023170726").registerCourse(courses.at("course#1"));*/

    //test files

    /*for (auto it : students) {
        cout << "ID " << it.first << endl;
        cout << "name " << it.second.getName() << endl;
        cout << "passwor " << it.second.getPassword() << endl;
        cout << "gpa " << it.second.getGpa() << endl;
        cout << "tele " << it.second.getTelephoneNumber() << endl;

        cout << "courses.........\n";
        deque<Course> c = it.second.getRegisteredCourses();
        for (auto course : c) {
            cout << "course ID " << course.getID() << endl;
            cout << "course title " << course.getTitle() << endl;
            cout << "course hours " << course.getCreditHours() << endl;
            cout << "instructors........\n";
            for (auto ins : course.getInstructors()) {
                cout << "ID " << ins.ID << endl;
                cout << "name " << ins.name << endl;
                cout << "department " << ins.department << endl;
            }

            cout << "prerequisite......." << endl;
            for (auto pre : course.getPrerequisite()) {
                cout << "ID " << pre.getID() << endl;
                cout << "title " << pre.getTitle() << endl;
            }
        }
    }*/


    writeCourses(courses);
    writeInstructors(courses);
    writePrerequisites(courses);
    writeStudents(students);


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
    }

    string line;
    queue<string> data;
    Student student;

    getline(file, line); // to ignore header 

    while (getline(file, line)) {    
        data = split(line, ',');
        student.setID(data.front()), data.pop();
        student.setUsername(data.front()), data.pop();
        student.setPassword(encrypt(data.front(), 'M')), data.pop();
        student.setName(data.front()), data.pop();
        student.setNationality(data.front()), data.pop();
        student.setNationalID(data.front()), data.pop();
        student.setTelephoneNumber(data.front()), data.pop();
        student.setAddress(data.front()), data.pop();
        student.setGpa(stof(data.front())), data.pop();
        student.setStudyLvl(stoi(data.front())), data.pop();
        student.setCurrentCreditHours(stoi(data.front())), data.pop();
        students.insert({student.getID(), student});
        while(!data.empty()){  // get registered courses ids
            students.at(student.getID()).registerCourseInFiles(courses.at(data.front())), data.pop();
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

    file << "Student ID,Username,Password,Name,Nationality,National ID,Telephone Number,Address,GPA,Study Level,Total Credit Hours,Registered Courses IDs\n";  // Header
    
    deque<Course> registeredCourses;

    for (auto it : students) {
        file << it.first << ",";
        file << it.second.getUsername() << ",";
        file << encrypt(it.second.getPassword(), 'M') << ",";
        file << it.second.getName() << ",";
        file << it.second.getNationality() << ",";
        file << it.second.getNationalID() << ",";
        file << it.second.getTelephoneNumber() << ",";
        file << it.second.getAddress() << ",";
        file << it.second.getGpa() << ",";
        file << it.second.getStudyLvl() << ",";
        file << it.second.getCurrentCreditHours();
        registeredCourses = it.second.getRegisteredCourses();
        while (!registeredCourses.empty())
            file << "," << registeredCourses.front().getID(), registeredCourses.pop_front();
        file << endl;
    }

    file.close();
}

void readCourses(map<string,Course>& courses) {
    ifstream file ("courses.csv");
    if (!file) {
        cout << "Error opening courses file!" << endl;
    }

    string line;
    queue<string> data;
    Course course;

    getline(file, line);  // to ignore header

    while (getline(file, line)) {    
        data = split(line, ',');
        course.setID(data.front()), data.pop();
        course.setTitle(data.front()), data.pop();
        course.setSyllabus(data.front()), data.pop();
        course.setCreditHours(stoi(data.front())), data.pop();
        courses.insert({course.getID(), course});
    }

    readInstructors(courses);
    readPrerequisites(courses);

    file.close();
}

void writeCourses(map<string,Course> courses) {
    ofstream file("courses.csv");

    if (!file) {
        cout << "Error opening courses file!" << endl;
        return;
    }

    file << "Course ID,Title,Syllabus,Credit Hours,Instructor ID,Prerequisite ID\n";
    for (auto it : courses) {
        file << it.first << ",";
        file << it.second.getTitle() << ",";
        file << it.second.getSyllabus() << ",";
        file << it.second.getCreditHours();
        for (auto inst : it.second.getInstructors()) {
            file << "," << inst.ID;  
        }
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
        cout << "Error opening instructors file!" << endl;
    }

    string line;
    queue<string> data;
    Instructor instructor;

    getline(file, line); // to ignore header

    while (getline(file, line)) {    
        data = split(line, ',');
        instructor.ID = data.front(), data.pop();
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
        cout << "Error opening instructors file!" << endl;
        return;
    }

    file << "Instructor ID,Name,Department,Course ID\n";  // Header

    for (auto it : courses) {
        for(auto inst : it.second.getInstructors()){
            file << inst.ID << ",";
            file << inst.name << ",";
            file << inst.department << ",";
        }
        file << it.first << endl;
    }

    file.close();
}

void readPrerequisites(map<string,Course>& courses) {
    ifstream file ("prerequisites.csv"); 

    if (!file) {
        cout << "Error opening prerequisites file!" << endl;
    }

    string line;
    queue<string> data;
    string courseID;
    string preCourseID;

    getline(file, line);  // to ignore headred

    while (getline(file, line)) {    
        data = split(line, ',');
        courseID = data.front(), data.pop();
        while (!data.empty()) {
            preCourseID = data.front(), data.pop();
            courses.at(courseID).addPrerequisite(courses.at(preCourseID));
        }
    }

    file.close();
}

void writePrerequisites(map<string,Course> courses) {
    ofstream file("prerequisites.csv"); 

    if (!file) {
        cout << "Error opening prerequisites file!" << endl;
        return;
    }

    file << "Course ID,Prerequisite Courses IDs\n";  // Header

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
