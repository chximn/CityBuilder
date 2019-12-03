#pragma once
#include <iostream>
#include <string>

class color {
private:
    int r, g, b;
public:
    color() = default;
    color(int, int, int);
    color(std::string const &);
    std::string to_string() const;
};
