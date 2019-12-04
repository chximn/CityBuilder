#pragma once
#include "expression.hh"

class Constante : public Expression {
public:
    Constante() = delete;
    Constante(const Constante&) = default;
    Constante(int valeur);


    int calculer(const Contexte& contexte) const override;

private:
    int _valeur;
};
