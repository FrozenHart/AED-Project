#ifndef AED_PROJECT_UC_H
#define AED_PROJECT_UC_H
#include <string>
#include <vector>

class UC {
public:
    UC(std::string UCcode,std::vector<std::string> ClassCode);
private:
    std::string UCcode_;
    std::vector<std::string> ClassCode_;
};


#endif //AED_PROJECT_UC_H
