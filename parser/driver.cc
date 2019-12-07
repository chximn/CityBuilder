#include "driver.hh"
#include <iostream>

const Contexte& Driver::getContexte() const {
    return variables;
}

int Driver::getVariable(const std::string & name) const {
  return variables[name];
}

void Driver::setVariable(const std::string & name, double value) {
  variables[name]=value;
}
ville & Driver::get_ville()  {
    return _ville;
}

void Driver::show() {
	V->setRayon(_ville.get_radius());

	std::map<house_ptr,bool> visited;
	for (auto const & h : _ville.get_houses()) {
		point c = h->get_coordinates();
		color clr = h->get_color();
		degree d = h->get_orientation();

		V->construireMaison(c.get_x(), c.get_y(), c.get_z());
		V->setCouleur(c.get_x(), c.get_y(), c.get_z(), clr.get_r(), clr.get_g(), clr.get_b());
		V->setOrientation(c.get_x(), c.get_y(), c.get_z(), d.get_value());

		for (auto const & v : h->get_neighbors()) {
			if (visited.find(v) != visited.end()) continue;
			point vc = v->get_coordinates();

			V->construireRoute(c.get_x(), c.get_y(), c.get_z(), vc.get_x(), vc.get_y(), vc.get_z());
		}

		visited[h] = true;
	}

}
