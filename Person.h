#pragma once
#include <vector>
#include "Course.h"

class Person{

protected:
    char* AM;
    std::string name;
    char gender;
    std::vector<Course*> Courses;
public:
    //constructors
    Person(const char*,std::string);
    Person(const char*,std::string,char);
    Person(const Person&);
    Person();
    
    //destructor
    virtual ~Person();

    //getters
    const char* getAM() const;
    std::string getName() const;
    char getGender() const;
    const std::vector<Course*>& getCourses() const;

    //setters
    void setAM(const char*);
    void setName(std::string);
    void setGender(char);

    //Student registry functions
    void addCourse(Course*);
    void deleteCourse(Course*);
    
    Person& operator-();
    Person& operator=(const Person&);
    virtual void print(std::ostream&);
};
