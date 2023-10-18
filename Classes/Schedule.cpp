

#include "Schedule.h"

Schedule::Schedule(std::vector<Lesson> horario) {
this->horario=horario;
}

std::vector<Lesson> Schedule::get_Schedule() {
    std::vector<Lesson> s=horario;
    return s;
}

void Schedule::add_Lesson(Lesson aula) {
    horario.emplace_back(aula);
}

bool Schedule::operator==(const Schedule & s) const {
    for(int x=0;x<horario.size();x++)
    {
        if(!(s.horario.at(x)==horario.at(x)))
            return false;
    }
    return true;
}

Schedule::Schedule() {
    std::vector<Lesson> empty;
    horario=empty;
}

