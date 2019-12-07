#include "house_ref.hh"

house_ptr house_ref_name::execute(city & c, Contexte const & ctx) const {
	return c.get_house(name);
}

house_ptr house_ref_index::execute(city & c, Contexte const & ctx) const {
	return c.get_house(index->calculer(ctx));
}

house_ptr house_ref_coordinates::execute(city & c, Contexte const & ctx) const {
	return c.get_house(coordinates->execute(ctx));
}

house_ptr house_ref_create::execute(city & c, Contexte const & ctx) const {
	return std::make_shared<house>(coordinates->execute(ctx), degree(0), name);
}
