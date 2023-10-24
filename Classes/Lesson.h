
#ifndef AED_PROJECT_LESSON_H
#define AED_PROJECT_LESSON_H

#include <string>

class Lesson {

private:
    float start_hour;
    float duration;
    std::string Type;
    std::string Day;
    std::string UCcode;
    std::string ClassCode;
public:
    Lesson(float start_hour,float duration,std::string Type,std::string Day,std::string UCcode,std::string ClassCode);
    bool operator == (const Lesson& l) const;

    //gets
    float get_Start_hour();
    float get_Duration();
    std::string get_Type();
    std::string get_Day();
    std::string get_UCcode();
    std::string get_ClassCode();
};


#endif //AED_PROJECT_LESSON_H
