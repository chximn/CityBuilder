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
	std::vector<house_ptr> get_neighbors();
	void remove_neighbor(house_ptr);
	int distance(house_ptr);
};
