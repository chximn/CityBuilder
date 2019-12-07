#pragma once
#include "point.hh"
#include <string>

class house_ref {
private:
public:
    house_ref() = default;
	virtual std::string to_string() const = 0;
};

class house_ref_coordinates : public house_ref {
private:
	point coordinates;
public:
	house_ref_coordinates(point const & p): coordinates(p){}
	point const & get_coordinates() const { return coordinates; }
	std::string to_string() const override;
};

class house_ref_index : public house_ref {
private:
	int index;
public:
	house_ref_index(int i): index(i){}
	int get_index() const { return index; }
	std::string to_string() const override;
};

class house_ref_name : public house_ref {
private:
	std::string name;
public:
	house_ref_name(std::string const & s): name(s) {}
	std::string const & get_name() const { return name; }
	std::string to_string() const override;
};
