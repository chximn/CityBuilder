#include "point.hh"

point::point(int a, int b, int c):
	x(a), y(b), z(c) {}

int point::get_x() const {
	return x;
}

int point::get_y() const {
	return y;
}

int point::get_z() const {
	return z;
}

void point::set_x(int n) {
	x = n;
}

void point::set_y(int n) {
	y = n;
}

void point::set_z(int n) {
	z = n;
}

std::string point::to_string() const {
	return '(' + std::to_string(x) + ","
	           + std::to_string(y) + ","
			   + std::to_string(z) + ")";
}

bool point::operator==(point const & p) const {
	return x == p.x && y == p.y && z == p.z;
}
