# Student Registry

A terminal-based student registry system written in C++. It manages students, professors and courses through a text-based user interface built with the **ncurses** library, and stores all data in CSV files.

Developed as an individual university project at the Department of Informatics and Computer Engineering, University of West Attica.

## Features

- **Members:** add, edit and delete students and professors (registration number, name, gender, semester or specialty)
- **Courses:** add, edit and delete courses (code, description, teaching semester, professor in charge)
- **Enrolments:** add or remove courses for any member and view each member's course list
- **Professor assignment:** assign or change the professor in charge of a course
- **Notifications:** simulated email notifications to all professors or all students
- **Persistence:** save and load all data (members, courses and enrolments) to and from CSV files
- **Error handling:** custom exceptions for duplicate or missing members and courses, file errors and invalid operations

## OOP Concepts

- **Inheritance and polymorphism:** `Student` and `Professor` derive from the base class `Person`, which has a virtual `print()` method and a virtual destructor
- **Runtime type identification:** `dynamic_cast` to handle students and professors differently
- **Operator overloading:** `++`, `+=` and `-=` for a student's semester, unary `-`, and assignment operators
- **Rule of Three:** copy constructors, assignment operators and destructors that deep-copy dynamically allocated memory
- **Custom exception classes** derived from `std::exception`

## Project Structure

| File | Description |
|------|-------------|
| `main.cpp` | Entry point, startup demo and interactive menu |
| `StudentRegistry.h` / `.cpp` | Core class: manages members and courses, CSV file I/O and UI windows |
| `Person.h` / `.cpp` | Base class for all members |
| `Student.h` / `.cpp` | Student class (adds semester) |
| `Professor.h` / `.cpp` | Professor class (adds specialty) |
| `Course.h` / `.cpp` | Course class |
| `Exceptions.h` | Custom exception classes |
| `members.csv`, `courses.csv`, `StudentsCourses.csv` | Sample data |

## Build and Run

Requirements: a C++17 compiler and the ncurses library.

**macOS** (ncurses is included with the Xcode Command Line Tools)

```bash
clang++ -std=c++17 *.cpp -lncurses -o StudentRegistry
./StudentRegistry
```

**Linux (Debian/Ubuntu)**

```bash
sudo apt install libncurses-dev
g++ -std=c++17 *.cpp -lncursesw -o StudentRegistry
./StudentRegistry
```

Notes:

- Run the program from the project folder, so it can find the CSV files.
- Use a large terminal window (at least 145 columns × 45 rows).
- On startup, the program runs a short demo with sample data (adding members and courses, detecting duplicates, deleting a course) and then opens the main menu.
- The user interface is in Greek.

## Data Format

| File | Line format |
|------|-------------|
| `members.csv` | `Student,<registration no.>,<name>,<gender>,<semester>` or `Professor,<registration no.>,<name>,<gender>,<specialty>` |
| `courses.csv` | `<code>,<description>,<semester>,<professor registration no. or ->` |
| `StudentsCourses.csv` | `<member registration no.>,<course code>` |

## Author

**Vasileios Kamprianis** · [github.com/clever-snake](https://github.com/clever-snake)
