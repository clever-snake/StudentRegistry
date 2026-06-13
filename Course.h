#pragma once
#include <iostream>

class Professor;

class Course{
private:
    int code;
    std::string description;
    int semester;
    Professor* head_prof;
public:
    Course(int,std::string,int,Professor*);
    Course(const Course&);
    Course();
    ~Course();

    int getCode() const;
    std::string getDescription() const;
    int getSemester() const;
    Professor* getProfessor() const;

    void setCode(int);
    void setDescription(std::string);
    void setSemester(int);
    void setProfessor(Professor*);
    
    void print(std::ostream&);
};
