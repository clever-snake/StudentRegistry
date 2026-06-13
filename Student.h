#pragma once
#include "Person.h"
#include <string>

class Student : public Person{      
    
private:
    unsigned int semester;
public:
    //constructors
    Student(const char*, std::string,char,unsigned int);
    Student(const Student&);
    Student();
    //desctructor
    ~Student();    
    //getters
    unsigned int getSemester()const;
    //setters
    void setSemester(unsigned int);
    
    virtual void print(std::ostream&);
    
    Student operator++();
    Student operator++(int);
    Student& operator+=(unsigned int);
    Student& operator-=(unsigned int);
    Student& operator=(const Student&);
};
