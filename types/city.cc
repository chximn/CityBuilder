#include "city.hh"

void city::add_house(house_ptr h) {
	auto coords = h->get_coordinates();
	if (coords.get_x() > radius|| coords.get_y() > radius || coords.get_z() > radius)
		error::report("La position " + coords.to_string() + " est hors du périmètre de la ville.");

	if (house_exists(coords)) error::report("une maison existe déjà en " + coords.to_string());
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

			int found = house_exists(pnt2);

			if (!found) { success = true; break; }

			pnt.rotate();
			if (pnt == start) { success = false; break; }
		}

		if (success) {
			h->get_coordinates() = pnt;
			return h;
		}

		i++;
	}
}

void city::remove_house(house_ptr f) {
	auto it = houses.begin();

	while (it != houses.end()) {
		if ((*it)->get_coordinates() == f->get_coordinates()) {
			(*it)->clear_neighbors();
			it = houses.erase(it);
		}

		else {
			(*it)->remove_neighbor(f);
			it++;
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

	error::report("Il n'existe pas une maison avec le nom \"" + name + "\"");
}

bool city::house_exists(std::string const & name) {
	for (auto & h : houses) {
		if (h->get_name() == name) return true;
	}

	return false;
}

house_ptr city::get_house(unsigned int index) {
	if (index > houses.size()) error::report("Il n'existe pas une maison avec l'indice " + std::to_string(index) + " (maison[" + std::to_string(index) + "])");
	return houses.at(index-1);
}

bool city::house_exists(unsigned int index) {
	if (index > houses.size()) return false;
	return true;
}

house_ptr city::get_house(point const & coordinates) {
	for (auto & h : houses) {
		if (h->get_coordinates() == coordinates) return h;
	}

	error::report("Il n'existe pas une maison en " + coordinates.to_string());
}

bool city::house_exists(point const & p) {
	for (auto & h : houses) {
		if (h->get_coordinates() == p) return true;
	}

	return false;
}

house_ptr city::add_neighbor(house_ptr h, int distance) {
	if (distance <= 0) error::report("La distance minimale pour un voisin est 1");

	point const & coordinates = h->get_coordinates();
	point start(distance);
	point pnt(start);
	bool success;

	while(1) {
		point pnt2(pnt);
		pnt2.translate(coordinates);

		int found = house_exists(pnt2);

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
		error::report("Il n'y a plus de place pour un voisin pour la maison en " + coordinates.to_string() + " avec la distance " + std::to_string(distance));
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
