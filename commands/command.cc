#include "command.hh"

using namespace commands;

void construct_house::execute(city & c, Contexte  & ctx) {
	c.add_house(_house->execute(c, ctx));
}

void construct_road::execute(city & c, Contexte  & ctx) {
	auto h1 = _house1->execute(c, ctx);
	auto h2 = _house2->execute(c, ctx);

	h1->add_neighbor(h2);
	h2->add_neighbor(h1);
}

void destruct_house::execute(city & c, Contexte  & ctx) {
	c.remove_house(_house->execute(c, ctx));
}

void position_house::execute(city & c, Contexte  & ctx) {
	os << _house->execute(c, ctx)->get_coordinates().to_string();
}

void turn_house::execute(city & c, Contexte  & ctx) {
	_house->execute(c, ctx)->get_orientation().turn(_clockwise);
}

void show_neighborhood::execute(city & c, Contexte  & ctx) {
	auto house = _house->execute(c, ctx);
	for (auto  & h : house->get_neighbors()) {
		os << h->to_string() << ", distance : " << house->distance(h) << "\n";
	}
}

void orientate_house::execute(city & c, Contexte  & ctx) {
	_house->execute(c, ctx)->get_orientation() = _degree->execute(ctx);
}

void move_house::execute(city & c, Contexte  & ctx) {
	_house->execute(c, ctx)->get_coordinates() = _coordinates->execute(ctx);
}

void colorize_house::execute(city & c, Contexte  & ctx) {
	_house->execute(c, ctx)->get_color() = _color->execute(ctx);
}

void show_color::execute(city & c, Contexte  & ctx) {
	os << _house->execute(c, ctx)->get_color().to_string();
}

void add_neighbor::execute(city & c, Contexte  & ctx) {
	c.add_neighbor(_house->execute(c, ctx), _expression->calculer(ctx));
}

void assignment::execute(city & c, Contexte  & ctx) {
	ctx[_var] = _expression->calculer(ctx);
}

void if_condition::execute(city & c, Contexte & ctx) {
	if (_condition->calculer(ctx)) {
		for (auto const & cmd : _body) {
			cmd->execute(c, ctx);
		}
	}
}

void if_else_condition::execute(city & c, Contexte & ctx) {
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
	while (_condition->calculer(ctx)) {
		for (auto const & cmd : _body) {
			cmd->execute(c, ctx);
		}
	}
}

void repeat_loop::execute(city & c, Contexte & ctx) {
	int ends = _times->calculer(ctx);

	for (int i = 0; i < ends; i++) {
		for (auto const & cmd : _body) {
			cmd->execute(c, ctx);
		}
	}
}

void pcc::execute(city & c, Contexte & ctx) {

	auto m0 = std::chrono::high_resolution_clock::now();
	auto l = c.a_star(_house1->execute(c, ctx), _house2->execute(c, ctx));
	auto m1 = std::chrono::high_resolution_clock::now();

	for (auto const & h : l) {
		os << h->get_name() << " ";
	}
	os << "\n";


	auto m2 = std::chrono::high_resolution_clock::now();
	auto l2 = c.dijkstra(_house1->execute(c, ctx), _house2->execute(c, ctx));
	auto m3 = std::chrono::high_resolution_clock::now();
	for (auto const & h : l2) {
		os << h->get_name() << " ";
	}
	os << "\n";


	std::cout << "A* took       " << (m1-m0).count() << " microseconds" << "\n";
	std::cout << "Dijkstra took " << (m3-m2).count() << " microseconds" << "\n";
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

	for (auto const & r : s) {
		c.add_house(r->get_house1());
		c.add_house(r->get_house2());

		r->get_house1()->add_neighbor(r->get_house2());
		r->get_house2()->add_neighbor(r->get_house1());
	}
}
