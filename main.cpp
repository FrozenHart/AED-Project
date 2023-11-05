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
#include <set>
#include <cmath>

std::vector<Class> classes;
std::map<std::string, std::vector<std::string>> UCs; //map<UCcode,vector<Class Codes>>
std::vector<Student> StudentsList;
std::set <std::string> StudentsCodes;
std::vector<std::string> PastActions;
std::vector<std::string> dias={"Monday","Tuesday","Wednesday","Thursday","Friday"};
int Class_Capacity=30;

//funcions
template<typename T, typename A>
bool in_map( std::map<T ,A> map,T s);
bool checkbalance(std::string metodo,std::string sc="",std::string cc="",std::string uc="",std::string fcc="") ;
void Trade_class(std::string sc,std::string old_class,std::string new_class,std::string uc);
void Trade_UC(std::string sc,std::string old_uc,std::string new_uc,std::string classcode);
bool checkbalance_Schedule(Schedule s,std::vector<Lesson> l);
void merge_students(std::vector<Student> &StudentsLists,int left, int mid, int right) ;
void merge_sort_students(std::vector<Student> &StudentsLists,int left,int right);
void merge_sort_students(std::vector<Student> &StudentsLists);
Student &BinarySearch(std::vector<Student> &list,std::string SC);
template<typename T>
bool in_vec( std::vector<T> vec, T s);
void set_up_classes_per_uc();
void set_up_classes();
void set_up_students();
Class& get_CLass(std::string ClassCode);
std::vector<Lesson> get_Lessons(std::string ClassCode,std::string UCcode,std::string Type="T");
Student &get_Student(std::string StudentCode);
bool validate_UC(std::string UCcode);
bool validate_Class(std::string ClassCode);
bool validate_Student(std::string StudentCode);
bool validate_Lesson_Structure(std::string start_hour,std::string duration,std::string Type,std::string Day,std::string UCcode,std::string ClassCode,bool new_class,bool new_UC);
bool validate_Student_Structure(std::string StudentCode,std::string StudentName);
bool validate_Lesson(std::string UCcode,std::string ClassCode,std::string Type="T");
void save();
void set_up_past_actions();
bool validate_hour(std::string hour);
void remove_Student(std::string StudentCode);
void remove_Class(std::string ClassCode);
void remove_UC(std::string UCcode);
bool validate_Day(std::string Day);
bool validate_Type(std::string Type);
bool valdate_StudentCode(std::string StudentCode);
float unformathour(std::string h);

