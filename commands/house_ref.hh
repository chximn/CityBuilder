#pragma once
#include "point.hh"
#include <memory>
#include <string>
#include "contexte.hh"
#include "expression.hh"
#include "point_ref.hh"
#include "house.hh"
#include "city.hh"

class house_ref;
using house_ref_ptr = std::shared_ptr<house_ref>;

class house_ref {
private:
public:
    house_ref() = default;
	virtual house_ptr execute(city &, Contexte const &) const = 0;
};

class house_ref_coordinates : public house_ref {
private:
	point_ref_ptr coordinates;
public:
	house_ref_coordinates(point_ref_ptr p): coordinates(p){}
	house_ptr execute(city &, Contexte const &) const override;
};

class house_ref_index : public house_ref {
private:
	ExpressionPtr index;
public:
	house_ref_index(ExpressionPtr i): index(i){}
	house_ptr execute(city &, Contexte const &) const override;
};

class house_ref_name : public house_ref {
private:
	std::string name;
public:
	house_ref_name(std::string const & s): name(s) {}
	house_ptr execute(city &, Contexte const &) const override;
};

class house_ref_create : public house_ref {
private:
	std::string name;
	point_ref_ptr coordinates;
public:
	house_ref_create(std::string s, point_ref_ptr p): name(s), coordinates(p) {}
	house_ptr execute(city &, Contexte const &) const override;
};

class house_ref_create_random : public house_ref {
private:
	std::string name;
public:
	house_ref_create_random(std::string s): name(s) {}
	house_ptr execute(city &, Contexte const &) const override;
};
