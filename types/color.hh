#pragma once
#include <iostream>
#include <string>
#include "point.hh"
#include "error.hh"

class color {
private:
    point rgb;
public:
    color(): rgb(255, 0, 0) {}
    color(point const &);
    color(std::string const &);
    std::string to_string() const;

	int get_r() { return rgb.get_x(); }
	int get_g() { return rgb.get_y(); }
	int get_b() { return rgb.get_z(); }
};
