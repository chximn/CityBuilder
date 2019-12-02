#pragma once

#include "point.hh"

class house {
private:
	point coordinates;

public:
	house() = default;
	house(point const &);
};
