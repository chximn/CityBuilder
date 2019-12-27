#include "command.hh"

using namespace commands;

void command::set_contextus() {
	error::context(error_line);
}

void construct_house::execute(city & c, Contexte  & ctx) {
	set_contextus();
	auto h = _house->execute(c, ctx);
	if (!h->get_coordinates().is_valid_coordinates()) error::report("la position " + h->get_coordinates().to_string() + " n'est pas une position valide");
	c.add_house(h);
}

void construct_road::execute(city & c, Contexte  & ctx) {
	set_contextus();

	auto h1 = _house1->execute(c, ctx);
	auto h2 = _house2->execute(c, ctx);

	h1->add_neighbor(h2);

	if (!_directed) {
		h2->add_neighbor(h1);
	}
}
void destruct_road::execute(city & c, Contexte  & ctx) {
	set_contextus();

	auto h1 = _house1->execute(c, ctx);
	auto h2 = _house2->execute(c, ctx);

	h1->remove_neighbor(h2);
	h2->remove_neighbor(h1);
}

void destruct_house::execute(city & c, Contexte  & ctx) {
	set_contextus();

	auto h = _house->execute(c, ctx);
	c.remove_house(h);
}

void position_house::execute(city & c, Contexte  & ctx) {
	set_contextus();
	os << "Position maison : " << _house->execute(c, ctx)->get_coordinates().to_string() << "\n";
}

void turn_house::execute(city & c, Contexte  & ctx) {
	set_contextus();
	_house->execute(c, ctx)->get_orientation().turn(_clockwise);
}

void show_neighborhood::execute(city & c, Contexte  & ctx) {
	set_contextus();

	auto house = _house->execute(c, ctx);

	os << "Voisinage de " << house->get_coordinates().to_string() << ":\n";

	for (auto  & h : house->get_neighbors()) {
		os << h->to_string() << ", distance : " << house->distance(h) << "\n";
	}
}

void orientate_house::execute(city & c, Contexte  & ctx) {
	set_contextus();

	_house->execute(c, ctx)->get_orientation() = _degree->execute(ctx);
}

void orientation_house::execute(city & c, Contexte  & ctx) {
	os << "Orientation: " << _house->execute(c, ctx)->get_orientation().to_string() << "\n";
}

void move_house::execute(city & c, Contexte  & ctx) {
	set_contextus();

	auto ccc = _coordinates->execute(ctx);;
	if (c.house_exists(ccc)) error::report("Une maison existe déjà en " + ccc.to_string());
	if (!ccc.is_valid_coordinates()) error::report("la position " + ccc.to_string() + " n'est pas une position valide");


	_house->execute(c, ctx)->get_coordinates() = ccc;
}

void colorize_house::execute(city & c, Contexte  & ctx) {
	set_contextus();

	_house->execute(c, ctx)->get_color() = _color->execute(ctx);
}

void show_color::execute(city & c, Contexte  & ctx) {
	set_contextus();

	auto ccc = _house->execute(c, ctx)->get_color();
	os << "La couleur de la maison est: " << ccc.to_string() << "\n";
}

void add_neighbor::execute(city & c, Contexte  & ctx) {
	set_contextus();

	c.add_neighbor(_house->execute(c, ctx), _expression->calculer(ctx));
}

void assignment::execute(city & c, Contexte & ctx) {
	set_contextus();

	ctx[_var] = _expression->calculer(ctx);
}

void if_condition::execute(city & c, Contexte & ctx) {
	set_contextus();

	if (_condition->calculer(ctx)) {
		for (auto const & cmd : _body) {
			cmd->execute(c, ctx);
		}
	}
}

void if_else_condition::execute(city & c, Contexte & ctx) {
	set_contextus();

	if (_condition->calculer(ctx)) {
		for (auto const & cmd : _body) {
			cmd->execute(c, ctx);
		}
	}

	else {
		for (auto const & cmd : _body2) {
			cmd->execute(c, ctx);
		}
	}
}

void while_loop::execute(city & c, Contexte & ctx) {
	set_contextus();

	while (_condition->calculer(ctx)) {
		for (auto const & cmd : _body) {
			cmd->execute(c, ctx);
		}
	}
}

void repeat_loop::execute(city & c, Contexte & ctx) {
	set_contextus();

	int ends = _times->calculer(ctx);

	for (int i = 0; i < ends; i++) {
		for (auto const & cmd : _body) {
			cmd->execute(c, ctx);
		}
	}
}

