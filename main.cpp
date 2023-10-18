#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "Classes/Class.h"
#include "Classes/Student.h"
#include "Classes/Schedule.h"
#include "Classes/Lesson.h"

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


    for (auto x: StudentsList) {
        std::cout << x.get_StudentCode() << ',' << x.get_StudentName() << "-> classes=";
        for (auto y: x.get_classes()) {
            std::cout << y<<'/';
        }
        std::cout << " -> horario= ";
        for (auto y: x.get_Horario().get_Schedule()) {
            std::cout << '(' << y.get_Day() << '/' << y.get_Start_hour() << '/' << y.get_Duration() << '/'
                      << y.get_Type() << ')';
        }
        std::cout << std::endl;
    }


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
            StudentsList.emplace_back(StudentCode,StudentName, std::vector<Lesson>{get_Lesson(ClassCode,UcCode,classes)},std::vector<std::string>{ClassCode});
        }
        else
        {
            for(auto &x:StudentsList)
            {
                if(x.get_StudentCode()==StudentCode)
                {
                    x.add_Lesson(get_Lesson(ClassCode,UcCode,classes));
                    if(!in_vec(x.get_classes(),ClassCode))
                    {
                        x.add_class(ClassCode);
                    }
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
                c.add_lesson(Lesson(StartHour, Duration, Type, Weekday,UcCode));
                temp = true;
                break;
            }
        }
        if (!temp) // adds a new Class
        {
            std::vector<Lesson> tempv;
            tempv.emplace_back(StartHour, Duration, Type, Weekday,UcCode);
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

