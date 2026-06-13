#include "StudentRegistry.h"

StudentRegistry::~StudentRegistry(){
    //διαγραφη μελων και μαθηματων
    for(int p=0; p<members.size(); p++){
        delete members[p];
    }
    for(int c=0; c<courses.size(); c++){
        delete courses[c];
    }
}

const std::vector<Person*>& StudentRegistry::getMembers() const{
    return members;
}

const std::vector<Course*>& StudentRegistry::getCourses() const{
    return courses;
}

void StudentRegistry::inputMember(Person* p){
    for(int i=0; i<members.size(); i++){
        if(strcmp(p->getAM(),members[i]->getAM())==0){
            throw DuplicateMemberException();
        }
    }
    members.push_back(p);
}

void StudentRegistry::deleteMember(char* AM){
    for(int i=0; i<members.size(); i++){
        if(strcmp(members[i]->getAM(),AM) == 0){
            Professor* prof = dynamic_cast<Professor*>(members[i]);
            if(prof != nullptr){
                for(int j=0; j<courses.size(); j++){
                    if(courses[j]->getProfessor() == prof){
                        courses[j]->setProfessor(nullptr);
                    }
                }
            }
            delete members[i];
            members.erase(members.begin() + i);
            return;
        }
    }
    throw MemberNotFoundException();
}

void StudentRegistry::inputCourse(Course* c){
    for(int i=0; i<courses.size(); i++){
        if(courses[i]->getCode() == c->getCode()){
            throw DuplicateCourseException();
        }
    }
    courses.push_back(c);
    if(c->getProfessor()!=nullptr){
        c->getProfessor()->addCourse(c);
    }
}

void StudentRegistry::deleteCourse(int code){
    Course * desired_course = findCourse(code);
    if(desired_course== nullptr){
        throw CourseNotFoundException();
    }
    else{
        //Διαγραφή του μαθήματος από τις λίστες των μελών που το περιέχουν
        for(int i=0; i<members.size(); i++){
            members[i]->deleteCourse(desired_course);
        }
        for(int i=0; i<courses.size(); i++){
            if(courses[i]->getCode()==code){
                delete courses[i];
                courses.erase(courses.begin() + i);
            return;
            }
        }
    }
}

void StudentRegistry::editMemberAM(Person* p){
    WINDOW* window = newwin(20,60,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);
    char buffer[100];

    mvwprintw(window,1,2,"Δώσε το καινούργιο ΑΜ.");
    wrefresh(window);
    mvwgetnstr(window,2,2,buffer,99);
    closeWindow(window);
    p->setAM(buffer);
}

void StudentRegistry::editMemberName(Person* p){
    WINDOW* window = newwin(20,60,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);
    char buffer[100];

    mvwprintw(window,1,2,"Δώσε το καινούργιο όνομα.");
    wrefresh(window);
    mvwgetnstr(window,2,2,buffer,99);
    std::string name(buffer);
    closeWindow(window);
    p->setName(name);
}

void StudentRegistry::addeleteCourse(){
    WINDOW* window = newwin(40,140,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);
    char buffer[100];
    mvwprintw(window,1,2,"Δώσε το ΑΜ του μαθητή που θες να προσθέσεις/αφαιρέσεις μάθημα.");
    wrefresh(window);
    mvwgetnstr(window,2,2,buffer,99);
    Person* p = findMember(buffer);

    mvwprintw(window,3,2,"1. Προσθήκη μαθήματος.");
    mvwprintw(window,4,2,"2. Διαγραφή μαθήματος.");
    wrefresh(window);

    mvwgetnstr(window,5,2,buffer,99);
    int ans= atoi(buffer);
    mvwprintw(window,6,2,"Γράψε το κωδικό του μαθήματος");
    wrefresh(window);
    mvwgetnstr(window,7,2,buffer,99);
    int code = atoi(buffer);
    if(findCourse(code)==nullptr){
        closeWindow(window);
        throw CourseNotFoundException();
    }
    else if(ans==1){
        p->addCourse(findCourse(code));
    }
    else if(ans==2){
        p->deleteCourse(findCourse(code));
    }
}

