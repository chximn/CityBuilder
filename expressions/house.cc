#include "house.hh"

house::house(point const & p): coordinates(p) {}

std::string house::to_string() const {
	return coordinates.to_string() + ", " + orientation.to_string();
}
