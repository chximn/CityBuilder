#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <vector>
#include <memory>
#include "contexte.hh"
#include "../IG/villeGUI.hh"
#include "point.hh"
#include "house.hh"
#include "ville.hh"
class Driver {
private:
    Contexte variables;
	ville _ville;
	VilleGUI* V;

public:
    Driver() { V = new VilleGUI(); }
    ~Driver() = default;
    Driver(const Driver&) = default;

	const Contexte& getContexte() const;
    int  getVariable(const std::string & name) const;
    void setVariable(const std::string & name, double value);
    ville & get_ville();

	void show();
};

#endif
