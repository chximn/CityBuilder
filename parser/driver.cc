#include "driver.hh"
#include <iostream>

const Contexte& Driver::getContexte() const {
    return variables;
}
double Driver::getVariable(const std::string & name) const {
  return variables[name];
}
void Driver::setVariable(const std::string & name, double value) {
  variables[name]=value;
}
