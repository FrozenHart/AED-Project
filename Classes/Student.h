#ifndef AED_PROJECT_STUDENT_H
#define AED_PROJECT_STUDENT_H
#include <string>
#include <vector>

class Student {
public:
    Student(std::string StudentCode,std::string StudentName);
private:
    std::string StudentCode_;
    std::string StudentName_;
    std::vector<std::pair<std::string,std::string>> Horario;
};


#endif //AED_PROJECT_STUDENT_H
