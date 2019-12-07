#pragma once
#include "degree.hh"
#include "expression.hh"
#include "contexte.hh"

class degree_ref;
using degree_ref_ptr = std::shared_ptr<degree_ref>;

class degree_ref {
private:
	ExpressionPtr _expression;
public:
	degree_ref(ExpressionPtr e): _expression(e) {}
	degree execute(Contexte const &) const;
};
