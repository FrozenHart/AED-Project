
#ifndef AED_PROJECT_SCHEDULE_H
#define AED_PROJECT_SCHEDULE_H
#include "Lesson.h"
#include <vector>

class Schedule {
private:
    std::vector<Lesson> horario;
    std::string formathours(float hours);
public:
    Schedule();
    Schedule(std::vector<Lesson> horario);

    //operators
    bool operator == (const Schedule& s) const;
    std::string print();

    //gets
    std::vector<Lesson> get_Schedule();

    //methods
    void add_Lesson(Lesson aula);
    void remove_Lesson(Lesson aula);

};


#endif //AED_PROJECT_SCHEDULE_H