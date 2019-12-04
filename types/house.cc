#include "house.hh"

house::house(point const & p): coordinates(p) {}
house::house(point const & p, degree const & d): coordinates(p), orientation(d) {}
house::house(point const & p, degree const & d, std::string const & s): coordinates(p), orientation(d), name(s) {}

std::string house::to_string() const {
	return name + coordinates.to_string() + ", " + orientation.to_string() + " : " + _color.to_string();
}

color const & house::get_color()const {
	return _color;
}
