#include "color.hh"

color::color(point const & p): rgb(p) {
	if (p.get_x() < 0 || p.get_x() > 255 || p.get_y() < 0 || p.get_y() > 255 || p.get_z() < 0 || p.get_z() > 255)
		error::report("La couleur " + p.to_string() + " n'est pas valide");
}

color::color(std::string const & s) {
	if (s.length() != 7 || s[0] != '#')
		error::report("La couleur " + s + " n'est pas valide");

	int vals[6];
	for (int i = 1; i < 7; i++) {
		if (s[i] >= '0' && s[i] <= '9') {
			vals[i - 1] = s[i] - '0';
		}

		else if (s[i] >= 'a' || s[i] <= 'f') {
			vals[i - 1] = s[i] - 'a' + 10;
		}

		else error::report("La couleur " + s + " n'est pas valide");
	}

	rgb.set_x(vals[0] * 16 + vals[1]);
	rgb.set_y(vals[2] * 16 + vals[3]);
	rgb.set_z(vals[4] * 16 + vals[5]);
}

std::string color::to_string() const {
    return "(" + std::to_string(rgb.get_x()) +
           "," + std::to_string(rgb.get_y()) +
           "," + std::to_string(rgb.get_z()) + ")";
}
