#pragma once
#include "house.hh"
#include <memory>

class road;
using road_ptr = std::shared_ptr<road>;

class road {
private:
	house_ptr _house1;
	house_ptr _house2;

public:
	road(house_ptr h1, house_ptr h2): _house1(h1), _house2(h2) {}
	house_ptr get_house1() const { return _house1; }
	house_ptr get_house2() const { return _house2; }
	int get_distance() const { return _house1->distance(_house2); }
};
