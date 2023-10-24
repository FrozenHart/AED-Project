#ifndef AED_PROJECT_STUDENT_H
#define AED_PROJECT_STUDENT_H
#include <string>
#include <vector>
#include "Schedule.h"

class Student {
public:
    Student(std::string StudentCode_,std::string StudentName_,Schedule horario);
    Student(std::string StudentCode_,std::string StudentName_);
    bool operator == (const Student& s) const;

    void add_Lesson(Lesson aula);

    std::string get_StudentCode();
    std::string get_StudentName();
    Schedule get_Horario();
    std::vector<std::string> get_classes();

private:
    std::string StudentCode;
    std::string StudentName;
    Schedule horario_student;
};


#endif //AED_PROJECT_STUDENT_H
