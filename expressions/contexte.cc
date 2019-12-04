#include "contexte.hh"

int& Contexte::get(const std::string & nom) {
    return variables[nom];
}

const int& Contexte::get(const std::string & nom) const {
    return variables.at(nom);
}

int& Contexte::operator[](const std::string & nom) {
    return variables[nom];
}

const int& Contexte::operator[](const std::string & nom) const {
    return variables.at(nom);
}
