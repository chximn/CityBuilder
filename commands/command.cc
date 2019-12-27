#include "command.hh"

using namespace commands;

void command::set_contextus() {
	error::context(error_line);
}

void construct_house::execute(city & c, Contexte  & ctx) {
	set_contextus();

	c.add_house(_house->execute(c, ctx));
}

void construct_road::execute(city & c, Contexte  & ctx) {
	set_contextus();

	auto h1 = _house1->execute(c, ctx);
	auto h2 = _house2->execute(c, ctx);

	h1->add_neighbor(h2);
	h2->add_neighbor(h1);
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

	os << _house->execute(c, ctx)->get_coordinates().to_string();
}

void turn_house::execute(city & c, Contexte  & ctx) {
	set_contextus();
	_house->execute(c, ctx)->get_orientation().turn(_clockwise);
}

void show_neighborhood::execute(city & c, Contexte  & ctx) {
	set_contextus();

	auto house = _house->execute(c, ctx);
	for (auto  & h : house->get_neighbors()) {
		os << h->to_string() << ", distance : " << house->distance(h) << "\n";
	}
}

void orientate_house::execute(city & c, Contexte  & ctx) {
	set_contextus();

	_house->execute(c, ctx)->get_orientation() = _degree->execute(ctx);
}

void move_house::execute(city & c, Contexte  & ctx) {
	set_contextus();

	_house->execute(c, ctx)->get_coordinates() = _coordinates->execute(ctx);
}

void colorize_house::execute(city & c, Contexte  & ctx) {
	set_contextus();

	_house->execute(c, ctx)->get_color() = _color->execute(ctx);
	// std::cout << _house->execute(c, ctx)->to_string() << "\n";
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
	else if (rad == 0) error::report("impossible de créer une ville avec rayon nul");

	c.set_radius(rad);
	for (auto const & cmd : _body) {
		cmd->execute(c, ctx);
	}
}
