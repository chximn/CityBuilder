#include "house.hh"

house::house(point const & p): coordinates(p) {}
house::house(point const & p, degree const & d): house(p), orientation(d) {}
house::house(point const & p, degree const & d, string const & s): house(p, d), name(s) {}

std::string house::to_string() const {
	return coordinates.to_string() + ", " + orientation.to_string();
}
