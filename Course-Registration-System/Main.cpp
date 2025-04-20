#include <iostream>
#include <map>
#include <fstream>
#include "queue"
#include "stack"
#include <forward_list>
#include "Person.h"
#include "Admin.h"
#include "Course.h"
#include "Student.h"

using namespace std;

queue<string> split(string line, char ch);
void readStudents();
void readCourses();
void writeStudents();
void writeCourses();
string encrypt(const string& input, char key);

int main() {
    map<int,Student> students;
    map<int,Course> courses;

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

void readStudents(map<int,Student>& students) {
    ifstream file ("students.csv"); // Open file for reading

    if (!file) {
        cout << "Error opening students file!" << endl;
        return;
    }
    string line;
    queue<string> data;
    getline(file, line); // to ignore header
    while (getline(file, line)) {    
        data = split(line, ',');
        // assign data and pop from queue
    }

    file.close();
}

void readCourses(map<int,Course>& courses) {
    ifstream file ("fileName.csv"); // Open file for reading

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }
    string line;
    queue<string> data;
    getline(file, line); // to ignore header
    while (getline(file, line)) {    
        data = split(line, ',');
        // assign data and pop from queue
    }

    file.close();
}

void writeStudents(map<int,Student> students) {
    ofstream file("fileName.csv");

    if (!file) {
        cout << "Error opening students file!" << endl;
        return;
    }

    file << "Student ID,Username,Password,Name,Nationality,National ID,Telephone Number,Address,GPA,Study Level,Total Credit Hours,Course ID,Title,Syllabus,Credit Hours,Instructor ID,Instructor Name,Instructor Department,Prerequisites\n";  // Header
    
    stack<Course> registeredCourses;
    forward_list<Instructor> instructors;
    forward_list<Course> prerequisites;

    for (auto it : students) {
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
        while(!registeredCourses.empty()) {
             file << "," << registeredCourses.top().getID();
             file << "," << registeredCourses.top().getTitle();
             file << "," << registeredCourses.top().getSyllabus();
             file << "," << registeredCourses.top().getCreditHours();
            instructors = registeredCourses.top().getInstructors();
            for(auto inst : instructors){
                file << "," << inst.id;
                file << "," << inst.name;
                file << "," << inst.department;
            }
            
        }
    }

    file.close();
}

void writeCourses(map<int,Course> courses) {
    ofstream file("fileName.csv"); // Open file for writing

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    file << "Course ID,Title,Syllabus,Credit Hours,Instructors,Prerequisites\n";  // Header
    for (auto it : courses) {
        
    }
    file.close(); // Close the file
}

string encrypt(const string& input, char key) {
    string output = input;
    for (int i = 0; i < input.size(); i++){
        output[i] = input[i] ^ key;
    }
    return output;
}