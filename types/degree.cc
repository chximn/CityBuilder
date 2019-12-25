#include "degree.hh"

degree::degree(int v) {
	val = v % 360;
}

degree degree::operator+(int v) {
	return degree((val + v) % 360);
}

degree degree::operator+(degree const & d) {
	return degree((val + d.val) % 360);
}

degree degree::operator-(int v) {
	int diff = val - v;
	if (diff < 0) diff += 360;
	return diff;
}

degree degree::operator-(degree const & d) {
	int diff = val - d.val;
	if (diff < 0) diff += 360;
	return diff;
}

degree degree::operator=(int v) {
	val = v % 360;
	return *this;
}

degree degree::operator =(degree const & d) {
	val = d.val;
	return *this;
}

void degree::turn(bool clockwise) {
	val = (val + 60 * (clockwise ? +1 : -1)) % 360;
	if (val < 0) val += 360;
}

std::string degree::to_string() const {
	return std::to_string(val) + "deg";
}
