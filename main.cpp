#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "Classes/Class.h"
#include "Classes/Student.h"
#include "Classes/Schedule.h"
#include "Classes/Lesson.h"
#include <queue>


std::vector<Class> classes;
std::map<std::string, std::vector<std::string>> UCs; //map<UCcode,vector<Class Codes>>
std::vector<Student> StudentsList;


//funcions
template<typename T, typename A>
bool in_map( std::map<T ,A> map,T s);
template<typename T>
bool in_vec( std::vector<T> vec, T s);
void set_up_classes_per_uc();
void set_up_classes();
void set_up_students();
Class& get_CLass(std::string ClassCode);
std::vector<Lesson> get_Lessons(std::string ClassCode,std::string UCcode,std::string Type="T");
Student get_Student(std::string StudentCode);
bool validate_UC(std::string UCcode);
bool validate_Class(std::string ClassCode);
bool validate_Student(std::string StudentCode);
bool validate_Lesson_Structure(Lesson l);
bool validate_Student_Structure(Student s);
bool validate_Lesson(std::string UCcode,std::string ClassCode,std::string Type="T");
void save();
//main
int main(int argc, char *argv[]) {
    // stores values from classes_per_uc.csv
    set_up_classes_per_uc();

    // stores values from classes.csv
    set_up_classes();

    // stores values from students_classes.csv
    set_up_students();

    //User Interface
    static std::map<std::string,int> OperationValue{{"Check",0},
                                                    {"Add",1},
                                                    {"Remove",2},
                                                    {"Undo Action",3}};

    static std::map<std::string, int> MethodValue{{"Student Schedule",    0}, // check
                                                  {"Class Schedule", 1},
                                                  {"Lesson", 2},
                                                  {"Lesson From Class",   3},
                                                  {"Lesson From UC",   4},
                                                  {"Classes From UC",   5},
                                                  {"Students From UC",   6},
                                                  {"Lesson to UC",   7}, // add
                                                  {"Lesson to Student",   8},
                                                  {"Student",   9},
                                                  {"Class",   10},
                                                  {"UC",   11},
                                                  {"Lesson From Students",   12}, // remove
                                                  {"Lesson From Class",   13},
                                                  {"Students",   14},
                                                  {"Class",   15},
                                                  {"UC",   16}};

    std::queue<std::string> ActionQueue;
    std::cout<<"           Welcome to the Schedule Manager\n";

    while (true) {
        std::string inputuser;
        std::cout<<"                Chose an Operation\n";
        std::cout<<"-------------------------------------------------------\n";
        std::cout<<"|  Check  |  Add  |  Remove  |  Undo Action  |  Exit  |\n";
        std::cout<<"-------------------------------------------------------\n";

        getline(std::cin,inputuser);
        if(inputuser=="Check")
        {
            std::string method;
            bool c= true;
            while (c) {
                c=false;
                std::cout<<"                          Chose Check Method\n";
                std::cout<<"-----------------------------------------------------------------------------\n";
                std::cout<<"| Student Schedule   -> Checks a Student Schedule                           |\n";
                std::cout<<"| Class Schedule     -> Checks a Class Schedule                             |\n";
                std::cout<<"| Lesson             -> Checks the time of The Lessons From a UC in a Class |\n";
                std::cout<<"| Lessons From Class -> Checks all the Lessons time and Type from a Class   |\n";
                std::cout<<"| Lessons From UC    -> Checks all the Lessons time and type from UC        |\n";
                std::cout<<"| Classes From UC    -> Checks all the Classes from a UC                    |\n";
                std::cout<<"| Students From UC   -> Checks all the Students from a UC                   |\n";
                std::cout<<"| Back                                                                      |\n";
                std::cout<<"-----------------------------------------------------------------------------\n";

                getline(std::cin, method);
                if (method=="Back") {
                    continue;
                }else if(!in_map(MethodValue, method))
                {
                    std::cout << "Invalid Method Try Again\n";
                    c= true;
                }
                else {
                    std::string temp = "Check/" + method;
                    bool validc = true;
                    while (validc) {
                        validc = false;
                        switch (MethodValue[method]) {
                            case 0: {   //Student Schedule
                                std::string element;
                                std::cout << "Student Code: \n";
                                std::getline(std::cin,element);
                                if (validate_Student(element)) {
                                    temp += ('/' + element);
                                    ActionQueue.push(temp);
                                }else {
                                    std::cout << "Invalid Student Code Try Again\n";
                                    validc = true;
                                }
                            }
                                break;
                            case 1: {   //Class Schedule
                                std::string element;
                                std::cout << "Class Code: \n";
                                std::getline(std::cin,element);
                                if (validate_Class(element)) {
                                    temp += ('/' + element);
                                    ActionQueue.push(temp);
                                }else {
                                    std::cout << "Invalid Class Code Try Again\n";
                                    validc = true;
                                }
                            }
                                break;
                            case 2: {   //Lesson
                                std::string element1, element2;
                                std::cout << "UC Code: \n";
                                std::getline(std::cin,element1);
                                std::cout << "Class Code: \n";
                                std::getline(std::cin,element2);
                                if(validate_Lesson(element1,element2)) {
                                    temp += ('/' + element1 + '/' + element2 );
                                    ActionQueue.push(temp);
                                }else {
                                    std::cout << "Invalid Lesson Try Again\n";
                                    validc = true;
                                }
                            }
                                break;
                            case 3: {   //Lessons From Class
                                std::string element;
                                std::cout << "Class Code: \n";
                                std::getline(std::cin,element);
                                if (validate_Class(element)) {
                                    temp += ('/' + element);
                                    ActionQueue.push(temp);
                                }else {
                                    std::cout << "Invalid Class Code Try Again\n";
                                    validc = true;
                                }
                            }
                                break;
                            case 4: {   //Lessons From UC
                                std::string element;
                                std::cout << "UC Code: \n";
                                std::getline(std::cin,element);
                                if (validate_UC(element)) {
                                    temp += ('/' + element);
                                    ActionQueue.push(temp);
                                }else {
                                    std::cout << "Invalid UC Code Try Again\n";
                                    validc = true;
                                }
                            }
                                break;
                            case 5: {   //Classes From UC
                                std::string element;
                                std::cout << "UC Code: \n";
                                std::getline(std::cin,element);
                                if (validate_UC(element)) {
                                    temp += ('/' + element);
                                    ActionQueue.push(temp);
                                }else {
                                    std::cout << "Invalid UC Code Try Again\n";
                                    validc = true;
                                }
                            }
                                break;
                            case 6: {   //Students From UC
                                std::string element;
                                std::cout << "UC Code: \n";
                                std::getline(std::cin,element);
                                if (validate_UC(element)) {
                                    temp += ('/' + element);
                                    ActionQueue.push(temp);
                                }else {
                                    std::cout << "Invalid UC Code Try Again\n";
                                    validc = true;
                                }
                            }
                                break;
                        }
                    }
                }
            }
        }else if(inputuser=="Add")
        {
            std::string method;
            bool a= true;
            while (a) {
                a=false;
                std::cout<<"                      Chose Add Method\n";
                std::cout<<"----------------------------------------------------------------------\n";
                std::cout<<"| Lesson to UC      -> Adds a Lesson to a UC                         |\n";
                std::cout<<"| Lesson to Student -> Adds a Lesson to a Student Schedule           |\n";
                std::cout<<"| Student           -> Adds a Student to the System (Empty Schedule) |\n";
                std::cout<<"| Class             -> Adds a Class to the System (Empty Schedule)   |\n";
                std::cout<<"| UC                -> Adds a UC to the System                       |\n";
                std::cout<<"| Back                                                               |\n";
                std::cout<<"----------------------------------------------------------------------\n";

                getline(std::cin, method);
                if (method=="Back") {
                    continue;
                }else if(!in_map(MethodValue, method))
                {
                    std::cout << "Invalid Method Try Again\n";
                    a=true;
                }
                else {
                    std::string temp = "Add/" + method;
                    bool valida = true;
                    while (valida) {
                        valida = false;
                        switch (MethodValue[method]) {
                            case 7: {   //Lesson to UC
                                std::string sh, d, t, w, uc, cc;
                                std::cout << "UC Code: \n";
                                std::getline(std::cin,uc);
                                std::cout << "Class Code: \n";
                                std::getline(std::cin,cc);
                                std::cout << "Weekday: \n";
                                std::getline(std::cin,w);
                                std::cout << "Start Hour: \n";
                                std::getline(std::cin,sh);
                                std::cout << "Duration: \n";
                                std::getline(std::cin,d);
                                std::cout << "Type: \n";
                                std::getline(std::cin,t);
                                if(validate_Lesson_Structure(Lesson(std::stof(sh), std::stof(d), t, w, uc, cc))) {
                                    temp += '/' + uc + '/' + cc + '/' + w + '/' + sh + '/' + d + '/' + t;
                                    ActionQueue.push(temp);
                                }else {
                                    std::cout << "Invalid Lesson Structure Try Again\n";
                                    valida = true;
                                }
                            }
                                break;
                            case 8: {   //Lesson to Student
                                std::string uc, cc, sc;
                                std::cout << "Student Code: \n";
                                std::getline(std::cin,sc);
                                std::cout << "UC Code: \n";
                                std::getline(std::cin,uc);
                                std::cout << "Class Code: \n";
                                std::getline(std::cin,cc);
                                if(validate_Lesson(uc,cc)) {
                                    temp += '/' + sc + '/' + uc + '/' + cc;
                                    ActionQueue.push(temp);
                                }else {
                                    std::cout << "Invalid Lesson Try Again\n";
                                    valida = true;
                                }
                            }
                                break;
                            case 9: {   //Student
                                std::string sc, sn;
                                std::cout << "Student Code: \n";
                                std::getline(std::cin,sc);
                                std::cout << "Student Name: \n";
                                std::getline(std::cin,sn);
                                if(validate_Student_Structure(Student())) {
                                    temp += ('/' + sc + '/' + sn);
                                    ActionQueue.push(temp);
                                }else {
                                    std::cout << "Invalid Student Structure Try Again\n";
                                    valida = true;
                                }
                            }
                                break;
                            case 10: {   //Class
                                std::string cc,n;
                                std::cout << "Class Code: \n";
                                std::getline(std::cin,cc);
                                temp+=('/'+cc);
                            }
                                break;
                            case 11: {   //UC
                                std::string uc,n;
                                std::cout << "UC Code: \n";
                                std::getline(std::cin,uc);
                                std::cout << "How Many Lessons? \n";
                                std::getline(std::cin,n);
                                if(std::stoi(n) <= 0)
                                {
                                    std::cout << "Invalid Number of Lessons Try Again\n You need to have at least 1 Lesson\n";
                                    valida = true;
                                }
                                else {
                                    temp += '/' + uc + '/' + n;
                                    int x = 0;
                                    while (x < std::stoi(n)) {
                                        std::string sh, d, t, w, cc;
                                        std::cout << "Class Code: \n";
                                        std::getline(std::cin, cc);
                                        std::cout << "Weekday: \n";
                                        std::getline(std::cin, w);
                                        std::cout << "Start Hour: \n";
                                        std::getline(std::cin, sh);
                                        std::cout << "Duration: \n";
                                        std::getline(std::cin, d);
                                        std::cout << "Type: \n";
                                        std::getline(std::cin, t);
                                        if (validate_Lesson_Structure(Lesson(std::stof(sh), std::stof(d), t, w, uc, cc))) {
                                            temp += '/' + cc + '/' + w + '/' + sh + '/' + d + '/' + t;
                                            x++;
                                        } else {
                                            std::cout << "Invalid Lesson Structure Try Again\n";
                                        }
                                    }
                                    ActionQueue.push(temp);
                                }
                            }
                                break;
                        }
                    }
                }
            }
            continue;
        }else if(inputuser=="Remove")
        {
            std::string method;
            bool r= true;
            while (r) {
                r=false;
                std::cout<<"                       Chose Remove Method\n";
                std::cout<<"--------------------------------------------------------------------\n";
                std::cout<<"| Lesson From Students -> Removes a Lesson from a Student Schedule |\n";
                std::cout<<"| Lesson From Clas     -> Removes a Lesson from a Class Schedule   |\n";
                std::cout<<"| Student              -> Removes a Student from the System        |\n";
                std::cout<<"| Class                -> Removes a Class from the System          |\n";
                std::cout<<"| UC                   -> Removes a UC from the System             |\n";
                std::cout<<"| Back                                                             |\n";
                std::cout<<"--------------------------------------------------------------------\n";

                getline(std::cin, method);
                if (method=="Back") {
                    continue;
                }else if(!in_map(MethodValue, method))
                {
                    std::cout << "Invalid Method Try Again\n";
                    r=true;
                }
                else {
                    std::string temp = "Remove/" + method;
                    bool validr = true;
                    while (validr) {
                        validr=false;
                        switch (MethodValue[method]) {
                            case 12: {   //Lesson From Students
                                std::string uc,sc,t;
                                std::cout << "Student Code: \n";
                                std::getline(std::cin,sc);
                                std::cout << "UC Code: \n";
                                std::getline(std::cin,uc);
                                std::cout << "Type: \n";
                                std::getline(std::cin,t);
                                if(validate_Student(sc)&&validate_UC(uc)&&validate_Lesson(uc,"",t)) {
                                    temp += '/' + sc + '/' + uc + '/' + t;
                                    ActionQueue.push(temp);
                                } else {
                                    std::cout << "Invalid Lesson/Student Try Again\n";
                                    validr = true;
                                }
                            }
                                break;
                            case 13: {   //Lesson From Class
                                std::string cc,uc,t;
                                std::cout << "Class Code: \n";
                                std::getline(std::cin,cc);
                                std::cout << "UC Code: \n";
                                std::getline(std::cin,uc);
                                std::cout << "Type: \n";
                                std::getline(std::cin,t);
                                if(validate_Class(cc)&&validate_UC(uc)) {
                                    temp += '/' + cc + '/' + uc;
                                    ActionQueue.push(temp);
                                } else {
                                    std::cout << "Invalid Lesson/Class Try Again\n";
                                    validr = true;
                                }
                            }
                                break;
                            case 14: {   //Student
                                std::string element;
                                std::cout << "Student Code: \n";
                                std::getline(std::cin,element);
                                if (validate_Student(element)) {
                                    temp += ('/' + element);
                                    ActionQueue.push(temp);
                                }else {
                                    std::cout << "Invalid Student Code Try Again\n";
                                    validr = true;
                                }
                            }
                                break;
                            case 15: {   //Class
                                std::string element;
                                std::cout << "Class Code: \n";
                                std::getline(std::cin,element);
                                if (validate_Class(element)) {
                                    temp += ('/' + element);
                                    ActionQueue.push(temp);
                                }else {
                                    std::cout << "Invalid Class Code Try Again\n";
                                    validr = true;
                                }
                            }
                                break;
                            case 16: {   //UC
                                std::string element;
                                std::cout << "UC Code: \n";
                                std::getline(std::cin,element);
                                if (validate_UC(element)) {
                                    temp += ('/' + element);
                                    ActionQueue.push(temp);
                                }else {
                                    std::cout << "Invalid UC Code Try Again\n";
                                    validr = true;
                                }
                            }
                                break;
                        }
                    }
                }
            }
            continue;
        }else if(inputuser=="Undo Action")
        {

        }else if(inputuser=="Exit") {
            break;
        }
        else
        {
            std::cout << "              Invalid input Try Again\n";
        }
    }
    std::cout <<"Action Queue: ";
    for(int x=0;x<=ActionQueue.size();x++)
    {
        std::cout <<ActionQueue.front()<<'\n';
        ActionQueue.pop();
    }
    // stores values back in the files(students_classes.csv,classes.csv,classes_per_uc.csv)
    save();

    return 0;
}

