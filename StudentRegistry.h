#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <ncurses.h>
#include "Student.h"
#include "Professor.h"
#include "Course.h"
#include "Exceptions.h"


class StudentRegistry{

private:
    std::vector<Person*> members;
    std::vector<Course*> courses;
public:
    //destructor
    ~StudentRegistry();

    //getters
    const std::vector<Person*>& getMembers() const;
    const std::vector<Course*>& getCourses() const;
    //functions
    void inputMember(Person*);
    void deleteMember(char*);
    
    void inputCourse(Course*);
    void deleteCourse(int);

    void addeleteCourse();
    
    void editMemberAM(Person*);
    void editMemberName(Person*);
    void editStudentSemester(Student*);
    void editProfessorSpecialty(Professor*);

    void editCourseCode(Course*);
    void editCourseDescription(Course*);
    void editCourseSemester(Course*);
    void editHead_Professor(Course*);
    
    void printMembers();
    void printCourses();
    void printMembersCourses(Person*);

    void sendMailprof();
    void sendMailstud();
    void writeCSV();
    void readCSV();
    Person* findMember(const char*);
    Course* findCourse(int);
    void closeWindow(WINDOW*);
};
