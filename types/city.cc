#include "city.hh"

int inf = 2147483647;

void city::add_house(house_ptr h) {
	auto coords = h->get_coordinates();
	if (coords.get_x() > radius || coords.get_y() > radius || coords.get_z() > radius) throw out_of_radius();
	houses.push_back(h);
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
	if (index >= houses.size()) throw house_not_found_list(index);
	return houses.at(index);
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

std::list<house_ptr> city::a_star(house_ptr start, house_ptr goal) {

	std::list<house_ptr> path;

	struct record {
		int g = inf;
		int f = inf;
		house_ptr pred = nullptr;
		bool visited = false;
	};

	std::map<house_ptr, record> records;

	records[start] = record{0,start->distance(goal),nullptr};

	while (!records.empty()) {
		house_ptr current = nullptr;

		for (auto const & p : records) {
			if (p.second.visited) continue;

			if (current == nullptr || records[p.first].f < records[current].f) {
				current = p.first;
			}
		}

		if (current == nullptr) {
			throw path_not_found();
		}

		if (current == goal) {
			house_ptr pred = goal;

			while (pred != nullptr) {
				path.push_front(pred);
				pred = records[pred].pred;
			}

			return path;
		}

		records[current].visited = true;

		for (auto const & n : current->get_neighbors()) {
			if (records[n].visited) continue;

			int tentative = records[current].g + current->distance(n);
			if (tentative < records[n].g) {
				records[n].pred = current;
				records[n].g = tentative;
				records[n].f = tentative + n->distance(goal);
			}
		}
	}

	return path;
}