void set_up_students()
{
    // stores values from students_classes.csv
    std::fstream fin;
    fin.open("../schedule/students_classes.csv",std::ios::in);
    std::string line,StudentCode,StudentName,UcCode,ClassCode;
    std::getline(fin,line);
    while(getline(fin, line)) {
        std::stringstream str(line);
        getline(str, StudentCode, ','); // gets the StudentCode
        getline(str, StudentName, ','); // gets the StudentName
        getline(str, UcCode, ','); // gets the UcCode
        getline(str, ClassCode, ','); // gets the ClassCode

        if(!in_vec(StudentsList,Student(StudentCode,StudentName)))
        {
            std::vector<Lesson> temp=get_Lessons(ClassCode,UcCode,"ALL");
            StudentsList.emplace_back(StudentCode,StudentName, temp);
        }
        else
        {
            for(auto &x:StudentsList)
            {
                if(x.get_StudentCode()==StudentCode)
                {
                    for(auto y: get_Lessons(ClassCode,UcCode,"ALL"))
                    {
                        x.add_Lesson(y);
                    }
                }
            }
        }
    }
    fin.close();
}

void set_up_classes()
{
    // stores values from classes.csv
    std::fstream fin;
    fin.open("../schedule/classes.csv",std::ios::in);
    std::string line,ClassCode,UcCode,Weekday,sh,d,Type;
    float StartHour,Duration;
    std::getline(fin,line);
    while(getline(fin, line)) {
        std::stringstream str(line);
        getline(str, ClassCode, ','); // gets the ClassCode
        getline(str, UcCode, ','); // gets the UCcode
        getline(str, Weekday, ','); // gets the Weekday
        getline(str, sh, ','); // gets the StartHour as string
        getline(str, d, ','); // gets the Duration as string
        getline(str, Type, ','); // gets the Type
        StartHour = std::stof(sh);
        Duration = std::stof(d);

        bool temp = false;
        for (auto& c: classes) { // adds a Lesson to an existing Class and cheks if it already exists
            if (c.get_ClassCode() == ClassCode)
            {
                c.add_lesson(Lesson(StartHour, Duration, Type, Weekday,UcCode,ClassCode));
                temp = true;
                break;
            }
        }
        if (!temp) // adds a new Class
        {
            std::vector<Lesson> tempv;
            tempv.emplace_back(StartHour, Duration, Type, Weekday,UcCode,ClassCode);
            classes.emplace_back(Schedule(tempv), ClassCode);
        }
    }
    fin.close();
}

