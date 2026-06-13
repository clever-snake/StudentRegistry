#pragma once
#include <exception>

class DuplicateMemberException : public std::exception{
    public:
        const char* what() const throw(){
            return "Υπάρχει ήδη μέλος με αυτό το ΑΜ.";
        }
};

class DuplicateCourseException : public std::exception{
    public:
        const char* what() const throw(){
            return "Υπάρχει ήδη μάθημα με αυτό το κωδικό.";
        }
};

class MemberNotFoundException : public std::exception{
    public:
        const char* what() const throw(){
            return "Δεν βρέθηκε μέλος με αυτό το ΑΜ.";
        }
};

class CourseNotFoundException :public std::exception{
    public:
        const char* what() const throw(){
            return "Δεν βρέθηκε μάθημα με αυτο το κωδικό";
        }
};

class FileNotOpenedException : public std::exception{
    public:
        const char* what() const throw(){
            return "Σφάλμα ανοίγματος αρχείου.";
        }
};

class CourseAlreadyExistsException : public std::exception{
    public:
        const char* what() const throw(){
            return "Το μάθημα είναι ήδη γραμμένο στην λίστα.";
        }
};

class GenderNotDefinedException : public std::exception{
    public:
        const char* what() const throw(){
            return "Αυτό το μέλος δεν έχει προσδιορίσει το φύλο του.";
        }
};