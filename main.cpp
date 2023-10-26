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

//funcions
template<typename T, typename A>
bool in_map( std::map<T ,A> map,T s);
template<typename T>
bool in_vec( std::vector<T> vec, T s);
void set_up_classes_per_uc(std::map<std::string ,std::vector<std::string>> &UCs);
void set_up_classes(std::vector<Class> &classes);
void set_up_students(std::vector<Student> &StudentsList,std::vector<Class> &classes);
Class& get_CLass(std::string ClassCode,std::vector<Class> classes);
Lesson get_Lesson(std::string ClassCode,std::string UCcode,std::vector<Class> classes);
void add_UC();
void remove_UC(std::string UcCode);
void save(std::vector<Student> StudentsList,std::vector<Class> classes,std::map<std::string ,std::vector<std::string>> UCs);
//main
int main(int argc, char *argv[]) {

    // stores values from classes_per_uc.csv
    std::map<std::string, std::vector<std::string>> UCs; //map<UCcode,vector<Class Codes>>
    set_up_classes_per_uc(UCs);

    // stores values from classes.csv
    std::vector<Class> classes;
    set_up_classes(classes);

    // stores values from students_classes.csv
    std::vector<Student> StudentsList;
    set_up_students(StudentsList, classes);

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
                                                  {"Students",   9},
                                                  {"Class",   10},
                                                  {"UC",   11},
                                                  {"Lesson From Students",   12}, // remove
                                                  {"Lesson From Class",   13},
                                                  {"Students",   14},
                                                  {"Class",   15},
                                                  {"UC",   16}};

    std::string inputuser;
    std::queue<std::string> ActionQueue;
        std::cout<<"           Welcome to the Schedule Manager\n";
    while (true) {
        std::cout<<"                Chose an Operation\n";
        std::cout<<"-------------------------------------------------------\n";
        std::cout<<"|  Check  |  Add  |  Remove  |  Undo Action  |  Exit  |\n";
        std::cout<<"-------------------------------------------------------\n";

        getline(std::cin,inputuser);
        if(inputuser=="Check")
        {
            std::string method;
            while (true) {
                std::cout<<"                   Chose Check Method\n";
                std::cout<<"---------------------------------------------------------------------------\n";
                std::cout<<"| Student Schedule   -> Checks a Student Schedule                         |\n";
                std::cout<<"| Class Schedule     -> Checks a Class Schedule                           |\n";
                std::cout<<"| Lesson             -> Checks the time and type of a Lesson              |\n";
                std::cout<<"| Lessons From Class -> Checks all the Lessons time and Type from a Class |\n";
                std::cout<<"| Lessons From UC    -> Checks all the Lessons time and type from UC      |\n";
                std::cout<<"| Classes From UC    -> Checks all the Classes from a UC                  |\n";
                std::cout<<"| Students From UC   -> Checks all the Students from a UC                 |\n";
                std::cout<<"| Back                                                                    |\n";
                std::cout<<"---------------------------------------------------------------------------\n";

                getline(std::cin, method);
                if (method=="Back") {
                    break;
                }else if(!in_map(MethodValue, method))
                {
                    std::cout << "Invalid Method Try Again\n";
                }
                else {
                    std::string temp = "Check/" + method;
                    bool valid = true;
                    while (valid) {
                        switch (MethodValue[method]) {
                            case 0: {   //Student Schedule
                                std::string element;
                                std::cout << "Student Code: \n";
                                std::cin >> element;
                                temp += '/' + element;
                            }
                                break;
                            case 1: {   //Class Schedule
                                std::string element;
                                std::cout << "Class Code: \n";
                                std::cin >> element;
                                temp += '/' + element;
                            }
                                break;
                            case 2: {   //Lesson
                                std::string element1, element2;
                                std::cout << "UC Code: \n";
                                std::cin >> element1;
                                std::cout << "Class Code: \n";
                                std::cin >> element2;
                                temp += ('/' + element1 + '/' + element2);
                            }
                                break;
                            case 3: {   //Lessons From Class
                                std::string element;
                                std::cout << "Class Code: \n";
                                std::cin >> element;
                                temp += '/' + element;
                            }
                                break;
                            case 4: {   //Lessons From UC
                                std::string element;
                                std::cout << "UC Code: \n";
                                std::cin >> element;
                                temp += '/' + element;
                            }
                                break;
                            case 5: {   //Classes From UC
                                std::string element;
                                std::cout << "UC Code: \n";
                                std::cin >> element;
                                temp += '/' + element;
                            }
                                break;
                            case 6: {   //Students From UC
                                std::string element;
                                std::cout << "UC Code: \n";
                                std::cin >> element;
                                temp += '/' + element;
                            }
                                break;
                        }
                        ActionQueue.push(temp);
                        break;
                    }
                }

            }
        }else if(inputuser=="Add")
        {
            std::string method;
            while (true) {
                std::cout<<"                      Chose Add Method\n";
                std::cout<<"---------------------------------------------------------------\n";
                std::cout<<"| Lesson to UC      -> Adds a Lesson to a UC                  |\n";
                std::cout<<"| Lesson to Student -> Adds a Lesson to a Student Schedule    |\n";
                std::cout<<"| Student           -> Adds a Student to the System           |\n";
                std::cout<<"| Class             -> Adds a Class to the System             |\n";
                std::cout<<"| UC                -> Adds a UC to the System                |\n";
                std::cout<<"| Back                                                        |\n";
                std::cout<<"---------------------------------------------------------------\n";

                getline(std::cin, method);
                if (method=="Back") {
                    break;
                }else if(!in_map(MethodValue, method))
                {
                    std::cout << "Invalid Method Try Again\n";
                }
                else {
                    std::string temp = "Add/" + method;
                    ActionQueue.push(temp);
                    break;
                }
            }
        }else if(inputuser=="Remove")
        {
            std::string method;
            while (true) {
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
                    break;
                }else if(!in_map(MethodValue, method))
                {
                    std::cout << "Invalid Method Try Again\n";
                }
                else {
                    std::string temp = "Remove/" + method;
                    ActionQueue.push(temp);
                    break;
                }
            }

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

    std::string User;
    std::string UserCode;
    switch (OperationValue[inputuser],MethodValue[inputuser]) {

        default:
            std::cout << "Invalid Operation or Method\n";
            break;
    }


    // stores values back in the files(students_classes.csv,classes.csv,classes_per_uc.csv)
    save(StudentsList,classes,UCs);

    return 0;
}

