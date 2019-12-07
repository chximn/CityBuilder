#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "contexte.hh"
#include "../GUI/city.hh"
#include "point.hh"
#include "house.hh"
#include "city.hh"

using CityGUI = VilleGUI;

class Driver {
private:
    Contexte variables;
	city _city;
	CityGUI * gui;

public:
    Driver() { gui = new VilleGUI(); }
    ~Driver() = default;
    Driver(const Driver&) = default;

	Contexte & getContexte();
    int  getVariable(const std::string & name) const;
    void setVariable(const std::string & name, double value);
    city & get_city();
    CityGUI * & getGUI() { return gui; };

	void show();
};

#endif
