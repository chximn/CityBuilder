#pragma once

#include "point.hh"
#include "degree.hh"

class house {
private:
	point coordinates;
	degree orientation;

public:
	house() = default;
	house(point const &);

	degree & get_orientation();
	point  & get_coordinates();
};
