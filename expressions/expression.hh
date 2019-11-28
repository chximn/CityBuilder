#pragma once
#include <memory>
#include "contexte.hh"


class Expression {
public:
    virtual double calculer(const Contexte & contexte) const = 0;
};

using ExpressionPtr = std::shared_ptr<Expression>;

