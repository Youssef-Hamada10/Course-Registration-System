#include <iostream>
#include <map>
#include <fstream>
#include <queue>
#include <deque>
#include <string>
#include <forward_list>
#include "Admin.h"
#include "Student.h"
#include "Course.h"

using namespace std;

map<string, Student> students;
map<string, Admin> admins;
map<string, Course> courses;

queue<string> split(string line, char ch);
void readStudents();
void readAdmins();
void readCourses();
void readInstructors();
void readPrerequisites();
void writeStudents();
void writeAdmins();
void writeCourses();
void writeInstructors();
void writePrerequisites();
string encryptPassword(const string& password, int key);
string decryptPassword(const string& password, int key);
bool mainMenu(int choice);
bool signUpAsStudent();
bool signUpAsAdmin();
bool isUniqueInfo(string nationalID, string telephoneNumber);
pair<bool, map<string, Student>::iterator> loginAsStudent();
pair<bool, map<string, Student>::iterator> isValidInfoAsStudent(string ID, string password, string nationalID);
pair<bool, map<string, Admin>::iterator> loginAsAdmin();
void studentMenu();
void adminMenu();

int main() {
    bool flag;
    readCourses();
    readStudents();
    readAdmins();
    
    do {
        flag = false;
        auto menuChoice = [](int choice = 0) -> int {
            cout << "Course Registration Management System\n------------------------------------\n";
            cout << "1: Sign Up.\n2: Login.\n3: Exit.\nYour Choice: ";
            cin >> choice;
            return choice;
        };
        flag = mainMenu(menuChoice());
    } while (flag);

    for (auto& it : students) {
        cout << "stu: " << it.second.getPassword() << endl;
    }
    cout << "Thanks For Using Our System :)" << endl;
    writeCourses();
    writeInstructors();
    writePrerequisites();
    writeStudents();
    writeAdmins();
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

void readStudents() {
    ifstream file("students.csv");

    if (!file) {
        cout << "Error opening students file!" << endl;
    }

    string line;
    queue<string> data;
    queue<string> IDs;
    queue<string> grades;

    getline(file, line); // to ignore header 
    while (getline(file, line)) {
        Student student;
        data = split(line, ',');
        student.setID(data.front()), data.pop();
        student.setUsername(data.front()), data.pop();
        student.setPassword(decryptPassword(data.front(), 3)), data.pop();
        student.setName(data.front()), data.pop();
        student.setNationality(data.front()), data.pop();
        student.setNationalID(data.front()), data.pop();
        student.setTelephoneNumber(data.front().insert(0, "0")), data.pop();
        student.setAddress(data.front()), data.pop();
        student.setGpa(stof(data.front())), data.pop();
        student.setStudyLvl(stoi(data.front())), data.pop();
        student.setCurrentCreditHours(stoi(data.front())), data.pop();
        student.setTotatlCreditHours(stoi(data.front())), data.pop();

        if (!data.empty() && data.front() != "") {
            IDs = split(data.front(), '&'), data.pop();
            grades = split(data.front(), '&'), data.pop();
            while (!IDs.empty() && IDs.front() != "" &&
                !grades.empty() && grades.front() != "") {  // get registered courses IDs
                student.registerCourseInFiles({ courses[IDs.front()], grades.front()});
                IDs.pop(), grades.pop();
            }
        }

        students.insert({ student.getID(), student });
    }
    file.close();
}

void writeStudents() {
    ofstream file("students.csv");

    if (!file) {
        cout << "Error opening students file!" << endl;
    }

    file << "Student ID,Username,Password,Name,Nationality,National ID,Telephone Number,Address,GPA,Study Level,Current Credit Hours,Total Credit Hours,Registered Courses IDs,Courses Grades\n";  // Header

    deque<pair<Course, string>> registeredCourses;
    string IDs;
    string grades;

    for (auto& it : students) {
        file << it.first << ",";
        file << it.second.getUsername() << ",";
        file << encryptPassword(it.second.getPassword(), 3) << ",";
        file << it.second.getName() << ",";
        file << it.second.getNationality() << ",";
        file << it.second.getNationalID() << ",";
        file << it.second.getTelephoneNumber() << ",";
        file << it.second.getAddress() << ",";
        file << it.second.getGpa() << ",";
        file << it.second.getStudyLvl() << ",";
        file << it.second.getCurrentCreditHours() << ",";
        file << it.second.getTotalCreditHours();

        registeredCourses = it.second.getRegisteredCourses();
        IDs = "";
        grades = "";

        for (auto c = registeredCourses.begin(); c != registeredCourses.end(); ++c) {
            IDs.append(c->first.getID());
            IDs.append("&");
            grades.append(c->second);
            grades.append("&");
        }

        if (!it.second.getRegisteredCourses().empty()) {
            file << "," << IDs.substr(0, IDs.size() - 1);
            file << "," << grades.substr(0, grades.size() - 1);
        }
        file << endl;
    }
    file.close();
}

void readAdmins() {
    ifstream file("admins.csv");

    if (!file) {
        cout << "Error opening students file!" << endl;
    }
    string line;
    queue<string> data;
    Admin admin;

    getline(file, line);
    while (getline(file, line)) {
        data = split(line, ',');
        admin.setID(data.front()), data.pop();
        admin.setUsername(data.front()), data.pop();
        admin.setPassword(data.front()), data.pop();
        admins.insert({ admin.getUsername(), admin });
        ++Admin::numberOfIDs;
    }

    file.close();
}

void writeAdmins() {
    ofstream file("admins.csv");

    if (!file) {
        cout << "Error opening students file!" << endl;
    }

    file << "Admin ID, Username, Password\n";

    for (auto& it : admins) {
        file << it.second.getID() << ",";
        file << it.second.getUsername() << ",";
        file << it.second.getPassword();
        file << endl;
    }
    file.close();
}

void readCourses() {
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
        course.setID(data.front()), data.pop();
        course.setTitle(data.front()), data.pop();
        course.setSyllabus(data.front()), data.pop();
        course.setCreditHours(stoi(data.front())), data.pop();
        course.setSemester(data.front() == "Fall" ? Fall : Spring), data.pop();
        courses.insert({ course.getID(), course });
    }
    readInstructors();
    readPrerequisites();

    file.close();
}

