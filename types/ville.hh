#pragma once
#include <string>
#include <vector>
#include <exception>
#include <memory>
#include <cmath>
#include "house.hh"
class ville
{
private:
    std::vector<house_ptr> houses;
public:
    ville() = default;
    ~ville() = default;
    ville(ville const &) = default;
    void add_house(house_ptr);
    void remove_house(house &);
    std::vector<house_ptr> & get_houses();
    house_ptr get_house(std::string const &);
    house_ptr get_house(unsigned int);
    house_ptr get_house(point const &);
    house_ptr add_neighbor(house_ptr, int);

};