void set_up_classes_per_uc()
{
    // stores values from classes_per_uc.csv
    std::fstream fin;
    fin.open("../schedule/classes_per_uc.csv",std::ios::in);
    std::string line,UcCode,ClassCode;
    std::getline(fin,line);
    while(getline(fin, line))
    {
        std::stringstream str(line);
        getline(str, UcCode, ','); // gets the UCcode
        getline(str, ClassCode, ','); // gets the Classcode
        if(!in_map(UCs,UcCode)) // see if there is already the UCcode in the map
        {
            std::vector<std::string> temp;
            temp.push_back(ClassCode);
            UCs[UcCode] = temp;
        }
        else // else adds a new key to the map with a UCcode and a vector as an element
        {
            std::vector<std::string> temp;
            temp=UCs[UcCode];
            temp.push_back(ClassCode);
            UCs[UcCode]=temp;
        }
    }
    fin.close();
}

Class& get_CLass(std::string ClassCode)
{
    for(auto &x:classes)
    {
        if(x.get_ClassCode()==ClassCode)
            return x;
    }
    // Handle the case where the Class with the specified ClassCode is not found
    throw std::runtime_error("Class not found for given ClassCode.");
}

Student get_Student(std::string StudentCode)
{
    for(auto x:StudentsList)
    {
        if(x.get_StudentCode()==StudentCode)
        {
            return x;
        }
    }

    // Handle the case where the student with the specified StudentCode is not found
    throw std::runtime_error("Student not found for given StudentCode.");
}

