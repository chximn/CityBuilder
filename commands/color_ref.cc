#include "color_ref.hh"

color color_ref_hex::execute(Contexte const & ctx) const {
	return color(_hex);
}

color color_ref_point::execute(Contexte const & ctx) const {
	return color(_point->execute(ctx));
}
