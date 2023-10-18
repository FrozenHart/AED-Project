#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

bool in_map( std::map<std::string ,std::vector<std::string>> map,std::string s);
std::map<std::string ,std::vector<std::string>> set_up_classes_per_uc();

int main() {

    // stores values from classes_per_uc.csv
    std::map<std::string ,std::vector<std::string>> UCs=set_up_classes_per_uc();

    // stores values from classes

    return 0;
}

void set_up_classes()
{
    std::fstream fin;
    fin.open("../schedule/classes.csv",std::ios::in);
    std::string line,ClassCode,s_word;
    std::getline(fin,line);
    while(getline(fin, line)) {

    }
}


std::map<std::string ,std::vector<std::string>> set_up_classes_per_uc()
{
    // stores values from classes_per_uc.csv
    std::map<std::string ,std::vector<std::string>> UCs;//map<UCcode,vector<Class Codes>>
    std::fstream fin;
    fin.open("../schedule/classes_per_uc.csv",std::ios::in);
    std::string line,UcCode,ClassCode;
    std::getline(fin,line);
    while(getline(fin, line))
    {
        std::stringstream str(line);
        getline(str, UcCode, ','); // gets the UCcode
        getline(str, ClassCode, ','); // gets the Classcode
        if(!in_map(UCs,UcCode)) // see if there is already the UCcode in the map
        {
            std::vector<std::string> temp;
            temp.push_back(ClassCode);
            UCs[UcCode] = temp;
        }
        else // else adds a new key to the map with a UCcode and a vector as an element
        {
            std::vector<std::string> temp;
            temp=UCs[UcCode];
            temp.push_back(ClassCode);
            UCs[UcCode]=temp;
        }
    }
    fin.close();
    return UCs;
}

bool in_map( std::map<std::string ,std::vector<std::string>> map,std::string s)
{
    for(auto x:map)
    {
        if(x.first==s)
        {
            return true;
        }
    }
    return false;
}

