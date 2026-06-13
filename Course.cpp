#include "Course.h"
#include "Professor.h"

Course::Course(){
    code= 0;
    description ="";
    semester= 0;
    head_prof = nullptr;
}

Course::Course(int code,std::string description,int semester, Professor* head_prof){
    this->code = code;
    this->description = description;
    this->semester = semester;
    this->head_prof = head_prof;
}

Course::Course(const Course& x){
    this->code = x.code; 
    description = x.description;
    semester = x.semester;
    head_prof = x.head_prof;
}

Course::~Course(){
}

int Course::getCode()const {
    return code;
}

std::string Course::getDescription()const {
    return description;
}

int Course::getSemester()const {
    return semester;
}

Professor* Course::getProfessor() const{
    return head_prof;
}

void Course::setCode(int code){
    this->code = code;
}

void Course::setDescription(std::string description){
    this->description = description;
}

void Course::setSemester(int semester){
    this->semester = semester;
}

void Course::setProfessor(Professor* head_prof){
    this->head_prof = head_prof;
}

void Course::print(std::ostream& x){
    x << "Κωδικός: " << code << " Περιγραφή: " << description << " Εξάμηνο διδασκαλίας: " << semester;
    if(head_prof!=nullptr){
        x << " Καθηγητής: " << head_prof->getName();
    }
    x << std::endl;
}
