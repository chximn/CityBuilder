#pragma once
#include "point.hh"
#include "expression.hh"
#include "contexte.hh"

class point_ref;
using point_ref_ptr = std::shared_ptr<point_ref>;

class point_ref {
private:
	ExpressionPtr x, y, z;
public:
	point_ref(ExpressionPtr _x, ExpressionPtr _y, ExpressionPtr _z): x(_x), y(_y), z(_z) {}
	point execute(Contexte const &) const;
};
