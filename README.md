# 📚 Courses Registration System

## 📝 Description

The **Courses Registration System** is a console-based C++ application designed to streamline course registration for students and facilitate course and grade management for administrators. It provides essential academic functions such as course enrollment, grade viewing, prerequisite checking, and administrative control over course and student data.

---

## 👤 User Roles

### 1. **Student**

- ✅ Register for available courses (with prerequisite checks)
- 📊 View previously completed course grades
- 🔍 Check prerequisites for future courses
- 🖨️ Generate a printable grade report including:
  - Name and ID
  - Courses with grades and semesters
  - Overall GPA

### 2. **Administrator**

- 📝 Upload detailed course descriptions
- 🔗 Define and update course prerequisites
- 📂 Upload and manage student grades

---

## 🔧 Features

### For Students:

- **Course Registration:** Search and register for available courses with prerequisite validation.
- **View Grades:** Display past grades in a structured format.
- **Check Prerequisites:** View required prior courses for each subject.
- **Generate Report:** Export academic performance, including GPA, to a printable format.

### For Administrators:

- **Upload Course Descriptions:** Include title, syllabus, credits, and instructor info.
- **Set Prerequisites:** Link prerequisite courses with enforcement during registration.
- **Manage Student Grades:** Upload and edit student performance data (bonus: CSV upload supported).

---

## 🧠 Data Structures & Evaluation Criteria

- Applying **suitable data structures** (e.g., trees, hash maps, linked lists) tailored for each functionality.
- The project will be evaluated based on:
  - Relevance and efficiency of chosen data structures
  - Explanation and justification for each structure
  - Code quality and clarity (clean, maintainable code is a must)

---

## 📌 Development Notes

- All data is **loaded once at the start** of the program.
- Subsequent operations manipulate the in-memory data structures.
- Use of **built-in C++ libraries** is allowed and encouraged for efficiency.

---

## 🛠 Development Environment

- **Language:** C++
- **Compiler:** Any C++17-compliant compiler (e.g., g++, MSVC)
- **IDE (optional):** Visual Studio / Code::Blocks / CLion / VS Code
- **Platform:** Cross-platform (Windows/Linux/Mac)

---

## 📂 Project Structure (Example)

```
/CoursesRegistrationSystem
├── src/
│   ├── main.cpp
│   ├── student.cpp
│   ├── admin.cpp
│   └── course.cpp
├── data/
│   ├── courses.csv
│   ├── students.csv
│   └── grades.csv
├── include/
│   └── headers.h
├── README.md
└── Makefile
```

---

## 🚀 How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/Youssef-Hamada10/Course-Registration-System.git
   ```
2. Compile the program:
   ```bash
   g++ src/*.cpp -o CoursesApp
   ```
3. Run the executable:
   ```bash
   ./CoursesApp
   ```

---

## 📌 Notes

- All data is processed using in-memory structures for performance and flexibility.

---
