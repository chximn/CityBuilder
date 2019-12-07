#pragma once
#include <memory>
#include "city.hh"
#include "house.hh"

namespace commands {
	class command;
	class construct_house;
}

using command_ptr = std::shared_ptr<commands::command>;


class commands::command {
private:
public:
	command() = default;
	virtual void execute(city &) = 0;
};

class commands::construct_house : public commands::command {
private:
	house _house;

public:
	construct_house(house const & h): _house(h) {}
	void execute(city &) override;
};