//main
int main(int argc, char *argv[]) {
    // stores values from classes_per_uc.csv
    set_up_classes_per_uc();
    /*std::cout << "Classes per uc done" << std::endl;
    for(auto x:UCs)
    {
        std::cout << x.first << " -> ";
        for(auto y:x.second)
        {
            std::cout << y << " ";
        }
        std::cout << '\n';
    }*/
    // stores values from classes.csv
    set_up_classes();
    /*std::cout << "Classes done" << std::endl;
    for(auto x:classes)
    {
        std::cout << x.get_ClassCode() << " -> ";
        for(auto y:x.get_Schedule().get_Schedule())
        {
            std::cout << y.get_UCcode() << " ";
        }
        std::cout << '\n';
    }*/
    // stores values from students_classes.csv
    set_up_students();
    /*std::cout << "Students done" << std::endl;
    for(auto x:StudentsList)
    {
        std::cout << x.get_StudentCode()<<" -> "<<x.get_StudentName() << " ; " <<'\n'<< x.get_Horario().print() << '\n';
    }*/

    set_up_past_actions();

    //User Interface
    static std::map<std::string,int> OperationValue{{"Check",0},
                                                    {"Add",1},
                                                    {"Remove",2},
                                                    {"Past Actions",3}};

    static std::map<std::string, int> MethodValue{{"Student Schedule",   0},
                                                  {"Class Schedule",   1},
                                                  {"Lesson",   2},
                                                  {"Lessons From Class",   3},
                                                  {"Lessons From UC",   4},
                                                  {"Classes From UC",   5},
                                                  {"Students From UC",   6},
                                                  {"Lesson to UC",   7}, // add
                                                  {"Lesson to Student",   8},
                                                  {"Student",   9},
                                                  {"Class",   10},
                                                  {"UC",   11},
                                                  {"Lesson From Student",   12}, // remove
                                                  {"Lesson From Class",   13},
                                                  {"Remove Student",   14},
                                                  {"Remove Class",   15},
                                                  {"Remove UC",   16},
                                                  {"UCs",    17}, // Switch
                                                  {"Classes", 18},
                                                  {"List of UC",19}};

    std::queue<std::string> ActionQueue;
        std::cout<<"----------------------------------------------------------------------------------\n";
        std::cout<<"                        Welcome to the Schedule Manager\n";

    while (true) {
        std::string inputuser;
        std::cout<<"                             Chose an Operation\n";
        std::cout<<"-----------------------------------------------------------------------------------\n";
        std::cout<<"|  Check  |  Add  |  Remove  | Switch |  Past Actions  |  Run  |  Queue  |  Exit  |\n";
        std::cout<<"-----------------------------------------------------------------------------------\n";

        getline(std::cin,inputuser);
        if(inputuser=="Check")
        {
            std::string method;
            bool c= true;
            while (c) {
                c=false;
                std::cout<<"                          Choose Check Method\n";
                std::cout<<"-----------------------------------------------------------------------------\n";
                std::cout<<"| Student Schedule   -> Checks a Student Schedule                           |\n";
                std::cout<<"| Class Schedule     -> Checks a Class Schedule                             |\n";
                std::cout<<"| Lesson             -> Checks the time of The Lessons From a UC in a Class |\n";
                std::cout<<"| Lessons From Class -> Checks all the Lessons time and Type from a Class   |\n";
                std::cout<<"| Lessons From UC    -> Checks all the Lessons time and type from UC        |\n";
                std::cout<<"| Classes From UC    -> Checks all the Classes from a UC                    |\n";
                std::cout<<"| Students From UC   -> Checks all the Students from a UC                   |\n";
                std::cout<<"| List of UC         -> Checks all the UCs in the System                    |\n";
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
                    bool validc = true;
                    while (validc) {
                        validc = false;
                        switch (MethodValue[method]) {
                            case 0: {   //Student Schedule
                                std::string element;
                                std::cout << "Student Code: \n";
                                std::getline(std::cin,element);
                                if (validate_Student(element)) {
                                    std::cout <<get_Student(element).get_StudentName()<<" Schedule "<<'\n';
                                    std::cout << get_Student(element).get_Horario().print() <<'\n';
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
                                    std::cout << element << " Schedule "<<'\n';
                                    std::cout << get_CLass(element).get_Schedule().print() <<'\n';
                                }else {
                                    std::cout << "Invalid Class Code Try Again\n";
                                    validc = true;
                                }
                            }
                                break;
                            case 2: {   //Lesson
                                std::string element1, element2,t;
                                std::cout << "UC Code: \n";
                                std::getline(std::cin,element1);
                                std::cout << "Class Code: \n";
                                std::getline(std::cin,element2);
                                std::cout << "Type: \n";
                                std::getline(std::cin,t);
                                if(validate_Lesson(element1,element2)) {
                                    std::cout << "Lesson From " << element1 << " in Class " << element2 << '\n';
                                    for(auto x:get_Lessons(element2,element1,t))
                                    {
                                        std::cout << x.print() ;
                                    }
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
                                    std::cout << "Lessons From Class " << element << '\n';
                                    std::cout << "------------------------------------------------------------------------------------------------------\n";
                                    std::cout << "| Weekday | UCcode | Type | Start | Finish |\n";
                                    std::cout << "------------------------------------------------------------------------------------------------------\n";
                                    for(auto x:get_CLass(element).get_Schedule().get_Schedule())
                                    {
                                        std::cout << x.print() ;
                                    }
                                    std::cout <<  "------------------------------------------------------------------------------------------------------\n";

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
                                    std::cout <<"Class "<< "Class Code" << " Schedule "<<'\n';
                                    std::cout << "------------------------------------------------------------------------------------------------------\n";
                                    std::cout << "| Weekday | UCcode | Type | Start | Finish |\n";
                                    std::cout << "------------------------------------------------------------------------------------------------------\n";
                                    for(auto x:UCs[element])
                                    {
                                        std::cout <<"Class "<< x << " Schedule "<<'\n';
                                        for(auto y:get_CLass(x).get_Schedule().get_Schedule())
                                        {
                                            if(y.get_UCcode()==element)
                                                std::cout << y.print() ;
                                        }
                                        std::cout <<  '\n';
                                    }
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
                                    std::cout << "Classes From " << element << '\n';
                                    for(auto x:UCs[element])
                                    {
                                        std::cout << x << " | ";
                                    }
                                    std::cout << '\n';
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
                                    std::cout << "Students From " << element <<'\n';
                                    std::vector<std::string> classesuc = UCs[element];
                                    for(auto x:classesuc)
                                    {
                                        std::cout << "Class " << x << " Students \n";
                                        for(auto y: get_CLass(x).get_ListStudents())
                                        {
                                            std::cout << y.print_Student() << " | ";
                                        }
                                        std::cout << "\n\n";
                                    }
                                }else {
                                    std::cout << "Invalid UC Code Try Again\n";
                                    validc = true;
                                }
                            }
                                break;
                            case 19:{  //List of UC
                                std::cout << "List of UCs\n";
                                for(auto x:UCs)
                                {
                                    std::cout << x.first << " | ";
                                }
                                std::cout << '\n';
                            }
                                break;

                            default:
                                std::cout << "Invalid Method Try Again\n";
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
                std::cout<<"| Class             -> Adds a Class to the System                    |\n";
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
                                std::cout << "Weekday: (Monday,Tuesday,Wednesday,Thursday,Friday)\n";
                                std::getline(std::cin,w);
                                std::cout << "Start Hour: (xx:xx) \n";
                                std::getline(std::cin,sh);
                                std::cout << "Duration: (xx:xx)\n";
                                std::getline(std::cin,d);
                                std::cout << "Type: (T,TP,PL)\n";
                                std::getline(std::cin,t);
                                if(validate_Lesson_Structure(sh, d, t, w, uc, cc, false, false)) {
                                    temp += '/' + uc + '/' + cc + '/' + w + '/' + sh + '/' + d + '/' + t+'/';
                                    ActionQueue.push(temp);
                                }else {
                                    std::cout << "Invalid Lesson Structure Try Again\n";
                                    valida = true;
                                }
                            }
                                break;
                            case 8: {   //Lesson to Student
                                std::string uc, cc, sc,t;
                                std::cout << "Student Code: \n";
                                std::getline(std::cin,sc);
                                std::cout << "UC Code: \n";
                                std::getline(std::cin,uc);
                                std::cout << "Class Code: \n";
                                std::getline(std::cin,cc);
                                std::cout << "Type: (T,TP,PL)\n";
                                std::getline(std::cin,t);
                                if(validate_Lesson(uc,cc,t)&&validate_Student(sc))
                                {
                                    if(checkbalance_Schedule(get_Student(sc).get_Horario(),get_Lessons(cc,uc,t))&&checkbalance("Class_Space","",cc)&&checkbalance("UC_Space",sc,"",uc)&&checkbalance("Normal_Class_Balance",sc,cc)){
                                        temp += '/' + sc + '/' + uc + '/' + cc + '/' + t + '/';
                                        ActionQueue.push(temp);
                                    }else {
                                        std::cout << "Class Full or cant have more UCs Try Again\n";
                                        valida = true;
                                    }

                                }else {
                                    std::cout << "Invalid Lesson/Student Try Again\n";
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
                                if(validate_Student_Structure(sc,sn)) {
                                    temp += ('/' + sc + '/' + sn+'/');
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
                                std::cout << "How Many NEW Lessons? \n";
                                std::getline(std::cin,n);
                                if((!validate_hour(n))||std::stoi(n)<=0)
                                {
                                    std::cout << "Invalid Number of Lessons Try Again\n You need to have at least 1 Lesson\n";
                                    valida = true;
                                }
                                else
                                {
                                    temp += '/' + cc + '/' + n;
                                    int x=0;
                                    Schedule te;
                                    while(x<std::stoi(n))
                                    {
                                        std::cout << "Lesson " << x+1 << '\n';
                                        std::string sh, d, t, w, uc;
                                        std::cout << "UC Code: \n";
                                        std::getline(std::cin,uc);
                                        std::cout << "Weekday: (Monday,Tuesday,Wednesday,Thursday,Friday)\n";
                                        std::getline(std::cin,w);
                                        std::cout << "Start Hour: (xx:xx)\n";
                                        std::getline(std::cin,sh);
                                        std::cout << "Duration: (xx:xx)\n";
                                        std::getline(std::cin,d);
                                        std::cout << "Type: (T,TP,PL)\n";
                                        std::getline(std::cin,t);
                                        if(validate_Lesson_Structure(sh,d, t, w, uc, cc, true, false))
                                        {
                                            std::vector<Lesson> h;
                                            h.emplace_back(unformathour(sh), unformathour(d), t, w, uc, cc);
                                            if(checkbalance_Schedule(te,h)) {
                                                te.add_Lesson(Lesson(unformathour(sh), unformathour(d), t, w, uc, cc));
                                                temp += '/' + uc + '/' + w + '/' + sh + '/' + d + '/' + t + '/';
                                                x++;
                                            }else {
                                                std::cout << "Lesson Overlay Try Again\n";
                                            }
                                        }else {
                                            std::cout << "Invalid Lesson Structure Try Again\n";
                                        }
                                    }
                                    ActionQueue.push(temp);
                                }
                            }
                                break;
                            case 11: {   //UC
                                std::string uc,n;
                                std::cout << "UC Code: \n";
                                std::getline(std::cin,uc);
                                std::cout << "How Many NEW Lessons? \n";
                                std::getline(std::cin,n);
                                if((!validate_hour(n))||std::stoi(n) <= 0)
                                {
                                    std::cout << "Invalid Number of Lessons Try Again\n You need to have at least 1 Lesson\n";
                                    valida = true;
                                }
                                else {
                                    temp += '/' + uc + '/' + n;
                                    int x = 0;
                                    while (x < std::stoi(n)) {
                                        std::cout << "Lesson " << x+1 << '\n';
                                        std::string sh, d, t, w, cc;
                                        std::cout << "Class Code: \n";
                                        std::getline(std::cin, cc);
                                        std::cout << "Weekday: (Monday,Tuesday,Wednesday,Thursday,Friday)\n";
                                        std::getline(std::cin, w);
                                        std::cout << "Start Hour: (xx:xx)\n";
                                        std::getline(std::cin, sh);
                                        std::cout << "Duration: (xx:xx)\n";
                                        std::getline(std::cin, d);
                                        std::cout << "Type: (T,TP,PL)\n";
                                        std::getline(std::cin, t);
                                        if (validate_Lesson_Structure(sh,d, t, w, uc, cc, false,true)) {
                                            temp += '/' + cc + '/' + w + '/' + sh + '/' + d + '/' + t + '/';
                                            x++;
                                        } else {
                                            std::cout << "Invalid Lesson Structure Try Again\n";
                                        }
                                    }
                                    ActionQueue.push(temp);
                                }
                            }
                                break;
                            default:
                                std::cout << "Invalid Method Try Again\n";
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
                std::cout<<"| Lesson From Student  -> Removes a Lesson from a Student Schedule |\n";
                std::cout<<"| Lesson From Class    -> Removes a Lesson from a Class Schedule   |\n";
                std::cout<<"| Remove Student       -> Removes a Student from the System        |\n";
                std::cout<<"| Remove Class         -> Removes a Class from the System          |\n";
                std::cout<<"| Remove UC            -> Removes a UC from the System             |\n";
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
                                std::string uc,sc,t,cc;
                                std::cout << "Student Code: \n";
                                std::getline(std::cin,sc);
                                std::cout << "UC Code: \n";
                                std::getline(std::cin,uc);
                                std::cout << "Class Code: \n";
                                std::getline(std::cin,cc);
                                std::cout << "Type: \n";
                                std::getline(std::cin,t);
                                if(validate_Student(sc)&&validate_UC(uc)&&validate_Lesson(uc,cc,t)) {
                                    temp += '/' + sc + '/' + uc + '/' + t+'/'+cc;
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
                                    temp += '/' + cc + '/' + uc+'/'+t;
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
                            default:
                                std::cout << "Invalid Method Try Again\n";
                                break;
                        }
                    }
                }
            }
            continue;
        }else if(inputuser=="Switch")
        {
            std::string method;
            bool a= true;
            while (a) {
                a=false;
                std::cout<<"                      Chose Switch Method\n";
                std::cout<<"----------------------------------------------------------------\n";
                std::cout<<"| UCs      -> Changes a Student previous UC to a new UC        |\n";
                std::cout<<"| Classes  -> Changes a Student previous Class to a new Class  |\n";
                std::cout<<"| Back                                                         |\n";
                std::cout<<"----------------------------------------------------------------\n";

                getline(std::cin, method);
                if (method=="Back") {
                    continue;
                }else if(!in_map(MethodValue, method))
                {
                    std::cout << "Invalid Method Try Again\n";
                    a=true;
                }
                else {
                    std::string temp = "Switch/" + method;
                    bool valids = true;
                    while (valids) {
                        valids = false;
                        switch (MethodValue[method]) {
                            case 17: {   //UCs
                                std::string puc,nuc,sc,uc;
                                std::cout << "Student Code: \n";
                                std::getline(std::cin,sc);
                                std::cout << "Previous UC Code: \n";
                                std::getline(std::cin,puc);
                                std::cout << "New UC Code: \n";
                                std::getline(std::cin,nuc);
                                std::string classcode;
                                std::cout << "Witch Class?(Class Code): \n";
                                std::getline(std::cin,classcode);
                                if (validate_UC(puc)&&(validate_UC(nuc))&&(validate_Student(sc))&&checkbalance("New_UC",sc)&&checkbalance("New_UC_Class",sc,"",nuc)&&validate_Class(classcode)){
                                    Schedule s=get_Student(sc).get_Horario();
                                    bool pode= true;
                                    for(auto x : s.get_Schedule())
                                    {
                                        if(x.get_UCcode()==puc)
                                        {
                                            s.remove_Lesson(x);
                                        }
                                    }
                                    for(auto x: get_Lessons(classcode,nuc,"ALL"))
                                    {
                                        if(checkbalance_Schedule(s,{x})) {
                                            s.add_Lesson(x);
                                        }
                                        else
                                        {
                                            pode= false;
                                            break;
                                        }
                                    }
                                    std::cout << s.print()<<'\n';
                                    std::cout << get_Student(sc).get_Horario().print()<<'\n';

                                    if(pode) {
                                        temp += ('/' + sc + '/' + puc + '/' + nuc + '/' + classcode);
                                        ActionQueue.push(temp);
                                    }
                                    else
                                    {
                                        std::cout << "Lesson Overlay Try Again\n";
                                        valids = true;
                                    }
                                }else {
                                    std::cout << "Invalid UC Code/Student Code Try Again\n";
                                    valids = true;
                                }
                            }
                                break;
                            case 18: {   //Classes
                                std::string pcc,ncc,sc;
                                std::cout << "Student Code: \n";
                                std::getline(std::cin,sc);
                                std::cout << "Previous Class Code: \n";
                                std::getline(std::cin,pcc);
                                std::cout << "New Class Code: \n";
                                std::getline(std::cin,ncc);
                                std::string uc;
                                std::cout << "Which UC?(UC Code): \n";
                                std::getline(std::cin,uc);
                                if (validate_Class(pcc)&&(validate_Class(ncc))&&(validate_Student(sc))&& validate_UC(uc)) {

                                    Schedule s= get_Student(sc).get_Horario();
                                    bool pode= true;
                                    for(auto x : s.get_Schedule())
                                    {
                                        if(x.get_ClassCode()==pcc)
                                        {
                                            s.remove_Lesson(x);
                                        }
                                    }
                                    for(auto x: get_Lessons(ncc,uc,"ALL"))
                                    {
                                        if(checkbalance_Schedule(s,{x})) {
                                            s.add_Lesson(x);
                                        }
                                        else
                                        {
                                            pode= false;
                                            break;
                                        }
                                    }
                                    std::cout << s.print()<<'\n';
                                    std::cout << get_Student(sc).get_Horario().print()<<'\n';
                                    if(pode) {
                                        temp += ('/' + sc + '/' + pcc + '/' + ncc + '/' + uc);
                                        ActionQueue.push(temp);
                                    }
                                    else
                                    {
                                        std::cout << "Lesson Overlay Try Again\n";
                                        valids = true;
                                    }
                                }else {
                                    std::cout << "Invalid UC Code/Student Code Try Again\n";
                                    valids = true;
                                }
                            }
                                break;
                            default:
                                std::cout << "Invalid Method Try Again\n";
                                break;
                        }
                    }
                }
            }
            continue;
        }else if(inputuser=="Past Actions")
        {
            std::cout <<"Action System Log \n";
            for(auto x:PastActions) {
                std::cout << x << '\n';
            }
        }else if(inputuser=="Run")
        {
            std::queue<std::string> tempa=ActionQueue;
            int v=tempa.size();
            for(int i=0;i<v;i++)
            {
                PastActions.push_back(tempa.front());
                tempa.pop();
            }

            std::cout <<"Running Actions ... \n";
            int nt=ActionQueue.size();
            for (int x = 0; x < nt; x++)
            {
                std::string acao=ActionQueue.front();
                std::stringstream ss(acao);
                std::string temp;
                getline(ss,temp,'/');
                std::string method ;
                getline(ss,method,'/');
                switch (MethodValue[method])
                {
                    case 7: //Add Lesson to UC
                        {
                            std::string uc,cc,w,sh,d,t;
                            getline(ss,uc,'/');
                            getline(ss,cc,'/');
                            getline(ss,w,'/');
                            getline(ss,sh,'/');
                            getline(ss,d,'/');
                            getline(ss,t,'/');
                            UCs[uc].emplace_back(cc);
                            get_CLass(cc).add_lesson(Lesson(unformathour(sh), unformathour(d),t,w,uc,cc));
                        }
                        break;
                    case 8: //Add Lesson to Student
                    {
                        std::string sc,uc,cc,t;
                        getline(ss,sc,'/');
                        getline(ss,uc,'/');
                        getline(ss,cc,'/');
                        getline(ss,t,'/');
                        for (auto l: get_Lessons(cc, uc, t))
                        {
                            get_Student(sc).add_Lesson(l);
                        }
                    }
                        break;
                    case 9: //Add Student
                    {
                        std::string sc,sn;
                        getline(ss,sc,'/');
                        getline(ss,sn,'/');
                        StudentsCodes.insert(sc);
                        StudentsList.emplace_back(sc,sn);
                    }
                        break;
                    case 10: //Add Class
                    {
                        std::string cc,n;
                        getline(ss,cc,'/');
                        getline(ss,n,'/');
                        classes.emplace_back(Schedule(),cc);//empty schedule
                        bool first= true;
                        for(int i = 0; i < std::stoi(n); i++)
                        {
                            std::string uc,w,sh,d,t;
                            getline(ss,uc,'/');
                            getline(ss,w,'/');
                            getline(ss,sh,'/');
                            getline(ss,d,'/');
                            getline(ss,t,'/');
                            get_CLass(cc).add_lesson(Lesson(std::stof(sh),std::stof(d),t,w,uc,cc));
                            if(first)
                            {
                                UCs[uc].emplace_back(cc);
                                first= false;
                            }
                        }
                    }
                        break;
                    case 11: //Add UC
                    {
                        std::string uc ,n;
                        getline(ss,uc,'/');
                        getline(ss,n,'/');
                        std::vector<std::string> temp;
                        for(int x=0;x<std::stoi(n);x++)
                        {
                            std::string cc,w,sh,d,t;
                            getline(ss,cc,'/');
                            getline(ss,w,'/');
                            getline(ss,sh,'/');
                            getline(ss,d,'/');
                            getline(ss,t,'/');
                            temp.push_back(cc);
                            get_CLass(cc).add_lesson(Lesson(std::stof(sh),std::stof(d),t,w,uc,cc));
                        }
                        UCs.insert({uc,temp});
                    }
                        break;
                    case 12: //Remove Lesson From Students
                    {
                        std::string uc,sc,t,cc;
                        getline(ss,sc,'/');
                        getline(ss,uc,'/');
                        getline(ss,t,'/');
                        getline(ss,cc,'/');
                        if(t=="T")
                        {
                            for(auto aula: get_Lessons(cc, uc, t))
                            {
                                get_Student(sc).remove_Lesson(aula);
                            }
                        } else
                            get_Student(sc).remove_Lesson(get_Lessons(cc, uc, t)[0]);
                    }
                        break;
                    case 13: //Remove Lesson From Class
                    {
                        std::string cc,uc,t;
                        getline(ss,cc,'/');
                        getline(ss,uc,'/');
                        getline(ss,t,'/');
                        for (auto aula: get_Lessons(cc, uc, t)){
                            get_CLass(cc).remove_lesson(aula);
                        }
                    }
                        break;
                    case 14: //Remove Student
                    {
                        std::string sc ;
                        getline(ss,sc,'/');
                        remove_Student(sc);
                    }
                        break;
                    case 15: //Remove Class
                    {
                        std::string cc ;
                        getline(ss,cc,'/');
                        remove_Class(cc);
                    }
                        break;
                    case 16: //Remove UC
                    {
                        std::string uc;
                        getline(ss,uc,'/');
                        remove_UC(uc);
                    }
                        break;
                    case 17: //Switch UCs
                    {
                        std::string sc, puc, nuc,wcc;
                        getline(ss, sc, '/');
                        getline(ss, puc, '/');
                        getline(ss, nuc, '/');
                        getline(ss, wcc, '/');
                        Trade_UC(sc, puc, nuc,wcc);
                    }
                        break;
                    case 18: //Switch Classes
                    {
                        std::string sc, pcc, ncc,wuc;
                        getline(ss, sc, '/');
                        getline(ss, pcc, '/');
                        getline(ss, ncc, '/');
                        getline(ss, wuc, '/');
                        Trade_class(sc, pcc, ncc,wuc);
                    }
                        break;
                }
                ActionQueue.pop();
            }
            std::cout <<"Actions Done \n";

        } else if(inputuser=="Queue")
        {
            if(ActionQueue.size()==0)
                std::cout <<"Action Queue is Empty\n";
            else {
                std::queue<std::string> temp = ActionQueue;
                std::cout << "Action Queue: "<<'\n';
                int nt=temp.size();
                for (int x = 0; x < nt; x++) {
                    std::cout << temp.front() << '\n';
                    temp.pop();
                }
            }
        }
        else if(inputuser=="Exit") {
            break;
        }
        else
        {
            std::cout << "              Invalid input Try Again\n";
        }
    }


    // stores values back in the files(students_classes.csv,classes.csv,classes_per_uc.csv)
    save();

    return 0;
}

void set_up_students()
{
    // stores values from students_classes.csv
    std::fstream fin;
    fin.open("../Original Data/schedule/students_classes.csv",std::ios::in);
    std::string line,StudentCode,StudentName,UcCode,ClassCode,Type;
    std::getline(fin,line);
    bool nfirst= false;
    if(line.find("Type")!=std::string::npos)  // checks if the file has the Type column
        nfirst= true;
    while(getline(fin, line)) {
        std::stringstream str(line);
        getline(str, StudentCode, ','); // gets the StudentCode
        getline(str, StudentName, ','); // gets the StudentName
        getline(str, UcCode, ','); // gets the UcCode
        getline(str, ClassCode, ','); // gets the ClassCode
        if(nfirst)
        {
            getline(str, Type, ','); // gets the Type
        }
        if(!in_vec(StudentsList,Student(StudentCode,StudentName))) // new student
        {
            StudentsCodes.insert(StudentCode);
            std::vector<Lesson>temp;
            if(nfirst)
            {
                temp=get_Lessons(ClassCode,UcCode,Type);
            }
            else
            {
                temp=get_Lessons(ClassCode,UcCode,"ALL");
            }
            StudentsList.emplace_back(StudentCode,StudentName, temp);
            get_CLass(ClassCode).add_student(StudentsList.back());
        }
        else
        {
            for(auto &x:StudentsList)
            {
                if(x.get_StudentCode()==StudentCode)
                {
                    if(nfirst)
                    {
                        for (auto y: get_Lessons(ClassCode, UcCode, Type)) {
                            x.add_Lesson(y);
                        }
                    }
                    else {
                        for (auto y: get_Lessons(ClassCode, UcCode, "ALL")) {
                            x.add_Lesson(y);
                        }
                    }
                }
            }
        }
    }
    fin.close();
}

void set_up_past_actions()
{
    std::fstream fin;
    fin.open("../schedule/ActionQueue.txt",std::ios::in);
    std::string line;
    while(getline(fin, line)) {
        PastActions.push_back(line);
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
            classes[classes.size() - 1].get_Schedule().sorted();
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
        if(x.get_ClassCode()==ClassCode) {
            return x;
        }
    }
    // Handle the case where the Class with the specified ClassCode is not found
    throw std::runtime_error("Class not found for given ClassCode.");
}

Student &BinarySearch(std::vector<Student> &list,std::string SC)
{
    int left = 0;
    int right = list.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        // Check if the middle element's StudentCode is equal to the target SC
        if (list[mid].get_StudentCode() == SC)
        {
            return list[mid];
        }

        // If the target SC is smaller, ignore the right half
        if (list[mid].get_StudentCode() > SC)
        {
            right = mid - 1;
        }
            // If the target SC is larger, ignore the left half
        else
        {
            left = mid + 1;
        }
    }

    // Handle the case where the student with the specified StudentCode is not found
    throw std::runtime_error("Student not found for given StudentCode.");
}

