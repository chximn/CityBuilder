#pragma once
#include "expression.hh"


enum class OperateurUnaire {
    neg
};

class ExpressionUnaire : public Expression {
public:
    ExpressionUnaire(const ExpressionUnaire &) = default;
    ExpressionUnaire(ExpressionPtr exp, OperateurUnaire op);
    ~ExpressionUnaire() = default;

    double calculer(const Contexte& contexte) const override;

private:
    ExpressionPtr _exp;
    OperateurUnaire _op;
};