void writeCourses() {
    ofstream file("courses.csv");

    if (!file) {
        cout << "Error opening courses file!" << endl;
        return;
    }

    string instructorsIDs;
    string prerequisitesIDs;

    file << "Course ID,Title,Syllabus,Credit Hours,Semester,Instructor ID,Prerequisite ID\n";

    for (auto& it : courses) {
        instructorsIDs = "";
        prerequisitesIDs = "";
        file << it.first << ",";
        file << it.second.getTitle() << ",";
        file << it.second.getSyllabus() << ",";
        file << it.second.getCreditHours() << ",";
        file << (it.second.getSemester() == Fall ? "Fall" : "Spring");

        for (auto& inst : it.second.getInstructors()) {
            instructorsIDs.append(inst.ID);
            instructorsIDs.append("&");
        }
        file << "," << instructorsIDs.substr(0, instructorsIDs.size() - 1);

        for (auto& pre : it.second.getPrerequisite()) {
            prerequisitesIDs.append(pre.getID());
            prerequisitesIDs.append("&");
        }
        if (!it.second.getPrerequisite().empty())
            file << "," << prerequisitesIDs.substr(0, prerequisitesIDs.size() - 1);

        file << endl;
    }
    file.close();
}

void readInstructors() {
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
        instructor.ID = data.front(), data.pop();
        instructor.name = data.front(), data.pop();
        instructor.department = data.front(), data.pop();
        instructor.courseID = data.front(), data.pop();

        if(instructor.courseID != "")
            courses[instructor.courseID].addInstructor(instructor);
    }
    file.close();
}

void writeInstructors() {
    ofstream file("instructors.csv");

    if (!file) {
        cout << "Error opening instructors file!" << endl;
        return;
    }

    file << "Instructor ID,Name,Department,Course ID\n";  // Header

    for (auto& it : courses) {
        for (auto& inst : it.second.getInstructors()) {
            file << inst.ID << ",";
            file << inst.name << ",";
            file << inst.department << ",";
            file << it.first << endl;
        }
    }

    file.close();
}

