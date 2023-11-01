#ifndef AED_PROJECT_CLASS_H
#define AED_PROJECT_CLASS_H
#include <vector>
#include <string>
#include "Student.h"
#include "Schedule.h"

class Class {
private:
    std::vector<Student> ListStudents;
    Schedule horario;
    std::string ClassCode;
public:
    Class(Schedule horario_, std::vector<Student> Liststudents,std::string ClassCode);
    Class(Schedule horario_,std::string ClassCode);
    ~Class();
    bool operator ==(const Class& c) const;

    //methods
    void add_lesson(Lesson aula);
    void remove_lesson(Lesson aula);

    //gets
    std::string get_ClassCode();
    Schedule get_Schedule();
    std::vector<Student> get_ListStudents();
};


#endif //AED_PROJECT_CLASS_H
