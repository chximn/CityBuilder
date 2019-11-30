#pragma once

#include "point.hh"

class House {
private:
	Point coordinates;

public:
	House() = default;
	House(Point const &);
};
