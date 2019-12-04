#include "color.hh"

color::color(int _r, int _g, int _b): r(_r), g(_g), b(_b) {
	if (_r < 0 || _r > 255 || _g < 0 || _g > 255 || _b < 0 || _b > 255) throw color_not_valid();
}

color::color(std::string const & s) {
	if (s.length() != 7 || s[0] != '#') throw color_not_valid();

	int vals[6];

	for (int i = 1; i < 7; i++) {
		if (s[i] >= '0' && s[i] <= '9') {
			vals[i - 1] = s[i] - '0';
		}

		else if (s[i] >= 'a' || s[i] <= 'f') {
			vals[i - 1] = s[i] - 'a' + 10;
		}

		else throw color_not_valid();
	}

	r = vals[0] * 16 + vals[1];
	g = vals[2] * 16 + vals[3];
	b = vals[4] * 16 + vals[5];
}

std::string color::to_string() const {
    return "(" + std::to_string(r) +
           "," + std::to_string(g) +
           "," + std::to_string(b) + ")";
}
