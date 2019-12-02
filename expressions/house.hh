#pragma once

#include "point.hh"

class house {
private:
	point coordinates;
	degree orientation;

public:
	house() = default;
	house(point const &);
};
