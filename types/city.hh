#pragma once
#include <list>
#include <string>
#include <map>
#include <vector>
#include <exception>
#include <memory>
#include <cmath>
#include <exception>
#include <iostream>
#include <algorithm>
#include <stack>
#include <utility>
#include <set>
#include "house.hh"
#include "road.hh"

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
    void remove_house(house_ptr);
	void clear_houses();
    std::vector<house_ptr> & get_houses();
    house_ptr get_house(std::string const &);
    house_ptr get_house(unsigned int);
    house_ptr get_house(point const &);
    house_ptr add_neighbor(house_ptr, int);
	void set_radius(int r) { radius = r; }
	int get_radius() const { return radius; }
	std::vector<road_ptr> get_roads() const;

 	std::list<house_ptr> a_star(house_ptr, house_ptr);
 	std::list<house_ptr> dijkstra(house_ptr, house_ptr);
	std::vector<std::vector<house_ptr>> tarjan();
	std::set<road_ptr> kruksal();
	void k_coloring();

};

class out_of_radius : std::exception {
public:
	const char * what() const noexcept override {
		return "Out Of Range";
	}
};

class path_not_found : std::exception {
public:
	const char * what() const noexcept override {
		return "Path not found!";
	}
};
