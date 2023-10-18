
#ifndef AED_PROJECT_SCHEDULE_H
#define AED_PROJECT_SCHEDULE_H
#include "Lesson.h"
#include <vector>

class Schedule {
private:
    std::vector<Lesson> horario;
public:
    Schedule();
    Schedule(std::vector<Lesson> horario);
    std::vector<Lesson> get_Schedule();
    void add_Lesson(Lesson aula);
    bool operator == (const Schedule& s) const;
};


#endif //AED_PROJECT_SCHEDULE_H
