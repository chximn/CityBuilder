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
	for (auto const & h : _ville.get_houses()) {
		point coordinates = h->get_coordinates();
		V->construireMaison(coordinates.get_x(), coordinates.get_y(), coordinates.get_z());
	}
}