void StudentRegistry::editStudentSemester(Student* stud){
    WINDOW* window = newwin(20,60,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);
    char buffer[100];

    mvwprintw(window,1,2,"Δώσε το καινούργιο εξάμηνο.");
    wrefresh(window);
    mvwgetnstr(window,2,2,buffer,99);
    int semester = atoi(buffer);
    closeWindow(window);
    stud->setSemester(semester);
}

void StudentRegistry::editProfessorSpecialty(Professor* prof){
    WINDOW* window = newwin(20,60,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);
    char buffer[100];

    mvwprintw(window,1,2,"Δώσε την καινούργια ειδικότητα.");
    wrefresh(window);

    mvwgetnstr(window,2,2,buffer,99);
    std::string specialty(buffer);
    closeWindow(window);
    prof->setSpecialty(specialty);
}

void StudentRegistry::editCourseCode(Course* course){
    WINDOW* window = newwin(20,60,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);
    char buffer[100];

    mvwprintw(window,1,2,"Δώσε τον καινούργιο κωδικό.");
    wrefresh(window);
    mvwgetnstr(window,2,2,buffer,99);
    int code = atoi(buffer); 
    closeWindow(window);
    course->setCode(code);
}

void StudentRegistry::editCourseDescription(Course* course){
    WINDOW* window = newwin(20,60,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);
    char buffer[100];

    mvwprintw(window,1,2,"Δώσε τη καινούργια περιγραφή." );
    wrefresh(window);

    mvwgetnstr(window,2,2,buffer,99);
    std::string description(buffer);
    closeWindow(window);
    course->setDescription(description);
}

void StudentRegistry::editCourseSemester(Course* course){
    WINDOW* window = newwin(20,60,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);
    char buffer[100];

    mvwprintw(window,1,2, "Δώσε το καινούργιο εξάμηνο διδασκαλίας." );
    wrefresh(window);

    mvwgetnstr(window,2,2,buffer,99);
    int semester = atoi(buffer);
    closeWindow(window);
    course->setSemester(semester);
}

void StudentRegistry::editHead_Professor(Course* desired_course){
    WINDOW* window = newwin(20,60,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);
    char buffer[100];

    mvwprintw(window,1,2,"Δώσε το ΑΜ του καθηγητή που θες να είναι υπεύθυνος μαθήματος." );
    wrefresh(window);
    mvwgetnstr(window,2,2,buffer,99);
    Professor* prof = dynamic_cast<Professor*>(findMember(buffer));
    if(prof != nullptr){
        prof->deleteCourse(desired_course);
        desired_course->setProfessor(prof);
        prof->addCourse(desired_course);
    }
    else{
        closeWindow(window);
        throw MemberNotFoundException();
    }
    closeWindow(window);
}

void StudentRegistry::printMembers(){
    WINDOW* window = newwin(40,140,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);
    
    if(members.size()==0){
        mvwprintw(window,1,2,"Η λίστα με τα μέλη είναι άδεια.");
        mvwprintw(window,2,2,"Πατήστε ένα πλήκτρο για να συνεχίσετε.");
        wrefresh(window);
        wgetch(window);
        closeWindow(window);
        return;
    }
    int row=0;
    for(row=0; row<members.size(); row++){
        std::stringstream ss;
        members[row]->print(ss);
        mvwprintw(window,row+1,2,ss.str().c_str());
        wrefresh(window);
    }
    mvwprintw(window,row+1,2,"Πατήστε ένα πλήκτρο για να συνεχίσετε.");
    wrefresh(window);
    wgetch(window);
    closeWindow(window);
}

