#pragma once
#include "expression.hh"

enum class OperateurBinaire {
    plus,
    moins,
    divise,
    multiplie,
    et,
    ou,
    inf_equ,
    sup_equ,
    equ,
    inf,
    sup
};

class ExpressionBinaire : public Expression {
public:
    ExpressionBinaire(const ExpressionBinaire &) = default;
    ExpressionBinaire(ExpressionPtr gauche, ExpressionPtr droite, OperateurBinaire op);
    ~ExpressionBinaire() = default;

    int calculer(const Contexte& contexte) const override;
private:
    ExpressionPtr _gauche;
    ExpressionPtr _droite;
    OperateurBinaire _op;
};
