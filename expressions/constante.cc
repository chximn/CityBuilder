#include "constante.hh"

Constante::Constante(int valeur) : _valeur(valeur) {}

int Constante::calculer(const Contexte & contexte) const {
    return _valeur;
}
