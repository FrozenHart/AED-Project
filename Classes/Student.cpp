#include "Student.h"


Student::Student(std::string StudentCode_, std::string StudentName_,Schedule horario): horario_student(horario) {
    StudentCode = StudentCode_;
    StudentName = StudentName_;
}

Student::Student(std::string StudentCode_, std::string StudentName_) {
    StudentCode=StudentCode_;
    StudentName=StudentName_;
    Schedule empty;
    horario_student=empty;
}

Student::Student() {
    StudentCode="";
    StudentName="";
    Schedule empty;
    horario_student=empty;
}

bool Student::operator==(const Student &s) const {
    if((StudentCode==s.StudentCode)&&(StudentName==s.StudentName))
        return true;
    return false;
}

Schedule Student::get_Horario() {
    Schedule s=horario_student;
    return s;
}

std::string Student::get_StudentName() {
    std::string s=StudentName;
    return s;
}

std::string Student::get_StudentCode() {
    std::string s=StudentCode;
    return s;
}

std::vector<std::string> Student::get_classes() {
    std::vector<std::string> s;
    for(auto x:horario_student.get_Schedule())
    {
        s.emplace_back(x.get_ClassCode());
    }
    return s;
}



void Student::add_Lesson(Lesson aula) {
    horario_student.add_Lesson(aula);
    horario_student.sorted();
}

void Student::remove_Lesson(Lesson aula) {
    horario_student.remove_Lesson(aula);
    horario_student.sorted();
}

Student::~Student() {

}

std::string Student::print_Student() {
    return StudentCode+"->"+StudentName;
}

bool Student::operator<(const Student &other) const {
    if(StudentCode<other.StudentCode)
        return true;
    return false;
}


