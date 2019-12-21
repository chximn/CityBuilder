#include "city.hh"

void city::add_house(house_ptr h) {
	auto coords = h->get_coordinates();
	if (coords.get_x() > radius || coords.get_y() > radius || coords.get_z() > radius) throw out_of_radius();
	houses.push_back(h);
}

house_ptr city::add_random_house(house_ptr h) {
	point coordinates(0, 0, 0);

	int i = 1;
	while (true) {
		point start(i);
		point pnt(start);
		bool success;

		while(true) {
			point pnt2(pnt);
			pnt2.translate(coordinates);

			int found = true;
			try { get_house(pnt2); }
			catch(...) { found = false; }

			if (!found) { success = true; break; }

			pnt.rotate();
			if (pnt == start) { success = false; break; }
		}

		if (success) {
			h->get_coordinates() = pnt;
			add_house(h);
			return h;
		}

		i++;
	}
}

void city::remove_house(house & f) {
	for (auto it = houses.begin(); it != houses.end(); it++) {
		if ((*it)->get_coordinates() == f.get_coordinates()) {
			houses.erase(it);
			break;
		}
	}
}

std::vector<house_ptr>  & city::get_houses() {
    return houses;
}

house_ptr city::get_house(std::string const & name) {
	for (auto & h : houses) {
		if (h->get_name() == name) return h;
	}

	throw house_not_found_var(name);
}

house_ptr city::get_house(unsigned int index) {
	if (index-1 >= houses.size()) throw house_not_found_list(index);
	return houses.at(index-1);
}

house_ptr city::get_house(point const & coordinates) {
	for (auto & h : houses) {
		if (h->get_coordinates() == coordinates) return h;
	}

	throw house_not_found_coordinates(coordinates);
}

house_ptr city::add_neighbor(house_ptr h, int distance) {
	point const & coordinates = h->get_coordinates();
	point start(distance);
	point pnt(start);
	bool success;

	while(1) {
		point pnt2(pnt);
		pnt2.translate(coordinates);

		int found = true;
		try { get_house(pnt2); }
		catch(...) { found = false; }

		if (!found) {
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

void city::set_radius(int r) {
	radius = r;

	auto it = houses.begin();
	while (it != houses.end()) {
		auto ppp = std::make_shared<house>(point(0,0,0));
		if ((*it)->distance(ppp) > r) {
			for (auto & v : (*it)->get_neighbors()) {
				v->remove_neighbor(*it);
				(*it)->remove_neighbor(v);
			}

			it = houses.erase(it);
		}
		else it++;
	}
}