void readPrerequisites() {
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

void writePrerequisites() {
    ofstream file("prerequisites.csv");

    if (!file) {
        cout << "Error opening prerequisites file!" << endl;
        return;
    }

    string IDs;

    file << "Course ID,Prerequisite Courses IDs\n";  // Header

    for (auto& it : courses) {
        file << it.first;
        IDs = "";
        for (auto& pre : it.second.getPrerequisite()) {
            IDs.append(pre.getID());
            IDs.append("&");
        }

        if (!it.second.getPrerequisite().empty())
            file << "," << IDs.substr(0, IDs.size() - 1);

        file << endl;
    }

    file.close();
}

string encryptPassword(const string& password, int key) {
    std::string encryptedPassword = "";
    for (char c : password) {
        encryptedPassword += static_cast<char>(c + key);
    }
    return encryptedPassword;
}

// Decrypt function
string decryptPassword(const string& encryptedPassword, int key) {
    std::string decryptedPassword = "";
    for (char c : encryptedPassword) {
        decryptedPassword += static_cast<char>(c - key);
    }
    return decryptedPassword;
}

bool mainMenu(int choice) {
    int counter = 0;
    bool loggedIn = false, signedUp = false, flag = false;

    if (choice == 1) {
        cout << "1: Sign Up As a Student.\n2: Sign Up As an Admin.\n3: Exit.\nYour Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            while (!signedUp) {
                ++counter;
                signedUp = signUpAsStudent();
                if (counter > 2) {
                    flag = true;
                    break;
                }
            }

            if (flag) {
                return 1;
            }
            cout << "Signed Up Is Done!" << endl;
        }

        else if (choice == 2) {

            while (!signedUp) {
                ++counter;
                signedUp = signUpAsAdmin();
                if (counter > 2) {
                    flag = true;
                    break;
                }
            }

            if (flag) {
                return 1;
            }
            cout << "Signed Up Is Done!" << endl;
        }
    }

    else if (choice == 2) {
        cout << "1: Login As a Student.\n2: Login As an Admin.\n3: Exit.\nYour Choice: ";
        cin >> choice;

        cin.ignore();
        if (choice == 1) {
            pair<bool, map<string, Student>::iterator> student;
            while (!loggedIn) {
                ++counter;
                student = loginAsStudent();
                loggedIn = student.first;

                if (counter > 2) {
                    flag = true;
                    break;
                }
            }

            if (flag) {
                return 1;
            }
            cout << "Logged In Is Done!" << endl;
        }

        else if (choice == 2) {
            pair<bool, map<string, Admin>::iterator> admin;
            while (!loggedIn) {
                ++counter;
                admin = loginAsAdmin();
                loggedIn = admin.first;

                if (counter > 2) {
                    flag = true;
                    break;
                }
            }

            if (flag) {
                return 1;
            }
            cout << "Logged In Is Done!" << endl;
        }
    }
    return 0;
}

bool signUpAsStudent() {
    string name, password, nationalID, telephoneNumber, address, nationality, ID, username;

    cout << "Enter Your Name: ";
    getline(cin, name);
    cout << "Enter Your Password: ";
    getline(cin, password);
    cout << "Enter Your National ID: ";
    getline(cin, nationalID);
    cout << "Enter Your Telephone Number: ";
    getline(cin, telephoneNumber);
    cout << "Enter Your Address: ";
    getline(cin, address);
    cout << "Enter Your Nationality: ";
    getline(cin, nationality);

    if (!isUniqueInfo(nationalID, telephoneNumber)) {
        cout << "Data is already exists, Try Again!" << endl;
        return false;
    }

    ID = to_string(stoi(students.rbegin()->first) + 1);
    Student student(ID, ID + "@cis.asu.edu.eg", password, name, nationalID, telephoneNumber, address, nationality, 0.0, 1, 19);

    students.emplace_hint(students.end(), student.getID(), student);
    return true;
}

bool isUniqueInfo(string nationalID, string telephoneNumber) {
    map<string, Student>::iterator temp = students.begin();
    for (temp; temp != students.end(); ++temp) {
        if (temp->second.getNationalID() == nationalID || temp->second.getTelephoneNumber() == telephoneNumber) {
            return false;
        }
    }
    return true;
}

bool signUpAsAdmin() {
    string username, password;

    cout << "Enter Your Username: ";
    getline(cin, username);
    cout << "Enter Your Password: ";
    getline(cin, password);

    auto isValid = [](string username) {
        map<string, Admin>::iterator temp = admins.find(username);
        return temp == admins.end();
    };

    if (!isValid(username)) {
        cout << "Data is already exists, Try Again!" << endl;
        return false;
    }

    Admin admin(username, password);
    admins.insert({ username, admin });
    return true;
}

pair<bool, map<string, Student>::iterator> loginAsStudent() {
    string ID, nationalID, password;

    cout << "Enter Your ID: ";
    getline(cin, ID);
    cout << "Enter Your National ID: ";
    getline(cin, nationalID);
    cout << "Enter Your Password: ";
    getline(cin, password);

    auto user = isValidInfoAsStudent(ID, password, nationalID);
    if (!user.first) {
        cout << "Invalid ID, National ID, or Password, Try Again!" << endl;
    }
    return user;
}

pair<bool, map<string, Student>::iterator> isValidInfoAsStudent(string ID, string password, string nationalID) {
    map<string, Student>::iterator temp = students.find(ID);
    return {
        temp != students.end() &&
        temp->second.getPassword() == password &&
        temp->second.getNationalID() == nationalID, temp
    };
}

pair<bool, map<string, Admin>::iterator> loginAsAdmin() {
    string username, password;

    cout << "Enter Your Username: ";
    getline(cin, username);
    cout << "Enter Your Password: ";
    getline(cin, password);

    auto isValid = [](string username, string password) -> pair<bool, map<string, Admin>::iterator> {
        map<string, Admin>::iterator temp = admins.find(username);
        return temp != admins.end() && temp->second.getPassword() == password ? make_pair(true, temp) : make_pair(false, temp);
    };

    auto user = isValid(username, password);
    if (!user.first) {
        cout << "Invalid ID or Password, Try Again!" << endl;
    }
    return user;
}

void studentMenu() {
}

void adminMenu() {
}
