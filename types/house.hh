#pragma once
#include "point.hh"
#include "degree.hh"
#include <string>
#include <exception>
#include "point.hh"
#include "color.hh"

class house {
private:
	point coordinates;
	degree orientation;
	std::string name;
	color _color;

public:
	house() = default;
	house(point const &);
	house(point const &, degree const &);
	house(point const &, degree const &, std::string const &);

	std::string to_string() const;
	color const & get_color() const;
};


class house_not_found_coordinates : public std::exception {
private:
	point coordinates;
public:
	house_not_found_coordinates(point const & p): coordinates(p) {}
	const char * what() const noexcept override {
		return "House not found\n";
	}
};

class house_not_found_list : public std::exception {
private:
	int index;
public:
	house_not_found_list(int i): index(i) {}
	const char * what() const noexcept override {
		return "House not found at index\n";
	}
};

class house_not_found_var : public std::exception {
private:
	std::string var;
public:
	house_not_found_var(std::string const & s): var(s) {}
	const char * what() const noexcept override {
		return "House not found with name\n";
	}
};

class house_already_exists : public std::exception {
private:
	point coordinates;
public:
	house_already_exists(point const & p): coordinates(p) {}
	const char * what() const noexcept override {
		return "Another house already exists\n";
	}
};
