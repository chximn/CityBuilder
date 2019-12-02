#pragma once
#include <string>
#include <exception>

class degree {
private:
	int val = 0;

public:
	degree() = default;
	degree(int v);
	degree(degree const & d): val(d.val) {}

	int get_value() const { return val; }

	degree operator +(int v);
	degree operator +(degree const & d);
	degree operator -(int v);
	degree operator -(degree const & d);
	degree operator =(int v);
	degree operator =(degree const & d);

	void turn(bool);
};

class degree_not_valid : public std::exception {
public:
	const char * what() const noexcept override;
};
