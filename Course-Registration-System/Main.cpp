#include <iostream>
#include <map>
#include <fstream>
#include <queue>
#include <conio.h>
#include <string>
#include <forward_list>
#include "Admin.h"
#include "Student.h"
#include "Course.h"
#include "Handleable.h"
using namespace std;
map<string, Student> students;
map<string, Admin> admins;
unordered_map<string, Course> courses;
unordered_map<string, Instructor> instructors;
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
string readLine();
string encryptPassword(const string& password, int key);
string decryptPassword(const string& password, int key);
string getPassword();
bool mainMenu(int choice);
bool signUpAsStudent();
bool signUpAsAdmin();
pair<bool, map<string, Student>::iterator> loginAsStudent();
pair<bool, map<string, Admin>::iterator> loginAsAdmin();
int main() {
    bool access = true;
    readCourses();
    readStudents();
    readAdmins();
    auto menuChoice = [](int choice = 0) -> int {
        system("cls");
        cout << "Course Registration Management System\n------------------------------------\n";
        cout << "1: Sign Up.\n2: Login.\n3: Exit.\nYour Choice: ";
        choice = Handleable::handlingChoiceNotFound(3);
        return choice;
        };
    while (access)
        access = mainMenu(menuChoice());
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
        student.setTelephoneNumber("0" + data.front()), data.pop();
        student.setAddress(data.front()), data.pop();
        student.setGpa(stof(data.front())), data.pop();
        student.setStudyLvl(stoi(data.front())), data.pop();
        student.setMajor(data.front()), data.pop();
        student.setCurrentCreditHours(stoi(data.front())), data.pop();
        student.setTotatlCreditHours(stoi(data.front())), data.pop();

        if (!data.empty() && data.front() != "") {
            IDs = split(data.front(), '&'), data.pop();
            grades = split(data.front(), '&'), data.pop();
            while (!IDs.empty() && IDs.front() != "" &&
                !grades.empty() && grades.front() != "") {  // get registered courses IDs
                student.addCourseInFiles({ &courses[IDs.front()], grades.front() });
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

    file << "Student ID,Username,Password,Name,Nationality,National ID,Telephone Number,Address,GPA,Level,Major,Current Credit Hours,Total Credit Hours,Registered Courses IDs,Courses Grades\n";  // Header

    vector<pair<const Course*, string>> registeredCourses;
    string IDs;
    string grades;

    for (auto& it : students) {
        file << it.first << ",";
        file << it.second.getUsername() << ",";
        file << encryptPassword(it.second.getPassword(), 3) << ",";
        file << it.second.getName() << ",";
        file << it.second.getNationality() << ",";
        file << it.second.getNationalID() << ",";
        file << it.second.getTelephoneNumber().substr(1, it.second.getTelephoneNumber().length() - 1) << ",";
        file << it.second.getAddress() << ",";
        file << it.second.getGpa() << ",";
        file << it.second.getStudyLvl() << ",";
        file << it.second.getMajor() << ",";
        file << it.second.getCurrentCreditHours() << ",";
        file << it.second.getTotalCreditHours();

        registeredCourses = it.second.getRegisteredCourses();
        IDs = "";
        grades = "";

        for (const auto& c : registeredCourses) {
            IDs.append(c.first->getID());
            IDs.append("&");
            grades.append(c.second);
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
    queue<string> majors;

    getline(file, line);  // to ignore header

    while (getline(file, line)) {
        Course course;
        data = split(line, ',');
        course.setID(data.front()), data.pop();
        course.setTitle(data.front()), data.pop();
        course.setSyllabus(data.front()), data.pop();
        course.setCreditHours(stoi(data.front())), data.pop();
        course.setSemester(data.front() == "Fall" ? Fall : Spring), data.pop();
        if (!data.empty() && data.front() != "") {
            majors = split(data.front(), '&'), data.pop();
            while (!majors.empty() && majors.front() != "") {
                course.addMajor(majors.front());
                majors.pop();
            }
        }
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
    string majors;

    file << "Course ID,Title,Syllabus,Credit Hours,Semester,Required Major,Instructor ID,Prerequisite ID\n";

    for (auto& it : courses) {
        instructorsIDs = "";
        prerequisitesIDs = "";
        majors = "";
        file << it.first << ",";
        file << it.second.getTitle() << ",";
        file << it.second.getSyllabus() << ",";
        file << it.second.getCreditHours() << ",";
        file << (it.second.getSemester() == Fall ? "Fall" : "Spring");
        for (auto& major : it.second.getReqMajors()) {
            majors.append(major);
            majors.append("&");
        }
        if (!it.second.getReqMajors().empty()) {
            file << "," << majors.substr(0, majors.length() - 1);
        }

        for (auto& inst : it.second.getInstructors()) {
            instructorsIDs.append(inst->ID);
            instructorsIDs.append("&");
        }
        if (!it.second.getInstructors().empty()) {
            file << "," << instructorsIDs.substr(0, instructorsIDs.length() - 1);
        }

        for (auto& pre : it.second.getPrerequisite()) {
            prerequisitesIDs.append(pre->getID());
            prerequisitesIDs.append("&");
        }
        if (!it.second.getPrerequisite().empty())
            file << "," << prerequisitesIDs.substr(0, prerequisitesIDs.length() - 1);

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
    queue<string> courseIDs;

    getline(file, line); // to ignore header

    while (getline(file, line)) {
        Instructor instructor;
        data = split(line, ',');
        instructor.ID = data.front(), data.pop();
        instructor.name = data.front(), data.pop();
        instructor.department = data.front(), data.pop();
        courseIDs = split(data.front(), '&'), data.pop();
        while (!courseIDs.empty() && courseIDs.front() != "") {
            instructor.courseIDs.push_back(courseIDs.front());
            courseIDs.pop();
        }
        instructors.insert({instructor.ID, instructor});
    }

    for (auto& it : instructors) {
        for (auto& ID : it.second.courseIDs) {
            courses[ID].addInstructor(&it.second);
    }
        }

    file.close();
}

void writeInstructors() {
    ofstream file("instructors.csv");

    if (!file) {
        cout << "Error opening instructors file!" << endl;
        return;
    }

    string courseIDs;
    file << "Instructor ID,Name,Department,Course ID\n";  // Header

    for (auto& it : instructors) {
        file << it.first << ",";
        file << it.second.name << ",";
        file << it.second.department;
        courseIDs = "";
        for (auto& courseID : it.second.courseIDs) {
            courseIDs.append(courseID);
            courseIDs.append("&");
        }

        if (!it.second.courseIDs.empty())
            file << "," << courseIDs.substr(0, courseIDs.size() - 1);
        file << endl;
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
                courses[courseID].addPrerequisite(&courses[preCourseID]);
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
            IDs.append(pre->getID());
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

string getPassword() {
    string password;
    char ch;
    while (true) {
        ch = _getch();
        if (ch == 13) { // Enter Buttom
            if (!password.empty()) {
                cout << endl;
                break;
            }
        }
        else if (ch == 8 && !password.empty()) { // Delete Buttom
            cout << "\b \b";
            password.pop_back();
        }
        else {
            password.push_back(ch);
            cout << "*";
        }
    }
    return password;
}

string readLine() {
    string text;
    getline(cin, text);
    return text;
}

bool mainMenu(int choice) {
    system("cls");
    cout << "------------------------------------------";
    int counter = 0;
    bool loggedIn = false, signedUp = false, flag = false;

    if (choice == 1) {
        cout << "\n1: Sign Up As a Student.\n2: Sign Up As an Admin.\n3: Exit.\n\nYour Choice: ";
        choice = Handleable::handlingChoiceNotFound(3);
        cin.ignore();

        if (choice == 1) {
            while (!signedUp) {
                if (counter > 2) {
                    flag = true;
                    break;
                }
                ++counter;
                signedUp = signUpAsStudent();
            }

            if (flag) {
                return 1;
            }
            cout << "Signed Up Is Done!" << endl;
            return 1;
        }

        else if (choice == 2) {
            while (!signedUp) {
                if (counter > 2) {
                    flag = true;
                    break;
                }
                ++counter;
                signedUp = signUpAsAdmin();
            }

            if (flag) {
                return 1;
            }
            cout << "Signed Up Is Done!" << endl;
            return 1;
        }
    }

    else if (choice == 2) {
        cout << "\n1: Login As a Student.\n2: Login As an Admin.\n3: Exit.\n\nYour Choice: ";
        choice = Handleable::handlingChoiceNotFound(3);
        cin.ignore();
        if (choice == 1) {
            pair<bool, map<string, Student>::iterator> student;
            while (!loggedIn) {
                if (counter > 2) {
                    flag = true;
                    break;
                }
                ++counter;
                student = loginAsStudent();
                loggedIn = student.first;
            }

            if (flag) {
                return 1;
            }
            student.second->second.menu(courses);
            cout << "Logged In Is Done!" << endl;
            return 0;
        }

        else if (choice == 2) {
            pair<bool, map<string, Admin>::iterator> admin;
            while (!loggedIn) {
                if (counter > 2) {
                    flag = true;
                    break;
                }

                ++counter;
                admin = loginAsAdmin();
                loggedIn = admin.first;
            }

            if (flag) {
                return 1;
            }
            admin.second->second.menu(students, courses, instructors);
            cout << "Logged In Is Done!" << endl;
            return 0;
        }
    }
    return 0;
}

bool signUpAsStudent() {
    string name, password, nationalID, telephoneNumber, address, nationality, ID, username;
    bool isUnique = true;

    cout << "Enter Your Name: ";
    name = Handleable::emptyString(readLine(), "Name");
    cout << "Enter Your Password: ";
    password = getPassword();
    cout << "Enter Your National ID: ";
    nationalID = Handleable::emptyString(readLine(), "National ID");
    cout << "Enter Your Telephone Number: ";
    telephoneNumber = Handleable::emptyString(readLine(), "Telephone Number");
    cout << "Enter Your Address: ";
    address = Handleable::emptyString(readLine(), "Address");
    cout << "Enter Your Nationality: ";
    nationality = Handleable::emptyString(readLine(), "Nationality");

    for (auto& temp : students) {
        if (temp.second.getNationalID() == nationalID || temp.second.getTelephoneNumber() == telephoneNumber) {
            isUnique = false;
            break;
        }
    }

    if (!isUnique) {
        cout << "Data is already exists, Try Again!" << endl;
        return false;
    }

    ID = to_string(stoi(students.rbegin()->first) + 1);
    Student student(ID, ID + "@cis.asu.edu.eg", password, name, nationalID, telephoneNumber, address, nationality, 0.0, 1, 21);
    students.emplace_hint(students.end(), student.getID(), student);
    return true;
}

bool signUpAsAdmin() {
    string username, password;

    cout << "Enter Your Username: ";
    username = Handleable::emptyString(readLine(), "Username");
    cout << "Enter Your Password: ";
    password = getPassword();

    bool isUnique = (admins.find(username) == admins.end());

    if (!isUnique) {
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
    ID = Handleable::emptyString(readLine(), "ID");
    cout << "Enter Your National ID: ";
    nationalID = Handleable::emptyString(readLine(), "National ID");
    cout << "Enter Your Password: ";
    password = getPassword();

    auto isValid = [&]() -> pair<bool, map<string, Student>::iterator> {
        map<string, Student>::iterator temp = students.find(ID);
        return {
            temp != students.end() &&
            temp->second.getPassword() == password &&
            temp->second.getNationalID() == nationalID, temp
        };
        };

    auto user = isValid();
    if (!user.first) {
        cout << "Invalid ID, National ID, or Password, Try Again!" << endl;
    }
    return user;
}

pair<bool, map<string, Admin>::iterator> loginAsAdmin() {
    string username, password;

    cout << "Enter Your Username: ";
    username = Handleable::emptyString(readLine(), "Username");
    cout << "Enter Your Password: ";
    password = getPassword();

    auto isValid = [&]() -> pair<bool, map<string, Admin>::iterator> {
        map<string, Admin>::iterator temp = admins.find(username);
        return temp != admins.end() && temp->second.getPassword() == password ? make_pair(true, temp) : make_pair(false, temp);
        };

    auto user = isValid();
    if (!user.first) {
        cout << "Invalid ID or Password, Try Again!" << endl;
    }
    return user;
}