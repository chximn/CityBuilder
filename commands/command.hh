#pragma once
#include <memory>
#include <ostream>
#include "city.hh"
#include "house.hh"
#include "road.hh"
#include "house_ref.hh"
#include "point_ref.hh"
#include "degree_ref.hh"
#include "color_ref.hh"
#include "contexte.hh"
#include "expression.hh"
#include <chrono>

namespace commands {

class command;
using command_ptr = std::shared_ptr<command>;

class command {
private:
public:
	command() = default;
	virtual void execute(city &, Contexte  &) = 0;
};

class construct_house : public command {
private:
	house_ref_ptr _house;

public:
	construct_house(house_ref_ptr h): _house(h) {}
	void execute(city &, Contexte  &) override;
};

class construct_road : public command {
private:
	house_ref_ptr _house1;
	house_ref_ptr _house2;
	bool _directed = false;
public:
	construct_road(house_ref_ptr h1, house_ref_ptr h2): _house1(h1), _house2(h2) {}
	construct_road(house_ref_ptr h1, house_ref_ptr h2, bool d): _house1(h1), _house2(h2), _directed(d) {}
	void execute(city &, Contexte  &) override;
};

class destruct_house : public command {
private:
	house_ref_ptr _house;
public:
	destruct_house(house_ref_ptr h): _house(h) {}
	void execute(city &, Contexte  &) override;
};

class position_house: public command {
private:
	house_ref_ptr _house;
	std::ostream & os;
public:
	position_house(house_ref_ptr h, std::ostream & s): _house(h), os(s) {}
	void execute(city &, Contexte  &) override;
};

class turn_house: public command {
private:
	house_ref_ptr _house;
	bool _clockwise;

public:
	turn_house(house_ref_ptr h, bool c): _house(h), _clockwise(c) {}
	void execute(city &, Contexte  &) override;
};

class show_neighborhood: public command {
private:
	house_ref_ptr _house;
	std::ostream & os;
public:
	show_neighborhood(house_ref_ptr h, std::ostream & s): _house(h), os(s) {}
	void execute(city &, Contexte  &) override;
};

class orientate_house: public command {
private:
	house_ref_ptr _house;
	degree_ref_ptr _degree;
public:
	orientate_house(house_ref_ptr h, degree_ref_ptr d): _house(h), _degree(d) {}
	void execute(city &, Contexte  &) override;
};

class move_house: public command {
private:
	house_ref_ptr _house;
	point_ref_ptr _coordinates;
public:
	move_house(house_ref_ptr h, point_ref_ptr p): _house(h), _coordinates(p) {}
	void execute(city &, Contexte  &) override;
};

class colorize_house: public command {
private:
	house_ref_ptr _house;
	color_ref_ptr _color;
public:
	colorize_house(house_ref_ptr h, color_ref_ptr c): _house(h), _color(c) {}
	void execute(city &, Contexte  &) override;
};

class show_color: public command {
private:
	house_ref_ptr _house;
	std::ostream & os;
public:
	show_color(house_ref_ptr h, std::ostream & s): _house(h), os(s) {}
	void execute(city &, Contexte  &) override;
};

class add_neighbor: public command {
private:
	house_ref_ptr _house;
	ExpressionPtr _expression;
public:
	add_neighbor(house_ref_ptr h, ExpressionPtr e): _house(h), _expression(e) {}
	void execute(city &, Contexte  &) override;
};

class assignment : public command {
private:
	std::string _var;
	ExpressionPtr _expression;

public:
	assignment(std::string v, ExpressionPtr e): _var(v), _expression(e) {}
	void execute(city &, Contexte  &) override;
};

class if_condition : public command {
private:
	ExpressionPtr _condition;
	std::vector<command_ptr> _body;
public:
	if_condition(ExpressionPtr c, std::vector<command_ptr> vc): _condition(c), _body(vc) {}
	void execute(city &, Contexte  &) override;
};

class if_else_condition : public command {
private:
	ExpressionPtr _condition;
	std::vector<command_ptr> _body;
	std::vector<command_ptr> _body2;
public:
	if_else_condition(ExpressionPtr c, std::vector<command_ptr> vc, std::vector<command_ptr> vc2): _condition(c), _body(vc), _body2(vc2) {}
	void execute(city &, Contexte  &) override;
};

class while_loop : public command {
private:
	ExpressionPtr _condition;
	std::vector<command_ptr> _body;
public:
	while_loop(ExpressionPtr c, std::vector<command_ptr> vc): _condition(c), _body(vc) {}
	void execute(city &, Contexte  &) override;
};

class repeat_loop : public command {
private:
	ExpressionPtr _times;
	std::vector<command_ptr> _body;
public:
	repeat_loop(ExpressionPtr t, std::vector<command_ptr> vc): _times(t), _body(vc) {}
	void execute(city &, Contexte  &) override;
};

class pcc : public command {
private:
	house_ref_ptr _house1;
	house_ref_ptr _house2;
	std::ostream & os;
public:
	pcc(house_ref_ptr h1, house_ref_ptr h2, std::ostream & s): _house1(h1), _house2(h2), os(s) {}
	void execute(city &, Contexte  &) override;
};

class tarjan_algorithm : public command {
public:
	tarjan_algorithm() = default;
	void execute(city &, Contexte  &) override;
};

class kruksal_algorithm : public command {
public:
	kruksal_algorithm() = default;
	void execute(city &, Contexte &) override;
};

class welsh_powell_algorithm : public command {
public:
	welsh_powell_algorithm() = default;
	void execute(city &, Contexte &) override;
};

}
