#include "Student.h"

Student::Student(const char* AM,std::string name,char gender,unsigned int semester) : Person(AM,name,gender){
    this->semester = semester;
}

Student::Student(const Student& x) : Person(x){
    semester = x.semester;
}

Student::Student() : Person(){
    semester = 1;
}

Student::~Student(){
}

unsigned int Student::getSemester()const{
    return semester;
}

void Student::setSemester(unsigned int semester){
    if(semester>0 && semester<10){
        this->semester = semester;
    }
}

void Student::print(std::ostream& x){
    Person::print(x);
    x << " Εξάμηνο: " << semester << std::endl;
}

Student Student::operator++(){
    if(semester<10){
        semester++;
    }
    return *this;
}

Student Student::operator++(int){
    Student temp = *this;
    if(semester<10){
        semester++;
    }
    return temp;
}

Student& Student::operator+=(unsigned int x){
    if(semester+x<=10){
        semester+= x;
    }
    return *this;
}

Student& Student::operator-=(unsigned int x){
    if(semester > x){
        semester-= x;
    }
    else{
        semester = 1;
    }
    return *this;
}

 Student& Student::operator=(const Student& x){
    if(this != &x){
        Person::operator=(x);
        semester = x.semester;
    }
    return *this;
 }