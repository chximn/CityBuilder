#include "point.hh"

point::point(int a, int b, int c):
	x(a), y(b), z(c) {}

int point::getX() const {
	return x;
}

int point::getY() const {
	return y;
}

int point::getZ() const {
	return z;
}

std::string point::to_string() const {
	return '(' + std::to_string(x) + ","
	           + std::to_string(y) + ","
			   + std::to_string(z) + ")";
}
