#include "Student.h"

Student::Student(std::string StudentCode_, std::string StudentName_,Schedule horario): horario_student(horario) {
    StudentCode = StudentCode_;
    StudentName = StudentName_;
}

bool Student::operator==(const Student &s) const {
    if((StudentCode==s.StudentCode)&&(StudentName==s.StudentName))
        return true;
    return false;
}
