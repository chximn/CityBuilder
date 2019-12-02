#include "degree.hh"

degree degree::operator+(float v) {
	return degree(val + v);
}

degree degree::operator+(degree const & d) {
	return degree(val + d.val);
}

degree degree::operator-(float v) {
	return degree(val - v);
}

degree degree::operator-(degree const & d) {
	return degree(val - d.val);
}

degree degree::operator=(float v) {
	val = v;
	return *this;
}

degree degree::operator =(degree const & d) {
	val = d.val;
	return *this;
}

void degree::turn(bool clockwise) {
	val += 60 * (clockwise ? -1 : 1);
}