void function::execute(city & cit, Contexte & ctx) {
	set_contextus();

	for (auto const & c : _body) {
		c->execute(cit, ctx);
	}
}

void function_call::execute(city & c, Contexte & ctx) {
	set_contextus();


	std::string n = _name;

	auto it = std::find_if(_functions.begin(), _functions.end(), [n](auto const & f){
		return f._name == n;
	});

	if (it != _functions.end()) {
	    auto func = *it;

		Contexte func_ctx;

		int i = 0;
		for (auto const & a : _arguments) {
			int v = a->calculer(ctx);

			try {
				func_ctx[func._arguments.at(i)] = v;
			}

			catch (...) {}

			func_ctx["$"+std::to_string(i+1)] = v;
			i++;
		}

		func.execute(c, func_ctx);
	}

	else error::report("Fonction \"" + _name + "\" n'existe pas");
}

void for_loop::execute(city & c, Contexte & ctx) {
	set_contextus();

	_init->execute(c, ctx);

	while (_cond->calculer(ctx)) {
		for (auto const & cmd : _body) {
			cmd->execute(c, ctx);
		}

		_inc->execute(c, ctx);
	}
}

void city_construction::execute(city & c, Contexte & ctx) {
	set_contextus();

	Contexte lctx;
	int rad = _radius->calculer(lctx);

	if (rad < 0) error::report("impossible de créer une ville avec rayon négatif");

	c.set_radius(rad);
	for (auto const & cmd : _body) {
		cmd->execute(c, ctx);
	}
}

void pcc::execute(city & c, Contexte & ctx) {

	auto m0 = std::chrono::high_resolution_clock::now();
	auto l = c.a_star(_house1->execute(c, ctx), _house2->execute(c, ctx));
	auto m1 = std::chrono::high_resolution_clock::now();


	auto m2 = std::chrono::high_resolution_clock::now();
	auto l2 = c.dijkstra(_house1->execute(c, ctx), _house2->execute(c, ctx));
	auto m3 = std::chrono::high_resolution_clock::now();
	std::cout<<"################################################################################\n";
	std::cout << "Time of execution :" << '\n';
	std::cout << "A* took       " << (m1-m0).count() << " microseconds" << "\n";
	std::cout << "Dijkstra took " << (m3-m2).count() << " microseconds" << "\n";

	os << "chemin: ";
	for (auto const & h : l) {
		os << h->get_name() << " -> ";
	}
	os << "\n";
}

void tarjan_algorithm::execute(city & c, Contexte & ctx) {
	std::vector<std::vector<house_ptr>> blocks = c.tarjan();

	color colors[] = {
		color("#ff0000"),
		color("#00ff00"),
		color("#0000ff"),
		color("#ffff00"),
		color("#ff00ff"),
		color("#00ffff"),
		color("#000000"),
		color("#888888"),
		color("#55ff55"),
		color("#5555ff"),
		color("#ff55ff"),
		color("#8855ff"),
		color("#005588")
	};

	int i = 0;
	for (auto const & block : blocks) {
		for (auto const & h : block) {
			h->get_color() = colors[i];
		}
		i++;
	}
}

void kruksal_algorithm::execute(city & c, Contexte & ctx) {
	auto s = c.kruksal();
	c.clear_houses();

	std::map<house_ptr, bool> visited;

	 for (auto const & r : s) {
		auto h1 = r->get_house1();
		if (visited.find(h1) == visited.end()) {
			visited[h1] = true;
			c.add_house(h1);
		}

		auto h2 = r->get_house2();
		if (visited.find(h2) == visited.end()) {
			visited[h2] = true;
			c.add_house(h2);
		}

		r->get_house1()->add_neighbor(r->get_house2());
		r->get_house2()->add_neighbor(r->get_house1());
	}
}

void welsh_powell_algorithm::execute(city & c, Contexte & ctx) {
	std::map<house_ptr, int> mp = c.welsh_powell();

	color colors[] = {
		color("#ff0000"),
		color("#00ff00"),
		color("#0000ff"),
		color("#ffff00"),
		color("#ff00ff"),
		color("#00ffff"),
		color("#000000"),
		color("#888888"),
		color("#55ff55"),
		color("#5555ff"),
		color("#ff55ff"),
		color("#8855ff"),
		color("#005588")
	};

	int size = 0;
	for (auto & hc : mp) {
		hc.first->get_color() = colors[hc.second];
		if (hc.second + 1 > size) size = hc.second + 1;
	}

	std::cout << "le nombre chromatique du graphe < " << size << "\n";
}
