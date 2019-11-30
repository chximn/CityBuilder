#include "point.hh"

Point::Point(int a, int b, int c):
	x(a), y(b), z(c) {}

int Point::getX() const {
	return x;
}

int Point::getY() const {
	return y;
}

int Point::getZ() const {
	return z;
}

std::string Point::toString() const {
	return '(' + std::to_string(x) + ","
	           + std::to_string(y) + ","
			   + std::to_string(z) + ")";
}
