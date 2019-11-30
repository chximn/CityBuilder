#pragma once
#include <string>

class Point {
private:
	int x, y, z;

public:
	Point() = default;
	Point(Point const &) = default;
	Point(int, int, int);

	int getX() const;
	int getY() const;
	int getZ() const;

	std::string toString() const;
};
