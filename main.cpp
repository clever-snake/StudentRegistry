#include <iostream>
#include <locale.h>
#include <ncurses.h>
#include "Professor.h"
#include "Student.h"
#include "StudentRegistry.h"

void menu(WINDOW* window);
Person* inputMember(StudentRegistry&);
char* deleteMember();
Course* inputCourse(StudentRegistry&);
int deleteCourse();
void editMember(StudentRegistry&);
void editCourse(StudentRegistry&);
void printMembersCourses(StudentRegistry&);
void errorWindow(const char*);
void closeWindow(WINDOW*);

int main(){
    setlocale(LC_ALL,"");
    initscr();
    cbreak();
    echo();
    WINDOW* window = newwin(40,140,1,1);

    StudentRegistry services;
    
    //Εισάγω 3 φοιτητές
    Student* stud;
    try{
        stud = new Student("23390204","basilis",'M',4);
        services.inputMember(stud);
        stud = new Student("123","vasileios",'M',2);
        services.inputMember(stud);
        stud = new Student("321","basilikh",'F',6);
        services.inputMember(stud);
    }
    catch(const std::exception& e){
        errorWindow(e.what());
    }
    
    //τυπώνω να δω ότι αποθηκεύτηκαν σωστά
    mvwprintw(window,1,2,"Τυπώνω τους 3 αρχικούς φοιτητές.");
    wrefresh(window);
    services.printMembers();
    
    //ξαναβάζω φοιτητή με το ίδιο ΑΜ για να δω τα exceptions
    mvwhline(window,1,2,' ',100);
    mvwprintw(window,1,2,"Έλεγχος αποθήκευσης duplicate.");
    wrefresh(window);
    try{
        stud = new Student("23390204", "billy", 'M',8);
        services.inputMember(stud);
    }
    catch(const std::exception& e){
        errorWindow(e.what());
    }


    //εισάγω 3 καθηγητές

    Professor* prof;
    try{
        prof = new Professor("12345","gmele",'M',"programmatismos");
        services.inputMember(prof);
        prof = new Professor("54321","bogiatzis",'M',"proedros");
        services.inputMember(prof);
        prof = new Professor("6789", "giannako",'M',"synhgoros");
        services.inputMember(prof);
    }    
    catch(const std::exception& e){
        errorWindow(e.what());
    }

    //Τυπώνω τη λίστα έχοντας εισάγει 3 καθηγητές
    mvwhline(window,1,2,' ',100);
    mvwprintw(window,1,2,"Λίστα μαζί με καθηγητές που εισήγαγα.");
    wrefresh(window);
    services.printMembers();

    //εισάγω 3 μαθήματα
    Course* c;
    try{
        c = new Course(123,"antik",2,dynamic_cast<Professor*>(services.findMember("12345")));
        services.inputCourse(c);
        c = new Course(543,"arxitektonikh",3,dynamic_cast<Professor*>(services.findMember("54321")));
        services.inputCourse(c);
        c = new Course(876,"hlektronikh",3,dynamic_cast<Professor*>(services.findMember("6789")));
        services.inputCourse(c);
    }
    catch(const std::exception& e){
        errorWindow(e.what());
    }
    mvwhline(window,1,2,' ',100);
    mvwprintw(window,1,2,"Λίστα μαθημάτων που εισήγαγα.");
    wrefresh(window);
    services.printCourses();
    
    //εισάγω τα μαθήματα σε έναν μαθητή
    
    try{
        services.findMember("23390204")->addCourse(services.findCourse(123));
        services.findMember("23390204")->addCourse(services.findCourse(543));
        services.findMember("23390204")->addCourse(services.findCourse(876));
    }
    catch(const std::exception& e){
        errorWindow(e.what());
    }
    
    mvwhline(window,1,2,' ',100);
    mvwprintw(window,1,2,"Λίστα μαθημάτων φοιτητή που εισήγαγα τα μαθήματα.");
    wrefresh(window);
    services.printMembersCourses(services.findMember("23390204"));

    //ελέγχω αν τα μαθήματα αποθηκεύονται στους καθηγητές που τα διδάσκουν
    mvwhline(window,1,2,' ',100);
    mvwprintw(window,1,2,"Έλεγχος αποθήκευσης μαθήματος στον υπεύθυνο καθηγητή.");
    wrefresh(window);

    services.printMembersCourses(services.findMember("12345"));
    
    
    try{
        services.deleteCourse(123);
    }
    catch(const std::exception& e){
        errorWindow(e.what());
    }
    mvwhline(window,1,2,' ',100);
    mvwprintw(window,1,2,"Έλεγχος διαγραφής μαθήματος από λίστα μελών με τη διαγραφή του μαθήματος 123.");
    wrefresh(window);
    services.printMembersCourses(services.findMember("23390204"));

    
    //αποθήκευση δεδομένων σε αρχείο
    try{
        services.writeCSV();
    }
    catch(const std::exception& e){
        errorWindow(e.what());
    }

    //ανάκτηση δεδομένων από αρχείο
    try{
        services.readCSV();
    }
    catch(const std::exception& e){
        errorWindow(e.what());
    }
    
    delwin(window);
    endwin();
    window = newwin(40,140,1,1);
    

    int ans=0;
    while(ans!=15){
        menu(window);
        char buffer[10];
        mvwhline(window,15,2,' ',140);
        mvwgetnstr(window,15,2,buffer,9);
        ans=atoi(buffer);
        switch (ans){    
            case 1:
                try{
                    Person* p = inputMember(services);
                    if(p!=nullptr){
                        services.inputMember(p);
                    }
                }
                catch(const std::exception& e){
                    errorWindow(e.what());
                }
                break;
            case 2:
                try{
                    services.inputCourse(inputCourse(services));
                }
                catch(const std::exception& e){
                    errorWindow(e.what());
                }
                break;
            case 3:
                try{
                    char* am = deleteMember();
                    services.deleteMember(am);
                    delete[] am;
                }
                catch(const std::exception& e){
                    errorWindow(e.what());
                }
                break;
            case 4:
                try{
                    services.deleteCourse(deleteCourse());
                }
                catch(const std::exception& e){
                    errorWindow(e.what());
                }
                break;
            case 5:
                try{
                    editMember(services);
                }
                catch(const std::exception& e){
                    errorWindow(e.what());
                }
                break;
            case 6:
                try{
                    editCourse(services);
                }
                catch(const std::exception& e){
                    errorWindow(e.what());
                }
                break;
            case 7:
                services.printMembers();
                break;
            case 8:
                services.printCourses();
                break;
            case 9:
                try{
                    services.addeleteCourse();
                }
                catch(const std::exception& e){
                    errorWindow(e.what());
                }
                break;
            case 10:
                try{
                    printMembersCourses(services);
                }
                catch(const std::exception& e){
                    errorWindow(e.what());
                }
                break;
            case 11:
                services.sendMailprof();
                break;
            case 12:
                services.sendMailstud();
                break;
            case 13:
                try{
                    services.writeCSV();
                }
                catch(const std::exception& e){
                    errorWindow(e.what());
                }
                break;
            case 14:
                try{
                    services.readCSV();
                }
                catch(const std::exception& e){
                    errorWindow(e.what());
                }
                break;
        }
    }
    delwin(window);
    endwin();
    return 0;
}

