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
void destruct_road::execute(city & c, Contexte  & ctx) {
	auto h1 = _house1->execute(c, ctx);
	auto h2 = _house2->execute(c, ctx);
	h1->remove_neighbor(h2);
	h2->remove_neighbor(h1);
}

void destruct_house::execute(city & c, Contexte  & ctx) {
	for(auto const & x:_house->execute(c, ctx)->get_neighbors())
		x->remove_neighbor((_house->execute(c, ctx)));
	c.remove_house(*(_house->execute(c, ctx)));
}

void position_house::execute(city & c, Contexte  & ctx) {
	os << _house->execute(c, ctx)->get_coordinates().to_string();
}

void turn_house::execute(city & c, Contexte  & ctx) {
	c.remove_house(*(_house->execute(c, ctx)));
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

void orientation_house::execute(city & c, Contexte  & ctx) {
	os << _house->execute(c, ctx)->get_orientation().to_string()<<"\n";
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

void assignment::execute(city & c, Contexte & ctx) {
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

void function::execute(city & cit, Contexte & ctx) {
	for (auto const & c : _body) {
		c->execute(cit, ctx);
	}
}

void function_call::execute(city & c, Contexte & ctx) {

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

	else throw "function does not exist";
}

void for_loop::execute(city & c, Contexte & ctx) {
	_init->execute(c, ctx);

	while (_cond->calculer(ctx)) {
		for (auto const & cmd : _body) {
			cmd->execute(c, ctx);
		}

		_inc->execute(c, ctx);
	}
}

void city_construction::execute(city & c, Contexte & ctx) {
	c.set_radius(_radius);
	for (auto const & cmd : _body) {
		cmd->execute(c, ctx);
	}
}