std::vector<Lesson> get_Lessons(std::string ClassCode,std::string UCcode,std::string Type)
{
    Class temp= get_CLass(ClassCode);
    if(Type=="ALL")
    {
        std::vector<Lesson> tempv;
        for(auto x:temp.get_Schedule().get_Schedule())
        {
            if(x.get_UCcode()==UCcode)
            {
                tempv.emplace_back(x);
            }
        }
        return tempv;
    } else
    {
        std::vector<Lesson> tempv;
        for(auto x:temp.get_Schedule().get_Schedule())
        {
            if(x.get_UCcode()==UCcode&&x.get_Type()==Type)
            {
                tempv.emplace_back(x);
            }
        }
        return tempv;
    }

    // Handle the case where the lesson with the specified UCcode is not found
    throw std::runtime_error("Lesson not found for given UCcode.");
}

template<typename T>
bool in_vec( std::vector<T> vec, T s)
{
    for(auto x:vec)
    {
        if(x==s)
        {
            return true;
        }
    }
    return false;
}

template<typename T, typename A>
bool in_map( std::map<T ,A> map,T s)
{
    for(auto x:map)
    {
        if(x.first==s)
        {
            return true;
        }
    }
    return false;
}

void save() {
    {
        //stores values from students_classes.csv
        std::fstream fin;
        fin.open("../schedule/students_classes.csv", std::ofstream::out | std::ofstream::trunc);
        fin << "StudentCode,StudentName,UcCode,ClassCode\n";
        for (auto x: StudentsList) {
            for (auto y: x.get_Horario().get_Schedule()) {
                fin << x.get_StudentCode() << "," << x.get_StudentName() << "," << y.get_UCcode() << ","<< y.get_ClassCode() << "\n";
            }
        }
        fin.close();
    }

    {
        //stores values from classes.csv
        std::fstream fin;
        fin.open("../schedule/classes.csv", std::ofstream::out | std::ofstream::trunc);
        fin << "ClassCode,UcCode,Weekday,StartHour,Duration,Type\n";
        for (auto x: classes) {
            for (auto y: x.get_Schedule().get_Schedule()) {
                fin << x.get_ClassCode() << "," << y.get_UCcode() << "," << y.get_Day() << "," << y.get_Start_hour()<< "," << y.get_Duration() << "," << y.get_Type() << "\n";
            }
        }
        fin.close();
    }

    {
        //stores values from classes_per_uc.csv
        std::fstream fin;
        fin.open("../schedule/classes_per_uc.csv", std::ofstream::out | std::ofstream::trunc);
        fin << "UcCode,ClassCode\n";
        for (auto x: UCs) {
            for (auto y: x.second) {
                fin << x.first << "," << y << "\n";
            }
        }
        fin.close();
    }
}

bool validate_UC(std::string UCcode)
{
    try {
        UCs.at(UCcode);
        return true;
    }
    catch (std::runtime_error &e) {
        return false;
    }
}
bool validate_Class(std::string ClassCode)
{
    try {
        get_CLass(ClassCode);
        return true;
    }
    catch (std::runtime_error &e) {
        return false;
    }
}
bool validate_Student(std::string StudentCode)
{
    try {
        get_Student(StudentCode);
        return true;
    }catch (std::runtime_error &e) {
        return false;
    }
}
bool validate_Lesson(std::string UCcode,std::string ClassCode,std::string Type)
{
    try
    {
        get_Lessons(ClassCode,UCcode,Type);
        return true;
    }
    catch (std::runtime_error &e)
    {
        return false;
    }
}
bool validate_Lesson_Structure(Lesson l)
{
    return true;
}
bool validate_Student_Structure(Student s)
{
    return true;
}

