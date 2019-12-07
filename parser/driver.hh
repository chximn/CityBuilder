#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <vector>
#include <memory>
#include "contexte.hh"
#include "../IG/villeGUI.hh"
#include "point.hh"
#include "house.hh"

class Driver {
private:
    Contexte variables;
	std::vector<house_ptr> houses;
	VilleGUI* V;

public:
    Driver() { V = new VilleGUI(); }
    ~Driver() = default;
    Driver(const Driver&) = default;

	const Contexte& getContexte() const;
    int  getVariable(const std::string & name) const;
    void setVariable(const std::string & name, double value);

	house_ptr get_house(std::string const &);
	house_ptr get_house(unsigned int);
	house_ptr get_house(point const &);
	void add_house(house_ptr);
	house_ptr add_neighbor(house_ptr, int);
	void remove_house(house &);
	VilleGUI* getVille() {return V;}

	void show();
};

#endif
