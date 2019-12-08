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
	c.remove_house(*(_house->execute(c, ctx)));
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
	auto l = c.a_star(_house1->execute(c, ctx), _house2->execute(c, ctx));

	auto it = l.begin();
	os << (*it)->get_name();
	while(true) {
		if (++it == l.end()) {
			os << "\n";
			return;
		}

		os << " -> " << (*it)->get_name();
	}

}
