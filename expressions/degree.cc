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
