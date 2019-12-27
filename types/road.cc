#include "road.hh"

int road::get_distance() const { return _house1->distance(_house2); }
