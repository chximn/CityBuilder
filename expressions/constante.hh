#pragma once
#include "expression.hh"

class Constante : public Expression {
public:
    Constante() = delete;
    Constante(const Constante&) = default;
    Constante(double valeur);


    double calculer(const Contexte& contexte) const override;

private:
    double _valeur;
};
