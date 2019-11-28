#include "constante.hh"

Constante::Constante(double valeur) : _valeur(valeur) {}

double Constante::calculer(const Contexte & contexte) const {
    return _valeur;
}
