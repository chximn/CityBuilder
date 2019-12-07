#include "command.hh"

void commands::construct_house::execute(city & c) {
	c.add_house(std::make_shared<house>(_house));
}
