#include "degree.hh"

const char * degree_not_valid::what() const noexcept {
	return std::string("Invalid Degree Value\n").c_str();
}

degree degree::operator+(int v) {
	if (v % 60 != 0) throw degree_not_valid();
	return degree((val + v) % 360);
}

degree degree::operator+(degree const & d) {
	if (d.val % 60 != 0) throw degree_not_valid();
	return degree((val + d.val) % 360);
}

degree degree::operator-(int v) {
	if (v % 60 != 0) throw degree_not_valid();
	return degree((val - v) % 360);
}

degree degree::operator-(degree const & d) {
	if (d.val % 60 != 0) throw degree_not_valid();
	return degree((val - d.val) % 360);
}

degree degree::operator=(int v) {
	if (v % 60 != 0) throw degree_not_valid();
	val = v % 360;
	return *this;
}

degree degree::operator =(degree const & d) {
	if (d.val % 60 != 0) throw degree_not_valid();
	val = d.val;
	return *this;
}

void degree::turn(bool clockwise) {
	val = (val + 60 * (clockwise ? -1 : 1)) % 360;
}
