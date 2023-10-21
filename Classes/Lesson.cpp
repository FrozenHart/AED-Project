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
    if((start_hour==l.start_hour)&&(duration==l.duration)&&(Type==l.Type)&&(Day==l.Day))
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
};