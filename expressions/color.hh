#pragma once
#include <iostream>
#include <string>
#include <exception>

class color {
private:
    int r, g, b;
public:
    color() = default;
    color(int, int, int);
    color(std::string const &);
    std::string to_string() const;
};

class color_not_valid : public std::exception {
public:
	const char * what() const noexcept override {
		return "Color Not Valid\n";
	}
};
