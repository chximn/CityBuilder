#pragma once
#include <iostream>
#include <string>
#include <exception>
#include "point.hh"

class color {
private:
    point rgb;
public:
    color() = default;
    color(point const &);
    color(std::string const &);
    std::string to_string() const;

	int get_r() { return rgb.get_x(); }
	int get_g() { return rgb.get_y(); }
	int get_b() { return rgb.get_z(); }
};

class color_not_valid : public std::exception {
public:
	const char * what() const noexcept override {
		return "Color Not Valid\n";
	}
};
