#include "city.hh"

int inf = 2147483647;

void city::add_house(house_ptr h) {
	auto coords = h->get_coordinates();
	if (coords.get_x() > radius || coords.get_y() > radius || coords.get_z() > radius) throw out_of_radius();
	houses.push_back(h);
}

void city::remove_house(house_ptr f) {
	for (auto it = houses.begin(); it != houses.end(); it++) {
		if ((*it)->get_coordinates() == f->get_coordinates()) {

			for (auto const & h : houses) {
				h->remove_neigbor(f);
			}

			houses.erase(it);
			break;
		}
	}
}

void city::clear_houses() {
	houses.clear();
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

		std::cout << "Noeud choisi: " << current->get_name() << "\n";

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

				std::cout << "calcule: pred=" << current->get_name() << ", dist=" << tentative << ", h=" << n->distance(goal) << "\n";
			}
		}
	}

	return path;
}

std::list<house_ptr> city::dijkstra(house_ptr start, house_ptr goal) {
	std::list<house_ptr> path;

	struct record {
		int dist = inf;
		house_ptr pred = nullptr;
		bool visited = false;
	};

	std::map<house_ptr, record> records;

	records[start] = record{0,nullptr, false};

	while (true) {
		house_ptr current = nullptr;


		for (auto const & p : records) {
			if (p.second.visited) continue;

			if (current == nullptr || records[p.first].dist < records[current].dist) {
				current = p.first;
			}
		}

		if (current == nullptr) {
			house_ptr pred = goal;

			while (pred != nullptr) {
				path.push_front(pred);
				pred = records[pred].pred;
			}

			return path;
		}

		records[current].visited = true;

		for (auto const & r : records) {
			if (r.second.visited) continue;
		}

		for (auto const & n : current->get_neighbors()) {
			if (records[n].visited) continue;

			int tentative = records[current].dist + current->distance(n);
			if (tentative < records[n].dist) {
				records[n].pred = current;
				records[n].dist = tentative;
			}
		}
	}

	return path;
}

struct record {
	int index = -1;
	int lowlink;
	bool on_stack;
};


void strong_connect(house_ptr v, std::map<house_ptr, record> & records, std::stack<house_ptr> & s, int & index, std::vector<std::vector<house_ptr>> & vsg) {
	records[v].index = index;
	records[v].lowlink = index;
	index++;
	s.push(v);
	records[v].on_stack = true;

	for (auto const & w: v->get_neighbors()) {
		if (records[w].index == -1) {
			strong_connect(w, records, s, index, vsg);
			int a = records[v].lowlink;
			int b = records[v].lowlink;
			records[v].lowlink = (a < b) ? a : b;
		}

		else if (records[w].on_stack) {
			int a = records[v].lowlink;
			int b = records[w].index;
			records[v].lowlink = (a < b) ? a : b;
		}
	}

	if (records[v].lowlink == records[v].index) {
		std::vector<house_ptr> sg;
		house_ptr w;
		do {
			w = s.top();
			s.pop();
			records[w].on_stack = false;
			sg.push_back(w);
		} while(w != v);

		vsg.push_back(sg);
	}
}

std::vector<std::vector<house_ptr>> city::tarjan() {
	std::vector<std::vector<house_ptr>> vsg;
	int index = 0;
	std::stack<house_ptr> s;
	std::map<house_ptr, record> records;

	for (auto const & h : houses) {
		if (records[h].index == -1) {
			strong_connect(h, records, s, index, vsg);
		}
	}

	return vsg;
}

std::vector<road_ptr> city::get_roads() const {
	std::vector<road_ptr> vec;

	for (auto const & h : houses) {
		for (auto const & v : h->get_neighbors()) {
			vec.push_back(std::make_shared<road>(h, v));
		}
	}

	return vec;
}

std::set<road_ptr> city::kruksal() {
	std::set<road_ptr> mst;

	std::set<std::set<house_ptr>> partitions;

	for (auto const & h : houses) {
		partitions.insert(std::set<house_ptr>{h});
	}

	std::vector<road_ptr> edges = get_roads();
	std::sort(edges.begin(), edges.end(), [](auto r1, auto r2){ return r1->get_distance() < r2->get_distance(); });

 	for (auto const & e : edges) {
		auto setu = *std::find_if(partitions.begin(), partitions.end(), [e](auto const & v){ return v.find(e->get_house1()) != v.end(); });
		auto itv =   std::find_if(partitions.begin(), partitions.end(), [e](auto const & v){ return v.find(e->get_house2()) != v.end(); });
		auto setv = *itv;

		if (std::find_if(setu.begin(), setu.end(), [e](auto const & v){ return v == e->get_house2(); }) == setu.end()) {
			mst.insert(e);
			setu.insert(setv.begin(), setv.end());
			partitions.erase(itv);
		}
	}

	return mst;
}
