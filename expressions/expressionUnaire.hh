#pragma once
#include "expression.hh"
#include "house_ref.hh"
#include "city.hh"

enum class OperateurUnaire {
    neg,
    non
};

class ExpressionUnaire : public Expression {
public:
    ExpressionUnaire(const ExpressionUnaire &) = default;
    ExpressionUnaire(ExpressionPtr exp, OperateurUnaire op);
    ~ExpressionUnaire() = default;

    int calculer(const Contexte& contexte) const override;

private:
    ExpressionPtr _exp;
    OperateurUnaire _op;
};

class ExpressionOccupied : public Expression {
private:
	house_ref_ptr _house;
	city & _city;
public:
	ExpressionOccupied(house_ref_ptr h, city & c): _house(h), _city(c) {}
	int calculer(const Contexte& contexte) const override;
};
