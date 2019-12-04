#include "contexte.hh"

double& Contexte::get(const std::string & nom) {
    return variables[nom];
}

const double& Contexte::get(const std::string & nom) const {
    return variables.at(nom);
}

double& Contexte::operator[](const std::string & nom) {
    return variables[nom];
}

const double& Contexte::operator[](const std::string & nom) const {
    return variables.at(nom);
}