void StudentRegistry::printCourses(){
    WINDOW* window = newwin(40,140,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);
    
    if(courses.size()==0){
        mvwprintw(window,1,2,"Η λίστα με τα μαθήματα είναι άδεια.");
        mvwprintw(window,2,2,"Πατήστε ένα πλήκτρο για να συνεχίσετε.");
        wrefresh(window);
        wgetch(window);
        closeWindow(window);
        return;
    }
    int row=0;;
    for(row=0; row<courses.size(); row++){
        std::stringstream ss;
        courses[row]->print(ss);
        mvwprintw(window,row+1,2,ss.str().c_str());
        wrefresh(window);
    }
    mvwprintw(window,row+1,2,"Πατήστε ένα πλήκτρο για να συνεχίσετε.");
    wrefresh(window);
    wgetch(window);
    closeWindow(window);
}

void StudentRegistry::printMembersCourses(Person* p){
    WINDOW* window = newwin(40,140,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);
    int row=0;
    const std::vector<Course*>& c = p->getCourses();
    if(c.size()>0){
        for(row=0; row<c.size(); row++){
            std::stringstream ss;
            c[row]->print(ss);
            mvwprintw(window,row+1,2,ss.str().c_str());
            wrefresh(window);
        }
    }
    else{
        mvwprintw(window,1,2 ,"Αυτό το μέλος δεν έχει γραμμένα μαθήματα στη λίστα του.");
        mvwprintw(window,2,2,"Πατήστε ένα πλήκτρο για να συνεχίσετε.");
        wrefresh(window);
        wgetch(window);
        closeWindow(window);
        return;
    }
    mvwprintw(window,row+1,2,"Πατήστε ένα πλήκτρο για να συνεχίσετε.");
    wrefresh(window);
    wgetch(window);
    closeWindow(window);
    return;
}

void StudentRegistry::sendMailprof(){
    WINDOW* window = newwin(20,60,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);
    Professor* prof;
    int row=0;
    for(int i=0; i< members.size(); i++){
        if((prof = dynamic_cast<Professor*>(members[i]))!=nullptr){
            mvwprintw(window,row+1,2,"Στάλθηκε mail στον %s", members[i]->getName().c_str());
            row++;
        }
    }
    mvwprintw(window,row+1,2,"Πατήστε ένα πλήκτρο για να συνεχίσετε.");
    wrefresh(window);
    wgetch(window);
    closeWindow(window);
}

void StudentRegistry::sendMailstud(){
    WINDOW* window = newwin(20,60,3,5);
    keypad(window,TRUE);
    echo();
    box(window,0,0);
    wrefresh(window);
    Student* stud;
    int row=0;
    for(int i=0; i< members.size(); i++){
        if((stud = dynamic_cast<Student*>(members[i]))!=nullptr){
            mvwprintw(window,row+1,2,"Στάλθηκε mail στον %s",members[i]->getName().c_str());
            row++;
        }
    }
    mvwprintw(window,row+1,2,"Πατήστε ένα πλήκτρο για να συνεχίσετε.");
    wrefresh(window);
    wgetch(window);
    closeWindow(window);
}

