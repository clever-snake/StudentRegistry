#include "Professor.h"

Professor::Professor(const char* AM,std::string name,char gender,std::string specialty) : Person(AM,name,gender){
    this->specialty = specialty;
}

Professor::Professor(const Professor& x) : Person(x){
    specialty = x.specialty;
}

Professor::Professor(): Person(){
    specialty = "";
}

Professor::~Professor(){
}

std::string Professor::getSpecialty() const{
    return specialty;
}

void Professor::setSpecialty(std::string specialty){
    this->specialty = specialty;
}

void Professor::print(std::ostream& x){
    Person::print(x);
    x << " Ειδικότητα: " << specialty << std::endl;
}

Professor& Professor::operator=(const Professor& x){
    if(this != &x){
        Person::operator=(x);
        specialty = x.specialty;
    }
    return *this;
}
