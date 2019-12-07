#include "command.hh"

using namespace commands;

void construct_house::execute(city & c, Contexte const & ctx) {
	c.add_house(_house->execute(c, ctx));
}

void construct_road::execute(city & c, Contexte const & ctx) {
	auto h1 = _house1->execute(c, ctx);
	auto h2 = _house2->execute(c, ctx);

	h1->add_neighbor(h2);
	h2->add_neighbor(h1);
}

void destruct_house::execute(city & c, Contexte const & ctx) {
	c.remove_house(*(_house->execute(c, ctx)));
}

void position_house::execute(city & c, Contexte const & ctx) {
	os << _house->execute(c, ctx)->get_coordinates().to_string();
}

void turn_house::execute(city & c, Contexte const & ctx) {
	_house->execute(c, ctx)->get_orientation().turn(_clockwise);
}

void show_neighborhood::execute(city & c, Contexte const & ctx) {
	auto house = _house->execute(c, ctx);
	for (auto const & h : house->get_neighbors()) {
		os << h->to_string() << ", distance : " << house->distance(h) << "\n";
	}
}

void orientate_house::execute(city & c, Contexte const & ctx) {
	_house->execute(c, ctx)->get_orientation() = _degree->execute(ctx);
}

void move_house::execute(city & c, Contexte const & ctx) {
	_house->execute(c, ctx)->get_coordinates() = _coordinates->execute(ctx);
}

void colorize_house::execute(city & c, Contexte const & ctx) {
	_house->execute(c, ctx)->get_color() = _color->execute(ctx);
}

void show_color::execute(city & c, Contexte const & ctx) {
	os << _house->execute(c, ctx)->get_color().to_string();
}

void add_neighbor::execute(city & c, Contexte const & ctx) {
	c.add_neighbor(_house->execute(c, ctx), _expression->calculer(ctx));
}
