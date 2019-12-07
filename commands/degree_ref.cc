#include "degree_ref.hh"

degree degree_ref::execute(Contexte const & ctx) const {
	return degree(_expression->calculer(ctx));
}
