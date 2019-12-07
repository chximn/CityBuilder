#include "ville.hh"
void ville::add_house(house_ptr h) {
	houses.push_back(h);
}
void ville::remove_house(house & f) {
	for (auto it = houses.begin(); it != houses.end(); it++) {
		if ((*it)->get_coordinates() == f.get_coordinates()) {
			houses.erase(it);
			break;
		}
	}
}
std::vector<house_ptr>  & ville::get_houses() {
    return houses;
}

house_ptr ville::get_house(std::string const & name) {
	for (auto & h : houses) {
		if (h->get_name() == name) return h;
	}

	throw house_not_found_var(name);
}

house_ptr ville::get_house(unsigned int index) {
	if (index >= houses.size()) throw house_not_found_list(index);
	return houses.at(index);
}

house_ptr ville::get_house(point const & coordinates) {
	for (auto & h : houses) {
		if (h->get_coordinates() == coordinates) return h;
	}

	throw house_not_found_coordinates(coordinates);
}

house_ptr ville::add_neighbor(house_ptr h, int distance) {
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
