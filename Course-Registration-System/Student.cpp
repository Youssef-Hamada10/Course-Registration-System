#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include "Student.h"
#include "Handleable.h"
#include <fstream>
#include <conio.h>
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

void Student::registerCourse(unordered_map<string, Course>&courses)//why refrence? bec.we need the address of the pointer inside it and if we take the copy the address will be diffrenet
{
    system("cls");
    string id = "";
    cout << left <<setw(10)<< "ID" << setw(40) << "Course Title" << "Credit Hours" << endl;
    cout << "=====================================================================" << endl;
    for (auto course : courses) {
        if (course.second.getSemester() == 0)
        {
            cout << left << setw(10) << course.first << setw(45) << course.second.getTitle() << course.second.getCreditHours() << endl;
        }
    }
    cout << "=====================================================================" << endl;
    cout << "Enter Course id :";
    id = Handleable::emptyString([&]() -> string { getline(cin, id); return id; }(), "ID");
    auto it = courses.find(id);
    if (it != courses.end() && it->second.getSemester() == 0)
    {
        it->second.displayCourseInfo();
        cout << "\nAre you sure you want to register " << it->second.getTitle() << " ?\n";
        char choice = Handleable::toContinue();
        if (choice)
        {
            bool found = false;
            for (auto iti = registeredCourses.begin(); iti != registeredCourses.end(); ++iti)
            {
                if (iti->first == &it->second) {
                    cout << "Course already registerd\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                pair<Course*, string>registeredCourse;
                registeredCourse.first = &(it->second);
                registeredCourse.second = "N.A";
                registeredCourses.push_back(registeredCourse);
                cout << "Course registered successfully\n";
            }

        }
    }
    else cout << "\nCourse not found\n";
    cout << "\nDo you want to register another course ?\n";
    char choice = Handleable::toContinue();
    cin.ignore();
    if (choice)
        registerCourse(courses);
}

void Student::addCourseInFiles(pair<Course*, string> course) {
    this->registeredCourses.push_back(course);
}

void Student::displayInfo() {
    system("cls");
    cout << "Personal Information:\n============================================================================\n";
    cout << "Name: " << left << setw(37) << name << "ID: " << ID << endl;
    cout << "Username: " << left << setw(33) << username << "Password: " << password << endl;
    cout << "National ID: " << left << setw(30) << nationalID << "Telephone Number: " << telephoneNumber << endl;
    cout << "Address: " << left << setw(34) << address << "Nationality: " << nationality << endl;
    cout << "Level: " << left << setw(36) << level << "Total Credit Hours: " << totalCreditHours << endl;
    cout << "===========================================================================\n";
    updateGPA();
    cout << "\npress any key to continue :";
    _getch();
}

void Student::displayGrades() {
    system("cls");
    if (registeredCourses.empty()) {
        cout << "No Grades To View\n";
        return;
    }

    cout << left << setw(10) << "ID" << setw(40) << "Course Title" << setw(12) << "Semester" << setw(5) << "Grade\n";
    cout << "=====================================================================" << endl;

    for (const auto& course : registeredCourses) {
        cout << left << setw(10) << course.first->getID() << setw(40) << course.first->getTitle() << setw(12) << (course.first->getSemester() ? "Spring" : "Fall") << setw(5) << course.second << endl;
    }
    cout << "=====================================================================" << endl;
    cout << "\npress any key to continue :";
    _getch();
}

void Student::displayPrerequisite(unordered_map<string, Course>& courses) {
    cout << "\npress any key to continue :";
    _getch();
}

void Student::searchCourse(unordered_map<string, Course>& courses) {
    system("cls");
    string id = "";
    cout << "\nEnter Course ID: ";
    id = Handleable::emptyString([&]() -> string { getline(cin, id); return id; }(), "ID" );

    auto course = courses.find(id);

    if (course != courses.end()) {
        cout << "Course Has Been Found!\n";
        course->second.displayCourseInfo();
    } else {
        cout << "Course Does Not Exist\n";
    }
    cout << "\npress any key to continue :";
    _getch();
}

/* 
* Report logic without html code
void Student::report() {
    cout << "name :" << this->name<<endl;
    cout <<"id :"<< this->ID<<endl;
    cout << "level :" << this->level << endl;
    string semster ="";
    string temp = "";
    for (const auto& course : registeredCourses) {
        semster = course.first->getSemester() ? "Spring" : "Fall";
        if (semster != temp)
        {
            cout << semster<<endl;
            temp = semster;
        }
        cout << left << setw(10) << course.first->getID() << setw(40) << course.first->getTitle() << setw(12) << course.first->getCreditHours() << setw(5) << course.second << endl;
    }

}
*/
void Student::report() {
    system("cls");
    ofstream htmlFile("student_report.html");
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
    //htmlFile << "<h1>Student Report</h1>\n";
    htmlFile << "<p><strong>Name:</strong> " << this->name << "</p>\n";
    htmlFile << "<p><strong>ID:</strong> " << this->ID << "</p>\n";
    htmlFile << "<p><strong>Level:</strong> " << this->level << "</p>\n";
    string semester = "";
    string temp = "";

    for (const auto& course : registeredCourses) {
        semester = course.first->getSemester() ? "Spring" : "Fall";
        if (semester != temp) {
            htmlFile << "</table>\n";
            htmlFile << "<h2>" << semester << " Semester</h2>\n";
            htmlFile << "<table>\n";
            htmlFile << "<tr><th>Course ID</th><th>Title</th><th>Credit Hours</th><th>Grade</th></tr>\n";
            temp = semester;
        }
        htmlFile << "<tr>\n";
        htmlFile << "<td>" << course.first->getID() << "</td>\n";
        htmlFile << "<td>" << course.first->getTitle() << "</td>\n";
        htmlFile << "<td>" << course.first->getCreditHours() << "</td>\n";
        htmlFile << "<td>" << course.second << "</td>\n";
        htmlFile << "</tr>\n";
    }
    htmlFile << "</table>\n";
    htmlFile << "</body>\n";
    htmlFile << "</html>\n";
    htmlFile.close();
    system("wkhtmltopdf student_report.html student_report.pdf");
    cout << "PDF report created successully\n";
    cout << "\npress any key to continue :";
    _getch();
}


void Student::menu(unordered_map<string, Course>& courses) {
    int choice;
    cout << "Welcome " << name << endl;

    while (true) {
    system("cls");
    cout << "Welcome " << name << endl;
    cout << "_______________________\n\n";
        cout << "1 : Display Info.\n2 : Register A Course.\n3 : View Grades.\n4 : Check Prerequisites For A Course.\n5 : Search For A Course.\n6 : Make A Report.\n7 : Log Out\n\n\nYour Choice:";
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

vector<pair<Course*, string>> Student::getRegisteredCourses() {
    return registeredCourses;
}