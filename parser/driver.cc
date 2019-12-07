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

house_ptr Driver::get_house(std::string const & name) {
	for (auto & h : houses) {
		if (h->get_name() == name) return h;
	}

	throw house_not_found_var(name);
}

house_ptr Driver::get_house(unsigned int index) {
	if (index >= houses.size()) throw house_not_found_list(index);
	return houses.at(index);
}

house_ptr Driver::get_house(point const & coordinates) {
	for (auto & h : houses) {
		if (h->get_coordinates() == coordinates) return h;
	}

	throw house_not_found_coordinates(coordinates);
}

void Driver::add_house(house_ptr f) {
	houses.push_back(f);
}

void Driver::remove_house(house & f) {
	for (auto it = houses.begin(); it != houses.end(); it++) {
		if ((*it)->get_coordinates() == f.get_coordinates()) {
			houses.erase(it);
			break;
		}
	}
}

house_ptr Driver::add_neighbor(house_ptr h, int distance) {
	point const & coordinates = h->get_coordinates();
	point start(distance);
	point pnt(start);
	bool success;

	while(1) {
		point pnt2(pnt);
		pnt2.translate(coordinates);

		int found = true;
		try { get_house(coordinates); }
		catch(...) { found = false; }

		if (found) {
			success = true;
			break;
		}

		pnt.rotate();
		if (pnt == start) {
			success = false;
			break;
		}
	}

	if (!success) {
		throw full_neighborhood(coordinates);
	}

	pnt.translate(coordinates);
	house_ptr hp = std::make_shared<house>(pnt);
	add_house(hp);
	hp->add_neighbor(h);
	h->add_neighbor(hp);
	return hp;
}

void Driver::show() {
	for (auto const & h : houses) {
		point coordinates = h->get_coordinates();
		V->construireMaison(coordinates.get_x(), coordinates.get_y(), coordinates.get_z());
	}
}
