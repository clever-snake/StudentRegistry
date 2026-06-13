#pragma once
#include "Person.h"
#include <iostream>

class Professor : public Person{
private:
    std::string specialty;
public: 
    Professor(const char* ,std::string ,char ,std::string);
    Professor(const Professor&);
    Professor();    
    ~Professor();

    std::string getSpecialty() const;
    
    void setSpecialty(std::string);
    
    
    virtual void print(std::ostream&);
    Professor& operator=(const Professor&);
};
