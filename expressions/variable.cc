#include "variable.hh"

Variable::Variable(const std::string& nom) : _nom(nom) {}

double Variable::calculer(const Contexte & contexte) const {
    return contexte[_nom];
}