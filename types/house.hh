#pragma once
#include "point.hh"
#include "degree.hh"
#include "color.hh"
#include <string>
#include <vector>
#include <exception>
#include <memory>
#include <cmath>

class house;
using house_ptr = std::shared_ptr<house>;

class house {
private:
	point coordinates;
	degree orientation;
	std::string name;
	color _color;
	std::vector<house_ptr> neighbors;
public:
	house() = default;
	house(point const &);
	house(point const &, degree const &);
	house(point const &, degree const &, std::string const &);

	std::string to_string() const;
	color & get_color();
	point & get_coordinates();
	degree &get_orientation();
	std::string const & get_name() const;
	void add_neighbor(house_ptr);
	void remove_neigbor(house_ptr);
	void clear_neighbors();
	std::vector<house_ptr> const & get_neighbors();
	int distance(house_ptr);

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

class full_neighborhood : public std::exception {
private:
	point coordinates;
public:
	full_neighborhood(point const & p): coordinates(p) {}
	const char * what() const noexcept override {
		return "Full neighborhood\n";
	}
};
