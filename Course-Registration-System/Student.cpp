#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include "Student.h"
#include "Handleable.h"
#include <fstream>
#include <conio.h>
#include <windows.h>
#include "Admin.h"
#include <unordered_set>
using namespace std;

unordered_map<string, float> grade = {
    {"A+", 4.0f}, {"A", 4.0f}, {"A-", 3.7f},
    {"B+", 3.3f}, {"B", 3.0f}, {"B-", 2.7f},
    {"C+", 2.3f}, {"C", 2.0f}, {"C-", 1.7f},
    {"D+", 1.4f}, {"D", 1.0f}, {"F", 0.0f}
};

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
    this->major = "General";
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
    this->major = other.major;
}

Student::Student() {
    level = 1;
    gpa = 0.0;
    currentCreditHours = 0;
    totalCreditHours = 0;
    major = "General";
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

string Student::getMajor() {
    return major;
}

void Student::setMajor(string major) {
    this->major = major;
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

vector<pair<const Course*, string>>& Student::getRegisteredCourses() {
    return registeredCourses;
}

void Student::addCourseInFiles(pair<Course*, string> course) {
    this->registeredCourses.push_back(course);
}

void Student::menu(const unordered_map<string, Course>& courses) {
    int choice;
    do {
    system("cls");
    cout << "Welcome " << name << endl;
    cout << string(18, '-')<<endl;
        cout << "\n1 : Display Info.\n2 : Register A Course.\n3 : View Grades.\n4 : Check Prerequisites For A Course.\n5 : Search For A Course.\n6 : Make A Report.\n7 : Log Out\n\n\nYour Choice:";
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
        }
    } while (true);
}

void Student::displayInfo() {
    system("cls");
    cout << "Personal Information:\n";
    cout << string(77, '=') << endl;
    cout << "1  : Name:- " << left << setw(37) << name << "2  : ID:- " << ID << endl;
    cout << "3  : Username:- " << left << setw(33) << username << "4  : Password:- " << password << endl;
    cout << "5  : National ID:- " << left << setw(30) << nationalID << "6  : Telephone Number:- " << telephoneNumber << endl;
    cout << "7  : Address: " << left << setw(35) << address << "8  : Nationality:- " << nationality << endl;
    cout << "9  : Level:- " << left << setw(36) << level << "10 : Major:- " << major << endl;
    cout << "11 : Total Credit Hours:- " << totalCreditHours << endl;
    cout << string(77, '=') << endl;
    cout << "\npress any key to continue: ";
    _getch();
}

int Student::getMaxCreditHours() {
    if (this->gpa >= 3.0 || this->gpa == 0.0)
        return 21;
    else if (this->gpa >= 2.0)
        return 18;
    else return 15;
}

bool Student::editInfo(int choice) {
    bool flag = false;
    string value = "";
    auto read = [&]() -> string {
        getline(cin, value);
        return value;
    };

    string old = "";

    switch (choice) {
        case 1:
        {
            do {
                cout << "Enter New Name: ";
                value = Handleable::handlingMinInputs(Handleable::emptyString(read(), "Name"), 9);
            } while (Handleable::trim(value).empty());

            cout << "Are You Sure To Change The Name From " << this->name << " To " << value << " (Y || N): ";
            if (Handleable::toContinue()) {
                this->name = value;
            }
            flag = true;
        }
        break;

        case 4:
        {
            do {
                cout << "Enter New Passowrd: ";
                value = Handleable::handlingMinInputs(Handleable::emptyString(read(), "Password"), 8);
            } while (Handleable::trim(value).empty());

            cout << "Are You Sure To Change The Password From " << this->password << " To " << value << " (Y || N): ";
            if (Handleable::toContinue()) {
                this->password = value;
            }
            flag = true;
        }
        break;

        case 5:
        {
            do {
                cout << "Enter New National ID: ";
                value = Handleable::handlingMinInputs(Handleable::emptyString(read(), "National ID"), 8);
            } while (Handleable::trim(value).empty());
        
            cout << "Are You Sure To Change The National ID From " << this->nationalID << " To " << value << " (Y || N): ";
            if (Handleable::toContinue()) {
                this->nationalID = value;
            }
            flag = true;
        }
        break;

        case 6:
        {
            do {
                cout << "Enter New Telephone Number: ";
                value = Handleable::handlingNumbers(Handleable::emptyString(read(), "Telephone Number"), "National ID");
            } while (Handleable::trim(value).empty());
        
            cout << "Are You Sure To Change The Telephone NUmber From " << this->telephoneNumber << " To " << value << " (Y || N): ";
            if (Handleable::toContinue()) {
                this->telephoneNumber = value;
            }
            flag = true;
        }
        break;

        case 7:
        {
            do {
                cout << "Enter New Address: ";
                value = Handleable::handlingMinInputs(Handleable::emptyString(read(), "Address"), 4);
            } while (Handleable::trim(value).empty());
        
            cout << "Are You Sure To Change The Address From " << this->address << " To " << value << " (Y || N): ";
            if (Handleable::toContinue()) {
                this->address = value;
            }
            flag = true;
        }
        break;

        case 8:
        {
            do {
                cout << "Enter New Nationality: ";
                value = Handleable::handlingMinInputs(Handleable::emptyString(read(), "Nationality"), 4);
            } while (Handleable::trim(value).empty());

            cout << "Are You Sure To Change The Nationality From " << this->nationality << " To " << value << " (Y || N): ";
            if (Handleable::toContinue()) {
                this->nationality = value;
            }
            flag = true;
        }
        break;

        case 12:
        {
            cout << "\nExit (Y || N) ?";
            if (Handleable::toContinue()) {
                return true;
            }
        }
        break;

        default:
            return false;
    }
    
    if (flag) {
        cout << "\nDone!\n";
        return true;
    }
    return false;
}

void Student::registerCourse(const unordered_map<string,Course>&courses)
{
    do {
        system("cls");
        string id = "";
        displayAvailableCourses(courses);
        cout << "Enter Course ID: ";
        id = Handleable::emptyString([&]() -> string { getline(cin, id); return id; }(), "ID");
        auto course = courses.find(id);

        if (course == courses.end() || course->second.getSemester() != Admin::currentSemester)
        {
            cout << "\nRegistration failed: Course not found or not Available this semester\n";
            break;
        }

        if (!checkDepartment(course->second.getReqMajors())) {
            cout << "\nRegistration failed: Course is not Avaliable for this department\n";
            break;
        }

        system("cls");
        course->second.displayCourseInfo();
        cout << "\nAre you sure you want to register " << course->second.getTitle() << " ?\n";
        char choice = Handleable::toContinue();
        if (!choice)
        {
            return;
        }

        if (!checkRegisteredCourses(&(course->second))) {
            cout << "\nRegistration failed: Course already registerثd\n";
            break;
        }

        if (this->currentCreditHours + course->second.getCreditHours() > getMaxCreditHours()) {
            cout << "\nRegistration failed: Credit hour limit exceeded\n";
            break;
        }

        if (!checkPrerequisites(&(course->second))) {
            cout << "\nRegistration failed: Prerequisite For This Course Not Completed\n";
            break;
        }

        this->totalCreditHours += course->second.getCreditHours();
        this->currentCreditHours += course->second.getCreditHours();
        registeredCourses.push_back({ &(course->second),"N.A" });
        cout << "Course registered successfully\n";
        cout << "\nDo you want to register another course ?\n";
        choice = Handleable::toContinue();

        if (!choice)
        {
            return;
        }
    } while (true);
    cout << "\nPress any key to continue: ";
    _getch();
}

void Student::displayAvailableCourses(const unordered_map<string, Course>& courses)
{

    cout << left << setw(10) << "ID" << setw(40) << "Course Title" << "Credit Hours" << endl;
    cout << string(65,'=')<<endl; 
    for (const auto& course : courses)
    {
        if (course.second.getSemester() != Admin::currentSemester) continue;
        if (checkDepartment(course.second.getReqMajors())) {
            cout << left << setw(10) << course.first
                << setw(45) << course.second.getTitle()
                << course.second.getCreditHours() << endl;
        }
    }
    cout << string(65,'=')<<endl;
}

bool Student::checkDepartment(const vector<string>&majors) {
    for (const string& major :majors)
    {
        if (major == this->major || major == "General") return true;
    }
    return false;
}

bool Student::checkRegisteredCourses(const Course* course)
{
    for (const auto& registeredCourse:registeredCourses)
    {
        if (registeredCourse.first == course && registeredCourse.second != "N.A") {
            return false;
        }
    }
     return true;
}

void Student::displayGrades() {
    system("cls");
    if (registeredCourses.empty()) {
        cout << "No Grades To View\n";
        return;
    }
    cout << left << setw(10) << "ID" << setw(40) << "Course Title" << setw(12) << "Semester" << setw(5) << "Grade\n";
    cout <<string(70,'=') << endl;
    for (const auto& course : registeredCourses) {
        cout << left << setw(10) << course.first->getID() << setw(40) << course.first->getTitle() << setw(12) << (course.first->getSemester() ? "Spring" : "Fall") << setw(5) << course.second << endl;
    }
    cout << string(70, '=') << endl;
    cout << "\npress any key to continue: ";
    _getch();
}

bool Student::checkPrerequisites(const Course* course) {
    const vector<const Course*>& prequisites = course->getPrerequisite();
    if (prequisites.empty()) {
        return true;
    }
    for (const auto& preq : prequisites) {
        bool found = false;
        for (const auto& regCourse : registeredCourses) {
            if (regCourse.first == preq) {
                if (regCourse.second != "F" && regCourse.second != "N.A") {
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

void Student::displayPrerequisite(const unordered_map<string, Course>& courses) {
    char choice;
    do 
    {
        system("cls");
        cout << string(43, '-')<<endl;
        cout << "\n1 : Search Prequisite for Specific Course\n2 : Check Prequisite for all Courses \n3 : Return Menu\n\n\nYour Choice:";
        choice = Handleable::handlingChoiceNotFound(3);
        cin.ignore();
        switch (choice) {
        case 1:
            searchCourse(courses);
            break;
        case 2:
            displayAllPrerequisite(courses);
            break;
        case 3:
            return;
        }
    } while (true);
}

void Student::displayAllPrerequisite(const unordered_map<string, Course>& courses) {
    system("cls");
    for (const auto& course : courses) {
        if (checkDepartment(course.second.getReqMajors()))
        {
            course.second.displayCourseInfo();
            Sleep(500);
        }
    }
    cout << "\npress any key to continue :";
    _getch();
}

void Student::searchCourse(const unordered_map<string, Course>& courses) {
    system("cls");
    cout << string(43, '-');
    string id = "";
    cout << "\nEnter Course ID: ";
    id = Handleable::emptyString([&]() -> string { getline(cin, id); return id; }(), "ID" );
    auto course = courses.find(id);
    if (course == courses.end()) {
        cout << "\nCourse Does Not Exist\n";
        cout << "\npress any key to continue :";
        _getch();
        return;
    }
    system("cls");
    course->second.displayCourseInfo();
    cout << "\npress any key to continue :";
    _getch();
}

void Student::report() {
    system("cls");
    int lvlcounter = 1;
    cout << string(43, '-') << endl;
    string htmlFilename = this->name + "_report.html";
    string pdfFilename = this->name + "_report.pdf";
    ofstream htmlFile(htmlFilename);
    if (!htmlFile.is_open()) {
        cout << "Error while Creating HTML file\n";
        cout << "\npress any key to continue: ";
        _getch();
        return;
    }    
    htmlFile << "<html>\n";
    htmlFile << "<head>\n";
    htmlFile << "<title>Student Report</title>\n";
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
    htmlFile << "<p><strong>Name:</strong> " << this->name << "</p>\n";
    htmlFile << "<p><strong>ID:</strong> " << this->ID << "</p>\n";
    htmlFile << "<p><strong>Level:</strong> " << this->level << "</p>\n";
    htmlFile << "<p><strong>Department :</strong> " << this->major << "</p>\n";
    htmlFile << "<h2>Level: " << lvlcounter << "</h2>\n";
    int semesterCount = 0;
    string currentSemester = "";
    string previousSemester = "";
    bool isTableOpen = false;


    for (const auto& course : registeredCourses) {
        currentSemester = course.first->getSemester() ? "Spring" : "Fall";

        if (currentSemester != previousSemester) {
            if (isTableOpen) {
                htmlFile << "</table>\n";
            }

            if (semesterCount > 0 && semesterCount % 2 == 0) {
                ++lvlcounter;
                htmlFile << "<div style='page-break-after: always;'></div>\n";
                htmlFile << "<h2>Level " << lvlcounter << "</h2>\n";
            }
            htmlFile << "<div style='margin-top: 50px;'></div>\n";
            htmlFile << "<h2>" << currentSemester << " Semester</h2>\n";
            htmlFile << "<table>\n";
            htmlFile << "<tr><th>Course ID</th><th>Title</th><th>Credit Hours</th><th>Grade</th></tr>\n";

            isTableOpen = true;
            previousSemester = currentSemester;
            semesterCount++;
        }

        htmlFile << "<tr>\n";
        htmlFile << "<td>" << course.first->getID() << "</td>\n";
        htmlFile << "<td>" << course.first->getTitle() << "</td>\n";
        htmlFile << "<td>" << course.first->getCreditHours() << "</td>\n";
        htmlFile << "<td>" << course.second << "</td>\n";
        htmlFile << "</tr>\n";
    }

    if (isTableOpen) {
        htmlFile << "</table>\n";
    }
    htmlFile << "<p style='font-size: 18px;'><strong>CGPA:</strong> " << this->gpa << "</p>\n";
    htmlFile << "</body>\n";
    htmlFile << "</html>\n";
    htmlFile.close();
    string command = "wkhtmltopdf \"" + htmlFilename + "\" \"" + pdfFilename;
    system(command.c_str());
    cout << "PDF report created successully\n";
    remove(htmlFilename.c_str());
    cout << "\npress any key to continue: ";
    _getch();
}

void Student::updateGPA() {
    if (registeredCourses.empty() || totalCreditHours == 0) {
        this->gpa = 0.0f;
        return;
    }
    
    float gpaSum = 0.0f;
    int validCreditHours = 0;//to divide on the right number not on the total credit which may contain registered course without grade
    int creditHours = 0;

    unordered_set<string> validSubs;

    for (auto courseIt = registeredCourses.crbegin(); courseIt != registeredCourses.crend(); ++courseIt) {
        auto it = grade.find(courseIt->second);
        
        if (it != grade.end()) {
            auto it2 = validSubs.find(courseIt->first->getID());

            if (it2 == validSubs.end()) {
                auto it2 = validSubs.find(courseIt->first->getID());
                validSubs.insert(courseIt->first->getID());

                creditHours = courseIt->first->getCreditHours();
                gpaSum += (it->second * creditHours);
                validCreditHours += creditHours;
            }
        }
    }

    if (validCreditHours <= 0)
    {
        this->gpa = 0.0f;
        return;
    }
    this->gpa = gpaSum /validCreditHours;
    this->gpa = round(this->gpa * 1000.0f) / 1000.0f;
}
