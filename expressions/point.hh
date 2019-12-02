#pragma once
#include <string>

class point {
private:
	int x, y, z;

public:
	point() = default;
	point(point const &) = default;
	point(int, int, int);

	int getX() const;
	int getY() const;
	int getZ() const;

	std::string toString() const;
};
