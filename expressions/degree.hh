#pragma once

class degree {
private:
	float val = 0;

public:
	degree() = default;
	degree(float v): val(v) {}
	degree(degree const & d): val(d.val) {}

	float get_value() const { return val; }

	degree operator +(float v);
	degree operator +(degree const & d);
	degree operator -(float v);
	degree operator -(degree const & d);
};
