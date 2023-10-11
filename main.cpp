#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

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

int main() {

    // stores values from classes_per_uc.csv
    std::map<std::string ,std::vector<std::string>> UCs;//map<UCcode,vector<Class Codes>>
    std::fstream fin;
    fin.open("../schedule/classes_per_uc.csv",std::ios::in);
    std::string line,f_word,s_word;
    std::getline(fin,line);
    while(getline(fin, line))
    {
        std::stringstream str(line);
        getline(str, f_word, ','); // gets the UCcode
        getline(str, s_word, ','); // gets the Classcode
        if(!in_map(UCs,f_word)) // see if there is already the UCcode in the map
        {
            std::vector<std::string> temp;
            temp.push_back(s_word);
            UCs[f_word] = temp;
        }
        else // else adds a new key to the map with a UCcode and a vector as an element
        {
            std::vector<std::string> temp;
            temp=UCs[f_word];
            temp.push_back(s_word);
            UCs[f_word]=temp;
        }
    }

    //stores values from classes.csv

    return 0;
}