void merge_students(std::vector<Student> &StudentsLists,int left, int mid, int right) //joins
{
    int fsi = mid - left + 1;
    int ssi = right - mid;

    // vetores q vao ser juntados
    std::vector<Student> Left_Students(StudentsLists.begin() + left, StudentsLists.begin() + left +fsi);
    std::vector<Student> Right_Students(StudentsLists.begin() + mid + 1, StudentsLists.begin() + mid + 1 + ssi);

    int indice_1 = 0,indice_2 = 0, indice_3 = left;
    // juntar os elementos sendo o primeiro o maior
    while (indice_1 < fsi && indice_2 < ssi) {
        if (Left_Students[indice_1] < Right_Students[indice_2]) {
            StudentsLists[indice_3] = Left_Students[indice_1];
            indice_1++;
        } else {
            StudentsLists[indice_3] = Right_Students[indice_2];
            indice_2++;
        }
        indice_3++;
    }

    //junta os elementos que faltao do vetor da esquerda
    while (indice_1 < fsi) {
        StudentsLists[indice_3] = Left_Students[indice_1];
        indice_1++;
        indice_3++;
    }

    //junta os elementos que faltao do vetor da direita
    while (indice_2 < ssi) {
        StudentsLists[indice_3] = Right_Students[indice_2];
        indice_2++;
        indice_3++;
    }
}
void merge_sort_students(std::vector<Student> &StudentsLists,int left,int right)
{
    if(left<right)
    {
        int middle=(left+right)/2;
        merge_sort_students(StudentsLists,left,middle);
        merge_sort_students(StudentsLists,middle+1,right);
        merge_students(StudentsLists,left,middle,right);
    }
}
void merge_sort_students(std::vector<Student> &StudentsLists)
{
    merge_sort_students(StudentsLists,0,StudentsLists.size()-1);
}

