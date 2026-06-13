#include "Person.h"
#include "Exceptions.h"
#include <cstring>
#include <iostream>

Person::Person(const char* AM,std::string name){

    this->AM = new char[strlen(AM)+1]; 
    strcpy(this->AM,AM);
    this->name = name;
    gender = '-';
}

Person::Person(const char* AM,std::string name, char gender){

    this->AM = new char[strlen(AM)+1]; 
    strcpy(this->AM,AM);
    this->name = name;
    this->gender = gender;

}

Person::Person(const Person& x){

    this->AM = new char[strlen(x.AM)+1]; 
    strcpy(this->AM,x.AM);
    name = x.name;
    gender = x.gender;
    Courses = x.Courses;
}

Person::Person(){
    AM = new char[1];
    AM[0] = '\0';
    name = "";
    gender = '-';
}

Person::~Person(){
    delete[] AM; 
}

const char* Person::getAM() const{
    return AM;
}

std::string Person::getName()const{
    return name;
}

char Person::getGender()const{
    return gender;
}

const std::vector<Course*>& Person::getCourses() const{
    return Courses;
}

void Person::setAM(const char* AM){
    delete[] this->AM;
    this->AM = new char[strlen(AM) +1];
    strcpy(this->AM,AM);
}

void Person::setName(std::string name){
    this->name = name;
}

void Person::setGender(char gender){
    if(gender == 'F' || gender=='M'){
        this->gender = gender;
    }
}

void Person::addCourse(Course* course){
    //ελεγχω αν υπαρχει το μαθημα στη λίστα
    for(int i=0; i <Courses.size(); i++){
        if(Courses[i]==course){
            throw CourseAlreadyExistsException();
        }
    }
    Courses.push_back(course);
}

void Person::deleteCourse(Course* course){    
    for(int i=0; i<Courses.size(); i++){
        if(Courses[i]->getCode() == course->getCode()){
            Courses.erase(Courses.begin() + i);
            return;
        }
    }
}

Person& Person::operator-(){

    if(gender != '-'){
        if (gender=='M'){
            gender ='F';
        }
        else{
            gender = 'M';
        }
    }
    else{
        throw GenderNotDefinedException();
    }
    return *this;
}

Person& Person::operator=(const Person& x){
    if(this != &x){
        delete[] AM;
        AM = new char[strlen(x.AM) + 1];
        strcpy(AM, x.AM);
        name = x.name;
        gender = x.gender;
        Courses = x.Courses;
    }
    return *this;
}

void Person::print(std::ostream& x){
    x << "Όνομα: " << name << "(" << name.length() << ")" << " AM: " << AM << " Φύλο: " << gender ;
}
