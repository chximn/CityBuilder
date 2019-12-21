#ifndef context_h
#define context_h

#include <string>
#include <map>
#include <ostream>

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

	void show(std::ostream & os);
};


#endif
