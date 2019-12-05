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