void set_up_students(std::vector<Student> &StudentsList,std::vector<Class> &classes)
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
            StudentsList.emplace_back(StudentCode,StudentName, std::vector<Lesson>{get_Lesson(ClassCode,UcCode,classes)});
        }
        else
        {
            for(auto &x:StudentsList)
            {
                if(x.get_StudentCode()==StudentCode)
                {
                    x.add_Lesson(get_Lesson(ClassCode,UcCode,classes));
                }
            }
        }
    }
    fin.close();
}

void set_up_classes(std::vector<Class> &classes)
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

void set_up_classes_per_uc(std::map<std::string ,std::vector<std::string>> &UCs)
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

Class& get_CLass(std::string ClassCode,std::vector<Class> classes)
{
    for(auto &x:classes)
    {
        if(x.get_ClassCode()==ClassCode)
            return x;
    }
    // Handle the case where the Class with the specified ClassCode is not found
    throw std::runtime_error("Class not found for given ClassCode.");
}


Lesson get_Lesson(std::string ClassCode,std::string UCcode,std::vector<Class> classes)
{
    Class temp= get_CLass(ClassCode,classes);
    for(auto x : temp.get_Schedule().get_Schedule())
    {
        if(x.get_UCcode()==UCcode)
        {
            return x;
        }
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

void save(std::vector<Student> StudentsList,std::vector<Class> classes,std::map<std::string ,std::vector<std::string>> UCs) {
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

void add_UC()
{

}

void remove_UC(std::string UcCode)
{

}


