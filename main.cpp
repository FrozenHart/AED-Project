#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "Classes/Class.h"

//funcions
template<typename T, typename A>
bool in_map( std::map<T ,A> map,T s);
template<typename T>
bool in_vec( std::vector<T> vec, T s);
std::map<std::string ,std::vector<std::string>> set_up_classes_per_uc();
std::vector<Class> set_up_classes();

//main
int main() {

    // stores values from classes_per_uc.csv
    std::map<std::string ,std::vector<std::string>> UCs=set_up_classes_per_uc();

    // stores values from classes
    std::vector<Class> classes=set_up_classes();

    for(auto x:classes)
    {
        std::cout<<x.get_ClassCode()<<"->";
        for (auto y :x.get_Schedule().get_Schedule())
        {
            std::cout<<"("<<y.get_UCcode()<<'/'<<y.get_Day()<<'/'<<y.get_Start_hour()<<'/'<<y.get_Duration()<<'/'<<y.get_Type()<<")";
        }
        std::cout<<'\n';
    }

    return 0;
}

std::vector<Class> set_up_classes()
{
    // stores values from classes.csv
    std::vector<Class> classes;
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
        for (auto c: classes) {
            if (c.get_ClassCode() == ClassCode)
            {
                temp = true;
            }
        }
        if (!temp) // adds a new Class
        {
            std::vector<Lesson> tempv;
            tempv.emplace_back(StartHour, Duration, Type, Weekday,UcCode);
            classes.emplace_back(Schedule(tempv), ClassCode);
        } else // adds a Lesson to an existing Class
        {
            for(Class& c:classes)
            {
                if(c.get_ClassCode()==ClassCode)
                {
                    c.add_lesson(Lesson(StartHour, Duration, Type, Weekday,UcCode));
                }
            }
        }
    }
    fin.close();
    return classes;
}


std::map<std::string ,std::vector<std::string>> set_up_classes_per_uc()
{
    // stores values from classes_per_uc.csv
    std::map<std::string ,std::vector<std::string>> UCs;  //map<UCcode,vector<Class Codes>>
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
    return UCs;
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

