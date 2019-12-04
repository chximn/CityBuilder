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
};

class color_not_valid : public std::exception {
public:
	const char * what() const noexcept override {
		return "Color Not Valid\n";
	}
};
