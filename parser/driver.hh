#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <vector>
#include <memory>
#include "contexte.hh"
#include "point.hh"
#include "house.hh"

class Driver {
private:
    Contexte variables;
	std::vector<house_ptr> houses;

public:
    Driver() = default;
    ~Driver() = default;
    Driver(const Driver&) = default;

	const Contexte& getContexte() const;
    int  getVariable(const std::string & name) const;
    void setVariable(const std::string & name, double value);

	house_ptr get_house(std::string const &);
	house_ptr get_house(unsigned int);
	house_ptr get_house(point const &);
	void add_house(house_ptr);
	void remove_house(house &);
};

#endif
