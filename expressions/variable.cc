#include "variable.hh"

Variable::Variable(const std::string& nom) : _nom(nom) {}

int Variable::calculer(const Contexte & contexte) const {
    return contexte[_nom];
}
