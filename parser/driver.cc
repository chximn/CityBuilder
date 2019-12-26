#include "driver.hh"
#include <iostream>

Contexte & Driver::getContexte() {
    return variables;
}

int Driver::getVariable(const std::string & name) const {
  return variables[name];
}

void Driver::setVariable(const std::string & name, double value) {
  variables[name]=value;
}
city & Driver::get_city()  {
    return _city;
}

void Driver::show() {
	gui->setRayon(_city.get_radius());

	std::map<house_ptr,bool> visited;
	for (auto const & h : _city.get_houses()) {
		point c = h->get_coordinates();
		color clr = h->get_color();
		degree d = h->get_orientation();

		gui->construireMaison(c.get_x(), c.get_y(), c.get_z());
		gui->setCouleur(c.get_x(), c.get_y(), c.get_z(), clr.get_r(), clr.get_g(), clr.get_b());
		gui->setOrientation(c.get_x(), c.get_y(), c.get_z(), d.get_value());

		for (auto const & v : h->get_neighbors()) {
			auto vn = v->get_neighbors();
			if (visited.find(v) != visited.end() && std::find(vn.begin(), vn.end(), h) != vn.end()) continue;

			point vc = v->get_coordinates();
			gui->construireRoute(c.get_x(), c.get_y(), c.get_z(), vc.get_x(), vc.get_y(), vc.get_z());
		}

		visited[h] = true;
	}

}
