#ifndef context_h
#define context_h

#include <string>
#include <map>

class Contexte {
private:
    std::map<std::string, int> variables;

public:
    Contexte() = default;
    Contexte(const Contexte & autre) = default;

    int& get(const std::string & nom);
    const int& get(const std::string & nom) const;

    int& operator[](const std::string & nom);
    const int& operator[](const std::string & nom) const;

};


#endif