Student &get_Student(std::string StudentCode)
{
    merge_sort_students(StudentsList);
    try {
        return  BinarySearch(StudentsList, StudentCode);
    }
    catch (std::runtime_error &e) {
        throw e;
    }
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
        if (tempv.size()!=0){return tempv;}
    } else
    {
        std::vector<Lesson> tempv;
        for(auto x:temp.get_Schedule().get_Schedule())
        {
            if(x.get_UCcode()==UCcode&&x.get_Type()==Type)
            {
                tempv.push_back(x);
            }
        }
        if (tempv.size()!=0){return tempv;}
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
    typename std::map<T ,A>::iterator it;
    it = map.find(s);
    if(it!=map.end())
    {
        return true;
    } else
        return false;
}

void save() {
    {
        //stores values from students_classes.csv
        std::fstream fin;
        std::string prevUCcode="";
        fin.open("../schedule/students_classes.csv", std::ofstream::out | std::ofstream::trunc);
        fin << "StudentCode,StudentName,UcCode,ClassCode,Type\n";
        for (auto x: StudentsList) {
            for (auto y: x.get_Horario().get_Schedule()) {
                if(prevUCcode!=y.get_UCcode()) {
                    fin << x.get_StudentCode() << "," << x.get_StudentName() << "," << y.get_UCcode() << ","<< y.get_ClassCode() <<","<< y.get_Type()<<"\n";
                    prevUCcode=y.get_UCcode();
                }
            }
        }
        fin.close();
    }

    {
        //stores values from ActionQueue.txt
        std::fstream fin;
        fin.open("../schedule/ActionQueue.txt", std::ofstream::out | std::ofstream::trunc);
        for (auto x: PastActions) {
            fin << x << "\n";
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
    catch (std::out_of_range &e) {
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

//RaquelRenata
bool validate_Lesson_Structure(std::string start_hour,std::string duration,std::string Type,std::string Day,std::string UCcode,std::string ClassCode,bool new_class,bool new_UC)
{

    if(new_class) {
        if(new_UC)
        {
            if (validate_hour(start_hour) && validate_hour(duration) && validate_Day(Day) &&validate_Type(Type)) {
                int hour = 0, minutes = 0;
                hour = std::stoi(start_hour.substr(0, start_hour.find(':')));
                minutes = std::stoi(start_hour.substr(start_hour.find(':') + 1, start_hour.size()));
                if (hour > 23 or minutes > 59) {
                    return false;
                }
            } else
                return false;
            return true;
        }else
        {
            if (validate_hour(start_hour) && validate_hour(duration)  && validate_UC(UCcode) && validate_Day(Day) &&validate_Type(Type)) {
                int hour = 0, minutes = 0;
                hour = std::stoi(start_hour.substr(0, start_hour.find(':')));
                minutes = std::stoi(start_hour.substr(start_hour.find(':') + 1, start_hour.size()));
                if (hour > 23 or minutes > 59) {
                    return false;
                }
            } else
                return false;
            return true;
        }
    }else
    {
        if(new_UC)
        {
            if (validate_hour(start_hour) && validate_hour(duration)&& validate_Class(ClassCode) && validate_Day(Day) &&validate_Type(Type)) {
                int hour = 0, minutes = 0;
                hour = std::stoi(start_hour.substr(0, start_hour.find(':')));
                minutes = std::stoi(start_hour.substr(start_hour.find(':') + 1, start_hour.size()));
                if (hour > 23 or minutes > 59) {
                    return false;
                }
            } else
                return false;
            return true;
        }else
        {
            if (validate_hour(start_hour) && validate_hour(duration) && validate_Class(ClassCode) && validate_UC(UCcode) && validate_Day(Day) &&validate_Type(Type)) {
                int hour = 0, minutes = 0;
                hour = std::stoi(start_hour.substr(0, start_hour.find(':')));
                minutes = std::stoi(start_hour.substr(start_hour.find(':') + 1, start_hour.size()));
                if (hour > 23 or minutes > 59) {
                    return false;
                }
            } else
                return false;
            return true;
        }
    }
}

bool validate_Day(std::string Day)
{
    if(in_vec(dias,Day))
        return true;
    else
        return false;
}

//RaquelRenata
bool validate_Student_Structure(std::string StudentCode,std::string StudentName)
{
    if(validate_hour(StudentCode)&&StudentCode.size()==9&&valdate_StudentCode(StudentCode))
        return true;
    return false;
}


bool validate_hour(std::string hour){
    bool two_points = true;
    for(char c : hour){
        if(c == ':' and two_points){
            two_points = false;
        }
        else if(!isdigit(c)){
            return false;
        }
    }
   return true;
}

void remove_Student(std::string StudentCode)
{
    for(size_t x=0;x<=StudentsList.size();x++)
    {
        if(StudentsList[x].get_StudentCode()==StudentCode)
        {
            StudentsList.erase(StudentsList.begin()+x, StudentsList.begin()+x+1);
            break;
        }
    }
}

void remove_Class(std::string ClassCode)
{
    for(size_t x=0;x<=classes.size();x++)
    {
        if(classes[x].get_ClassCode()==ClassCode)
        {
            classes.erase(classes.begin()+x, classes.begin()+x+1);
            break;
        }
    }
    for(auto v:UCs)
    {
        for(size_t x=0;x<=v.second.size();x++)
        {
            if(v.second[x]==ClassCode)
            {
                v.second.erase(v.second.begin()+x, v.second.begin()+x+1);
                break;
            }
        }
    }
    for (auto x:StudentsList) {
        for(auto y:x.get_Horario().get_Schedule())
        {
            if(y.get_ClassCode()==ClassCode)
            {
                x.remove_Lesson(y);
            }
        }
    }
}

void remove_UC(std::string UCcode)
{
    for(auto &x:classes)
    {
        for(auto y:x.get_Schedule().get_Schedule())
        {
            if(y.get_UCcode()==UCcode)
            {
                x.remove_lesson(y);
            }
        }
    }
    for (auto &x:StudentsList) {
        for(auto y:x.get_Horario().get_Schedule())
        {
            if(y.get_UCcode()==UCcode)
            {
                x.remove_Lesson(y);
            }
        }

    }
    UCs.erase(UCcode);
}

float unformathour(std::string h)
{   float hour=0, minutes=0;
    hour = std::stof(h.substr(0, h.find(':') ));
    minutes = std::stof(h.substr(h.find(':') + 1 ,h.size()-1));
    float sol=hour+minutes/60.0;
    return sol;
}
bool validate_Type(std::string Type)
{
    if(Type=="T"||Type=="TP"||Type=="PL")
        return true;
    else
        return false;
}
bool valdate_StudentCode(std::string StudentCode)
{
    if(StudentsCodes.find(StudentCode)==StudentsCodes.end()) {
        return true;
    }else {
        return false;
    }
}

bool checkbalance(std::string metodo,std::string sc,std::string cc,std::string uc,std::string fcc) {
    std::map<std::string, int> metodos={{"New_UC",0},
                                        {"New_UC_class",1},
                                        {"Class_Space",2},
                                        {"Switch_Class_Balance",3},
                                        {"One_Class_per_UC",4},
                                        {"Normal_Class_Balance",5}};
    switch (metodos[metodo]) {
        case 0:
        {
            std::set<std::string> ucs;
            for (auto x: get_Student(sc).get_Horario().get_Schedule()) {
                ucs.insert(x.get_UCcode());
            }
            if(ucs.size()+1>7)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
            break;
        case 1:
        {
            for (auto x: UCs[uc]) {
                if(checkbalance("Class_Space","",x))
                {
                    return true;
                }
            }
        }
            break;
        case 2:
        {
            if(get_CLass(cc).get_ListStudents().size()<Class_Capacity)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
            break;
        case 3:
        {
            int v= get_CLass(cc).get_ListStudents().size()+1,di=0,df=0,fv= get_CLass(fcc).get_ListStudents().size()+1;
            for(auto x:classes)
            {
                if(abs(v-x.get_ListStudents().size())>di) {
                    di = abs(v - x.get_ListStudents().size());
                }
            }
            if(di<4)
            {
                return true;
            } else
            {
                for(auto x:classes)
                {
                    if(abs(fv-x.get_ListStudents().size())>df) {
                        df = abs(v - x.get_ListStudents().size());
                    }
                }
                return df<di;
            }
        }
        break;

        case 4:
        {
            for(auto x:get_Student(sc).get_Horario().get_Schedule())
            {
                if(x.get_UCcode()==uc)
                {
                    return false;
                }
            }
        }
        break;

        case 5:
        {
            int v= get_CLass(cc).get_ListStudents().size()+1,di=0;
            for(auto x:classes)
            {
                if(abs(v-x.get_ListStudents().size())>di) {
                    di = abs(v - x.get_ListStudents().size());
                }
            }
            if(di<4)
            {
                return true;
            } else
            {
                return false;
            }
        }
        break;
        default:
            // Handle the case where the method is not valid
            throw std::runtime_error("Invalid Method");
    }
}



bool checkbalance_Schedule(Schedule s,std::vector<Lesson> l)
{
    for(auto v:l) {
        for (auto x: s.get_Schedule()) {
            if (x == v) {
                return false;
            } else if (x.get_Day() == v.get_Day()) {
                if (v.get_Type() != "T") {
                    if (x.get_Start_hour() + x.get_Duration() > v.get_Start_hour() &&
                        x.get_Start_hour() < v.get_Start_hour() + v.get_Duration()) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void Trade_UC(std::string sc,std::string old_uc,std::string new_uc,std::string classcode)
{
    for(auto x: get_Student(sc).get_Horario().get_Schedule())
    {
        if(x.get_UCcode()==old_uc)
        {
            std::cout<<x.print();
            get_Student(sc).remove_Lesson(x);
        }
    }
    for(auto x: get_Lessons(classcode,new_uc,"ALL"))
    {
        std::cout<<x.print();
        get_Student(sc).add_Lesson(x);
    }
}

void Trade_class(std::string sc,std::string old_class,std::string new_class,std::string uc)
{
    for(auto x: get_Student(sc).get_Horario().get_Schedule())
    {
        if(x.get_ClassCode()==old_class)
        {
            std::cout<<x.print();
            get_Student(sc).remove_Lesson(x);
        }
    }
    for(auto x: get_Lessons(new_class,uc,"ALL"))
    {
        std::cout<<x.print();
        get_Student(sc).add_Lesson(x);
    }
}