void menu(WINDOW* window){
    clear();
    mvwprintw(window,1,2,"1. Εισαγωγή μέλους.");
    mvwprintw(window,2,2,"2. Εισαγωγή μαθήματος.");
    mvwprintw(window,3,2,"3. Διαγραφή μέλους.");
    mvwprintw(window,4,2,"4. Διαγραφή μαθήματος.");
    mvwprintw(window,5,2,"5. Διόρθωση μέλους.");
    mvwprintw(window,6,2,"6. Διόρθωση μαθήματος.");
    mvwprintw(window,7,2,"7. Εμφάνιση λίστα μελών.");
    mvwprintw(window,8,2,"8. Εμφάνιση λίστα μαθημάτων.");
    mvwprintw(window,9,2,"9. Πρόσθεση/Αφαίρεση μαθήματος σε μέλος.");
    mvwprintw(window,10,2,"10. Εμφάνιση λίστα μαθημάτων μέλους.");
    mvwprintw(window,11,2,"11. Αποστολή Mail σε καθηγητές.");
    mvwprintw(window,12,2,"12. Αποστολή Mail φοιτητών.");
    mvwprintw(window,13,2,"13. Αποθήκευση δεδομένων σε csv αρχείο.");
    mvwprintw(window,14,2,"14. Ανάκτηση δεδομένων από csv αρχείο.");
    mvwprintw(window,15,2,"15. Έξοδος.");
    wrefresh(window);
}

