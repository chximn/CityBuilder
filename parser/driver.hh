#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <vector>

#include "contexte.hh"
#include "point.hh"
#include "house.hh"

class Driver {
private:
    Contexte variables;
	std::vector<house> houses;

public:
    Driver() = default;
    ~Driver() = default;
    Driver(const Driver&) = default;

	const Contexte& getContexte() const;
    int  getVariable(const std::string & name) const;
    void setVariable(const std::string & name, double value);

	house const & get_house(std::string const &);
	house const & get_house(unsigned int);
	house const & get_house(point const &);

	void add_house(house const &);
};

#endif
