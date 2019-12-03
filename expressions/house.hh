#pragma once

#include "point.hh"
#include "degree.hh"
#include <string>
#include <exception>
#include "point.hh"

class house {
private:
	point coordinates;
	degree orientation;
	std::string name;

public:
	house() = default;
	house(point const &);
	house(point const &, degree const &);
	house(point const &, degree const &, std::string const &);

	degree & get_orientation();
	point  & get_coordinates();

	std::string to_string() const;
};


class house_not_found_coordinates : public std::exception {
private:
	point coordinates;
public:
	house_not_found(point const & p): coordinates(p) {}
	const char * what() const {
		return "House not found at: " + coordinates.to_string() + "\n";
	}
};

class house_not_found_list : public std::exception {
private:
	int index;
public:
	house_not_found(int i): index(i) {}
	const char * what() const {
		return "House not found at index: " + std::to_string(index) + "\n";
	}
};

class house_not_found_var : public std::exception {
private:
	std::string var;
public:
	house_not_found(std::string const & s): var(s) {}
	const char * what() const {
		return "House not found with name: " + var + "\n";
	}
};

class house_already_exists : public std::exception {
private:
	point coordinates;
public:
	house_already_exists(point const & p): coordinates(p) {}
	const char * what() const {
		return "Another house already exists at: " + coordinates.to_string() + "\n";
	}
};
