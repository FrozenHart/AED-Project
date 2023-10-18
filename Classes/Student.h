#ifndef AED_PROJECT_STUDENT_H
#define AED_PROJECT_STUDENT_H
#include <string>
#include <vector>
#include "Schedule.h"

class Student {
public:
    Student(std::string StudentCode_,std::string StudentName_,Schedule horario);
    bool operator == (const Student& s) const;
private:
    std::string StudentCode;
    std::string StudentName;
    Schedule horario_student;
};


#endif //AED_PROJECT_STUDENT_H