Person* inputMember(StudentRegistry& services){
    WINDOW* window = newwin(20,60,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);

    mvwprintw(window,1,2,"1. Εισαγωγή φοιτητή.");
    mvwprintw(window,2,2,"2. Εισαγωγή καθηγητή.");
    mvwprintw(window,3,2,"3. Έξοδος.");
    wrefresh(window);
    char buffer[100];
    mvwgetnstr(window,4,2,buffer,99);

    int ans = atoi(buffer);

    if(ans==3 || (ans!=1 && ans!=2)){
        closeWindow(window);
        refresh();
        return nullptr;
    }

    char am[100];
    mvwprintw(window,5,2,"Δώσε AM: ");
    wrefresh(window);
    mvwgetnstr(window,6,2,am,99);

    if(services.findMember(am)!=nullptr){
        closeWindow(window);
        throw DuplicateMemberException();
    }

    mvwprintw(window,7,2,"Δώσε όνομα: ");
    wrefresh(window);
    mvwgetnstr(window,8,2,buffer,99);
    std::string name(buffer);

    mvwprintw(window,9,2,"Δώσε φύλο (M/F): ");
    wrefresh(window);
    mvwgetnstr(window,10,2,buffer,99);
    char gender = toupper(buffer[0]);
    if(ans==1){
        
        mvwprintw(window,11,2,"Δώσε εξάμηνο: ");
        wrefresh(window);
        mvwgetnstr(window,12,2,buffer,99);
        unsigned int semester = atoi(buffer);
        closeWindow(window);
        refresh();
        Student* p = new Student(am,name,gender,semester);
        return p;
    }
    else if(ans==2){
        
        mvwprintw(window,11,2,"Δώσε ειδικότητα: ");
        wrefresh(window);
        mvwgetnstr(window,12,2,buffer,99);
        std::string specialty(buffer);
        closeWindow(window);
        refresh();
        Professor* p = new Professor(am, name, gender, specialty);
        return p;
    }
    return nullptr;
}

char* deleteMember(){
    WINDOW* window = newwin(20,60,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);

    mvwprintw(window,1,2,"Δώσε το ΑΜ του μέλους που θες να διαγράψεις: ");
    char* tmp = new char[100];
    mvwgetnstr(window,2,2,tmp,99);
    closeWindow(window);
    return tmp;
}

Course* inputCourse(StudentRegistry& services){
    WINDOW* window = newwin(20,60,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);

    char buffer[100];
    mvwprintw(window,1,2,"Δώσε τον κωδικό του μαθήματος:");
    wrefresh(window);

    mvwgetnstr(window,2,2,buffer,99);
    int code = atoi(buffer);

    if(services.findCourse(code)!= nullptr){
        closeWindow(window);
        throw DuplicateCourseException();
    }
    mvwprintw(window,3,2,"Δώσε τη περιγραφή του μαθήματος:");
    wrefresh(window);

    mvwgetnstr(window,4,2,buffer,99);
    std::string description(buffer);
    
    mvwprintw(window,5,2,"Δώσε εξάμηνο διδασκαλίας:");
    wrefresh(window);
    
    mvwgetnstr(window,6,2,buffer,99);
    int semester = atoi(buffer);

    mvwprintw(window,7,2,"1. Διάλεξε καθηγητή.");
    mvwprintw(window,8,2,"2. Το μάθημα θα είναι χωρίς καθηγητή.");
    wrefresh(window);
    mvwgetnstr(window,9,2,buffer,99);
    int ans = atoi(buffer);
    Professor* prof=nullptr;
    if(ans==2){
        prof = nullptr;
    }
    else if(ans==1){
        char AM[100];
        mvwprintw(window,10,2,"Δώσε το ΑΜ του καθηγητή:");
        mvwgetnstr(window,11,2,AM,99);
        Person* p = services.findMember(AM);
        prof = dynamic_cast<Professor*>(p);
        if(prof==nullptr){
            closeWindow(window);
            throw MemberNotFoundException();
        }
    }
    closeWindow(window);
    refresh();
    Course* c = new Course(code,description,semester,prof);
    return c;
}

int deleteCourse(){
    WINDOW* window = newwin(20,60,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);
    mvwprintw(window,1,2,"Δώσε τον κωδικό του μαθήματος που θες να διαγράψεις.");
    wrefresh(window);
    char buffer[100];
    mvwgetnstr(window,2,2,buffer,99);
    int code = atoi(buffer);
    closeWindow(window);
    return code;
}

