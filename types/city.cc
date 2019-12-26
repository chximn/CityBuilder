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
				f->remove_neigbor(h);
				h->remove_neigbor(f);
			}

			houses.erase(it);
			break;
		}
	}
}

void city::clear_houses() {

	for (auto const & h : houses) {
		h->clear_neighbors();
	}

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
	std::cout<<"------------------------------------------------------------------------------\n";
	std::cout<<"A star : \n";
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

				std::cout << "calcule:" << current->get_name()<<"->"<<n->get_name()<< ", distance=" << tentative << ", heuristique=" << n->distance(goal) << "\n";
			}
		}
		std::cout<<std::endl;
	}

	return path;
}

std::list<house_ptr> city::dijkstra(house_ptr start, house_ptr goal) {
	std::cout<<"------------------------------------------------------------------------------\n";
	std::cout<<"Dijkstra : \n ";
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
		std::cout << " Noeud choisi: " << current->get_name() << "\n";

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
				std::cout << "calcule: " << current->get_name()<<"->"<<n->get_name()<< ", distance=" << tentative << "\n";
			}
		}
		std::cout<<std::endl;
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

	std::cout<<"*** racine choisie : "<<v->get_name()<<" ***"<<std::endl;
	for (auto const & w: v->get_neighbors()) {
		if (records[w].index == -1) {
			std::cout<<"+sommet non visité : "<<w->get_name()<<std::endl;
			std::cout<<"+Arête sélectionnée :"<<v->get_name()<<"->"<<w->get_name()<<std::endl;
			std::cout<<" "<<std::endl;
			strong_connect(w, records, s, index, vsg);
			int a = records[v].lowlink;
			int b = records[v].lowlink;
			records[v].lowlink = (a < b) ? a : b;
		}

		else if (records[w].on_stack) {
			std::cout<<"+sommet deja visité : "<<w->get_name()<<std::endl;
			int a = records[v].lowlink;
			int b = records[w].index;
			records[v].lowlink = (a < b) ? a : b;
		}
	}

	if (records[v].lowlink == records[v].index) {
		std::vector<house_ptr> sg;
		house_ptr w;
		while (!s.empty()) {
			w = s.top();
			s.pop();
			records[w].on_stack = false;
			sg.push_back(w);
		}

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
	std::vector<house_ptr> visited;
	std::map<house_ptr, int> partitions;

	int i;
	for (auto const & h : houses) {
		partitions[h] = i;
		i++;
	}

	std::vector<road_ptr> edges = get_roads();
	//trie des arc;
	std::sort(edges.begin(), edges.end(), [](auto r1, auto r2){ return r1->get_distance() < r2->get_distance(); });

 	for (auto const & e : edges) {
		auto setu = partitions[e->get_house1()];
		auto setv = partitions[e->get_house2()];

		if (setu != setv) {
			mst.insert(e);
				 visited.push_back(e->get_house1());
				 visited.push_back(e->get_house2());
				 std::cout<<std::endl;
				 std::cout<<"-Sommet concerné : "<<e->get_house1()->get_name()<<std::endl;
			for (auto & hhh : partitions) {
				if (hhh.second == setv)
				{
					hhh.second = setu;
					std::cout<<"sommet à l'extremite: "<<hhh.first->get_name()<<std::endl;
				}
			}
			std::cout<<"Arête choisie :"<<e->get_house1()->get_name()<<"->"<<e->get_house2()->get_name()<<std::endl;
			std::cout<<"    distance :"<<e->get_distance()<<std::endl;
		}
	}

	return mst;
}

std::map<house_ptr, int> city::welsh_powell() {
	std::sort(houses.begin(), houses.end(), [](auto h1, auto h2){ return h1->get_neighbors().size() > h2->get_neighbors().size(); });

	std::map<house_ptr, int> colors;

	int color = -1;
	for (auto const & h : houses) {

		for (int i = 0; i <= color + 1; i++) {
			bool neigh_col = false;

			for (auto const & n : h->get_neighbors()) {
				if (colors.find(n) != colors.end()) {
					if (colors[n] == i) {
						neigh_col = true;
						break;
					}
				}
			}

			if (!neigh_col) {
				colors[h] = i;
				if (i > color) color = i;
				break;
			}
		}
	}

	return colors;
}
