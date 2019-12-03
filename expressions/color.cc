#include "color.hh"

color::color(int _r, int _g, int _b): r(_r), g(_g), b(_b) {}

color::color(std::string const & s) {

}

std::string color::to_string() const {
    return "(" + std::to_string(r) +
           "," + std::to_string(g) +
           "," + std::to_string(b) + ")";
}
