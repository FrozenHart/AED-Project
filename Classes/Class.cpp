
#include "Class.h"

Class::Class(Schedule horario_, std::vector<Student> Liststudents,std::string ClassCode) : horario(horario_) ,ListStudents(Liststudents) ,ClassCode(ClassCode){}

Class::Class(Schedule horario_,std::string ClassCode): horario(horario_) , ClassCode(ClassCode)
{
    std::vector<Student> empty;
    ListStudents=empty;
}

bool Class::operator==(const Class& c) const {
    if (c.ClassCode == ClassCode)
        return true;
    return false;
}

std::vector<Student> Class::get_ListStudents() {
    std::vector<Student> s=ListStudents;
    return s;
}

Schedule Class::get_Schedule() {
    Schedule s=horario;
    return s;
}

std::string Class::get_ClassCode() {
    std::string s=ClassCode;
    return s;
}

void Class::add_lesson(Lesson aula) {
    horario.add_Lesson(aula);
}

void Class::remove_lesson(Lesson aula) {
    horario.remove_Lesson(aula);
}

Class::~Class() {
}

void Class::add_student(Student student) {
    ListStudents.emplace_back(student);
}