void StudentRegistry::writeCSV(){
    std::ofstream membersfile("members.csv");
    if(!membersfile.good()){
        throw FileNotOpenedException();
    }

    for(int i=0; i<members.size(); i++){
        Student* stud = dynamic_cast<Student*>(members[i]);
        if(stud!=nullptr){
            membersfile << "Student," << stud->getAM() << "," << stud->getName() << "," << stud->getGender() << "," << stud->getSemester() << "\n";
        }
        else{
            Professor* prof = dynamic_cast<Professor*>(members[i]);
            if(prof!=nullptr){
                membersfile << "Professor," << prof->getAM() << "," << prof->getName() << "," << prof->getGender() << "," << prof->getSpecialty() << "\n";
            }
        }
    }
    membersfile.close();

    std::ofstream coursesfile("courses.csv");
    
    if(!coursesfile.good()){
        throw FileNotOpenedException();
    }

    for(int i=0; i<courses.size(); i++){
        coursesfile << courses[i]->getCode() << "," << courses[i]->getDescription() << "," << courses[i]->getSemester() << ",";
        if(courses[i]->getProfessor()!=nullptr){
            coursesfile << courses[i]->getProfessor()->getAM() << "\n";
        }
        else{
            coursesfile << '-' << '\n';
        }
    }

    coursesfile.close();

    std::ofstream StudentsCourses("StudentsCourses.csv");

    if(!StudentsCourses.good()){
        throw FileNotOpenedException();
    }

    for(int i=0;i<members.size();i++){
        const std::vector<Course*>& c =
        members[i]->getCourses();
        for(int j=0;j<c.size();j++){
            StudentsCourses << members[i]->getAM() << "," << c[j]->getCode()<< "\n";
        }
    }
    StudentsCourses.close();
}

void StudentRegistry::readCSV(){

    for(int i=0; i<members.size(); i++){
        delete members[i];  
    }
    members.clear();

    for(int i=0; i<courses.size(); i++){
        delete courses[i];
    }
    courses.clear();
    std::ifstream membersfile("members.csv");

    if(!membersfile.good()){
        throw FileNotOpenedException();
    }

    std::string line;

    while(getline(membersfile,line)){
        std::stringstream ss(line);
        std::string type;
        std::string am;
        std::string name;
        std::string gender;
        getline(ss,type,',');
        getline(ss,am,',');
        getline(ss,name,',');
        getline(ss,gender,',');
        if(type == "Student"){
            std::string semester;
            getline(ss,semester,',');
            Student* stud = new Student(const_cast<char*>(am.c_str()),name,gender[0],stoi(semester));
            members.push_back(stud);
        }
        else if(type=="Professor"){
            std::string specialty;
            getline(ss,specialty,',');
            Professor* prof = new Professor(const_cast<char*>(am.c_str()),name,gender[0],specialty);
            members.push_back(prof);
        }
    }

    membersfile.close();

    std::ifstream coursesfile("courses.csv");

    if(!coursesfile.good()){
        throw FileNotOpenedException();
    }

    while(getline(coursesfile,line)){
        std::stringstream ss(line);
        std::string code;
        std::string description;
        std::string semester;
        std::string profAM;

        getline(ss,code,',');
        getline(ss,description,',');
        getline(ss,semester,',');
        getline(ss,profAM,',');
        Professor* prof=nullptr;

        if(profAM != "-"){
            prof = dynamic_cast<Professor*>(findMember(const_cast<char*>(profAM.c_str())));
        }

        Course* course = new Course(stoi(code),description,stoi(semester),prof);
        courses.push_back(course);
    }

    coursesfile.close();

    std::ifstream StudentsCourses("StudentsCourses.csv");

    if(!StudentsCourses.good()){
        throw FileNotOpenedException();
    }

    while(getline(StudentsCourses,line)){
        std::stringstream ss(line);

        std::string am;
        std::string code;
        getline(ss,am,',');
        getline(ss,code);
        Person* p = findMember(const_cast<char*>(am.c_str()));

        Course* c = findCourse(stoi(code));

        if(p!=nullptr && c!=nullptr){
            p->addCourse(c);
        }
    }

    StudentsCourses.close();
}

Person* StudentRegistry::findMember(const char* AM){
    for(int i=0; i<members.size(); i++){
        if(strcmp(members[i]->getAM(), AM) == 0){
            return members[i];
        }
    }
    return nullptr;
}

Course* StudentRegistry::findCourse(int code){

    for(int i=0; i<courses.size(); i++){
        if(courses[i]->getCode() == code){
            return courses[i];
        }
    }
    return nullptr;
}

void StudentRegistry::closeWindow(WINDOW* window){
    werase(window);
    wrefresh(window);
    delwin(window);
}