void editMember(StudentRegistry& services){
    WINDOW* window = newwin(20,60,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);

    char buffer[100];
    mvwprintw(window,1,2,"Δώσε το ΑΜ του μέλους που θες να διορθώσεις: ");
    wrefresh(window);
    
    mvwgetnstr(window,2,2,buffer,99);
    Person* p = nullptr;
    p=services.findMember(buffer);
    if(p == nullptr){
        closeWindow(window);
        throw MemberNotFoundException();
    }
    else{
        mvwprintw(window,3,2,"1. Αλλαγή AM.");
        mvwprintw(window,4,2,"2. Αλλαγή ονόματος.");
        mvwprintw(window,5,2,"3. Αλλαγή φύλου.");
        if(dynamic_cast<Student*>(p)!=nullptr){
            mvwprintw(window,6,2,"4. Αλλαγή εξαμήνου.");
            mvwprintw(window,7,2,"5. Έξοδος.");
            wrefresh(window);
            mvwgetnstr(window,8,2,buffer,99);
            int ans = atoi(buffer);
            Student* stud = dynamic_cast<Student*>(p);
            switch(ans){
                case 1:
                    services.editMemberAM(stud);
                    break;
                case 2:
                    services.editMemberName(stud);
                    break;
                case 3:
                    stud->operator-();
                    break;
                case 4:
                    services.editStudentSemester(stud);
                    break;
                case 5:
                    closeWindow(window);
                    return;
            }
        }
        else{
            mvwprintw(window,6,2,"4. Αλλαγή ειδικότητας.");
            mvwprintw(window,7,2,"5. Έξοδος.");
            wrefresh(window);
            mvwgetnstr(window,8,2,buffer,99);
            int ans = atoi(buffer);
            Professor* prof = dynamic_cast<Professor*>(p);
            switch(ans){
                case 1:
                    services.editMemberAM(prof);
                    break;
                case 2:
                    services.editMemberName(prof);
                    break;
                case 3:
                    prof->operator-();
                    break;
                case 4:
                    services.editProfessorSpecialty(prof);
                    break;
                case 5:
                    closeWindow(window);
                    return;
            }
        }
    }
    
}

void editCourse(StudentRegistry& services){
    WINDOW* window = newwin(20,60,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);

    char buffer[100];
    mvwprintw(window,1,2,"Δώσε τον κωδικό του μαθήματος:");
    wrefresh(window);
    mvwgetnstr(window,2,2,buffer,99);
    int code = atoi(buffer);
    Course* desired_course = services.findCourse(code);
    if(desired_course == nullptr){
        closeWindow(window);
        throw CourseNotFoundException();
    }
    else{
        mvwprintw(window,3,2,"1. Αλλαγή κωδικού.");
        mvwprintw(window,4,2,"2. Αλλαγή περιγραφής.");
        mvwprintw(window,5,2,"3. Αλλαγή εξαμήνου διδασκαλίας.");
        mvwprintw(window,6,2,"4. Αλλαγή υπεύθυνου καθηγητή.");
        mvwprintw(window,7,2,"5. Έξοδος.");
        wrefresh(window);
        mvwgetnstr(window,8,2,buffer,99);
        int ans = atoi(buffer);
        
        switch (ans){
        case 1:
            services.editCourseCode(desired_course);
            break;
        case 2:
            services.editCourseDescription(desired_course);
            break;
        case 3:
            services.editCourseSemester(desired_course);
            break;
        case 4:
            services.editHead_Professor(desired_course);
            break;
        case 5:
            return;
        }
    }
}

void printMembersCourses(StudentRegistry& services){
    WINDOW* window = newwin(20,60,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);

    char buffer[100];
    
    mvwprintw(window,1,2,"Δώσε το ΑΜ του μέλους.");
    mvwgetnstr(window,2,2,buffer,99);
    Person* p = services.findMember(buffer);
    if(p==nullptr){
        closeWindow(window);
        throw MemberNotFoundException();
    }
    services.printMembersCourses(p);
    closeWindow(window);
}

void errorWindow(const char* error){

    WINDOW* window = newwin(5,60,3,5);
    box(window,0,0);
    mvwprintw(window,1,2,"%s",error);
    mvwprintw(window,2,2,"Πατήστε ένα πλήκτρο για να συνεχίσετε");
    wrefresh(window);
    wgetch(window);

    delwin(window);

    clear();
    refresh();
}

void closeWindow(WINDOW* window){
    werase(window);
    wrefresh(window);
    delwin(window);
}
