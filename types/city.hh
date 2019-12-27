#pragma once
#include <string>
#include <vector>
#include <exception>
#include <memory>
#include <cmath>
#include "house.hh"
#include "error.hh"

class city
{
private:
    std::vector<house_ptr> houses;
	int radius;
public:
    city() = default;
    ~city() = default;
    city(city const &) = default;
    void add_house(house_ptr);
	house_ptr add_random_house(house_ptr);
    void remove_house(house &);
    std::vector<house_ptr> & get_houses();
    house_ptr get_house(std::string const &);
    house_ptr get_house(unsigned int);
    house_ptr get_house(point const &);
    house_ptr add_neighbor(house_ptr, int);
	void set_radius(int r);
	int get_radius() const { return radius; }

	void a_star(house_ptr, house_ptr);
	void tarjan();
	void kruksal();
	void k_coloring();
};
