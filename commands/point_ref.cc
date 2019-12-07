#include "point_ref.hh"

point point_ref::execute(Contexte const & ctx) const {
	return point(x->calculer(ctx), y->calculer(ctx), z->calculer(ctx));
}
