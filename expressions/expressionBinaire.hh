#pragma once
#include "expression.hh"

enum class OperateurBinaire {
    plus,
    moins,
    divise,
    multiplie
};

class ExpressionBinaire : public Expression {
public:
    ExpressionBinaire(const ExpressionBinaire &) = default;
    ExpressionBinaire(ExpressionPtr gauche, ExpressionPtr droite, OperateurBinaire op);
    ~ExpressionBinaire() = default;

    double calculer(const Contexte& contexte) const override;

private:
    ExpressionPtr _gauche;
    ExpressionPtr _droite;
    OperateurBinaire _op;
};
