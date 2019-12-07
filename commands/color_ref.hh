#pragma once
#include <memory>
#include "color.hh"
#include "point_ref.hh"

class color_ref;
using color_ref_ptr = std::shared_ptr<color_ref>;

class color_ref {
public:
	color_ref() = default;
	virtual color execute(Contexte const &) const = 0;
};

class color_ref_hex : public color_ref {
private:
	std::string _hex;
public:
	color_ref_hex(std::string const & s): _hex(s) {}
	color execute(Contexte const &) const override;
};

class color_ref_point : public color_ref {
private:
	point_ref_ptr _point;
public:
	color_ref_point(point_ref_ptr p): _point(p) {}
	color execute(Contexte const &) const override;
};
