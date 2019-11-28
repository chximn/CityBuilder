#ifndef context_h
#define context_h

#include <string>
#include <map>

class Contexte {
private:
    std::map<std::string, double> variables;

public:
    Contexte() = default;
    Contexte(const Contexte & autre) = default;

    double& get(const std::string & nom);
    const double& get(const std::string & nom) const;

    double& operator[](const std::string & nom);
    const double& operator[](const std::string & nom) const;

};


#endif