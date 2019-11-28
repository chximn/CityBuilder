#ifndef DRIVER_H
#define DRIVER_H

#include <string>

#include "contexte.hh"

class Driver {
private:
    Contexte variables;       

public:
    Driver() = default;
    ~Driver() = default;
    Driver(const Driver&) = default;
};

#endif
