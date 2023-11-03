
#include "Schedule.h"
#include <algorithm>

Schedule::Schedule(std::vector<Lesson> horario) {
this->horario=horario;
}

std::vector<Lesson> Schedule::get_Schedule() {
    std::vector<Lesson> s=horario;
    return s;
}

void Schedule::add_Lesson(Lesson aula) {

    std::sort(horario.begin(), horario.end());
    horario.push_back(aula);
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

void Schedule::remove_Lesson(Lesson aula) {
    std::vector<Lesson> temp;
    for (auto x:horario) {
        if(x==aula)
        {
            continue;
        }
        temp.emplace_back(x);
    }
    horario=temp;
}

std::string Schedule::print() {
    std::string ss;
    ss+=  "                   Horario                    \n";
    ss += "----------------------------------------------\n";
    ss += "|                    Day                     |\n";
    ss += "----------------------------------------------\n";
    ss+=  "| ClassCode | UCcode | Type | Start | Finish |\n";
    ss+=  "----------------------------------------------\n\n";

    std::vector<std::string> dias={"Monday","Tuesday","Wednesday","Thursday","Friday"};
    for(auto x:dias)
    {
        if(x=="Monday") {
            ss += "-------------------------------------------\n";
            ss += "|                  Monday                 |\n";
            ss += "-------------------------------------------\n";

        } else if (x=="Tuesday") {
            ss += "-------------------------------------------\n";
            ss += "|                  Tuesday                |\n";
            ss += "-------------------------------------------\n";

        } else if (x=="Wednesday") {
            ss += "-------------------------------------------\n";
            ss += "|                 Wednesday               |\n";
            ss += "-------------------------------------------\n";

        } else if (x=="Thursday") {
            ss += "-------------------------------------------\n";
            ss += "|                 Thursday                |\n";
            ss += "-------------------------------------------\n";

        } else if (x=="Friday") {
            ss += "-------------------------------------------\n";
            ss += "|                  Friday                 |\n";
            ss += "-------------------------------------------\n";

        }

        //sort by start hour RaquelRenata
        for(auto y:horario)
        {
            if(y.get_Day()==x)
            {
                if(y.get_Type()=="T")
                    ss+="| "+y.get_ClassCode()+" | "+y.get_UCcode()+" | "+y.get_Type()+"  | "+ formathours(y.get_Start_hour())+" | "+formathours(y.get_Start_hour()+y.get_Duration())+" |"+'\n';
                else
                    ss+="| "+y.get_ClassCode()+" | "+y.get_UCcode()+" | "+y.get_Type()+" | "+formathours(y.get_Start_hour())+" | "+formathours(y.get_Start_hour()+y.get_Duration())+" |"+'\n';
            }
        }
        ss += "-------------------------------------------\n";
        ss+='\n';
    }
    return ss;
}

std::string Schedule::formathours(float hours) {
    std::string ss;
    int h=hours;
    int m=(hours-h)*60;
    if (m==0)
    {
    if(h<10)
        ss="0"+std::to_string(h)+":00";
    else
        ss=std::to_string(h)+":00";
    }
    else if(m<10)
    {
        if(h<10)
            ss="0"+std::to_string(h)+":0"+std::to_string(m);
        else
            ss=std::to_string(h)+":0"+std::to_string(m);
    }
    else
    {
        if(h<10)
            ss="0"+std::to_string(h)+":"+std::to_string(m);
        else
            ss=std::to_string(h)+":"+std::to_string(m);
    }
    return ss;
}

Schedule::~Schedule() {
}

void Schedule::sorted() {
    std::sort(horario.begin(), horario.begin()+horario.size());
}





