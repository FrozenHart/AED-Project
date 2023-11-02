#include <map>
#include "Lesson.h"

Lesson::Lesson(float start_hour, float duration, std::string Type,std::string Day,std::string UCcode,std::string ClassCode) {
    this->start_hour=start_hour;
    this->duration=duration;
    this->Type=Type;
    this->Day=Day;
    this->UCcode=UCcode;
    this->ClassCode=ClassCode;
}

bool Lesson::operator==(const Lesson &l) const {
    if((start_hour==l.start_hour)&&(duration==l.duration)&&(Type==l.Type)&&(Day==l.Day)&&(UCcode==l.UCcode)&&(ClassCode==l.ClassCode))
        return true;
    return false;
}

float Lesson::get_Start_hour() {
    float s=start_hour;
    return s;
}

float Lesson::get_Duration() {
    float s=duration;
    return s;
}

std::string Lesson::get_Type() {
    std::string s=Type;
    return s;
}

std::string Lesson::get_Day() {
    std::string s=Day;
    return s;
}

std::string Lesson::get_UCcode() {
    std::string s=UCcode;
    return s;
}

std::string Lesson::get_ClassCode() {
    std::string s=ClassCode;
    return s;
}

std::string Lesson::print() {
    std::string ss;
    ss+=  "| "+Day+" | "+ClassCode+" | "+UCcode+" | "+Type+" | "+ formathours(start_hour)+" | "+ formathours(start_hour+duration)+" |\n";
    return ss;
}

std::string Lesson::formathours(float hours) {
    std::string ss;
    int h=hours;
    int m=(hours-h)*60;
    if (m==0)
    {
        if(h<10)
            ss="0"+std::to_string(h)+":00";
        else
            ss=std::to_string(h)+":00";
    }
    else if(m<10)
    {
        if(h<10)
            ss="0"+std::to_string(h)+":0"+std::to_string(m);
        else
            ss=std::to_string(h)+":0"+std::to_string(m);
    }
    else
    {
        if(h<10)
            ss="0"+std::to_string(h)+":"+std::to_string(m);
        else
            ss=std::to_string(h)+":"+std::to_string(m);
    }
    return ss;
}

Lesson::~Lesson() {

}
bool Lesson::operator<(const Lesson& other) const {

    if (Day != other.Day) {
        std::map<std::string,int> dias={{"Monday",0},{"Tuesday", 1}, {"Wednesday", 2}, {"Thursday", 3}, {"Friday", 4}};
        return dias[Day] < dias[other.Day];
    }

    return start_hour < other.start_hour;
}
