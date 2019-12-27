#include "point.hh"

point::point(int distance) {
	if (distance == 0) {
		x = 0;
		y = 0;
		z = 0;
	}

	else {
		int sign = (rand()%2)*2-1;
		int asign = sign > 0 ? -1 : 1;

		int a = distance * sign;
		int b = (rand() % distance) * asign;
		int c = (distance - abs(b)) * asign;

		int coords[] = {0, 0, 0};
		int pivot = rand() % 3;

		coords[pivot] = a;
		coords[(pivot+1)%3] = b;
		coords[(pivot+2)%3] = c;

		x = coords[0];
		y = coords[1];
		z = coords[2];
	}

}

point::point(int a, int b, int c): x(a), y(b), z(c) {}

int point::get_x() const {
	return x;
}

int point::get_y() const {
	return y;
}

int point::get_z() const {
	return z;
}

void point::set_x(int n) {
	x = n;
}

void point::set_y(int n) {
	y = n;
}

void point::set_z(int n) {
	z = n;
}

std::string point::to_string() const {
	return '(' + std::to_string(x) + ","
	           + std::to_string(y) + ","
			   + std::to_string(z) + ")";
}

bool point::operator==(point const & p) const {
	return x == p.x && y == p.y && z == p.z;
}

bool point::operator!=(point const & p) const {
	return !(operator==(p));
}

void point::translate(point const & p) {
	x += p.x;
	y += p.y;
	z += p.z;
}

void point::rotate() {
	if (x == 0 && y == 0 && z == 0) return;

	int pivot;
	if (x == 0) pivot = 2;
	else if (y == 0) pivot = 0;
	else if (z == 0) pivot = 1;
	else if (abs(x) > abs(y) && abs(x) > abs(z)) pivot = 0;
	else if (abs(y) > abs(x) && abs(y) > abs(z)) pivot = 1;
	else pivot = 2;

	if (pivot == 0) {
		int sign = (x > 0) ? 1 : -1;
		y -= sign;
		z += sign;
	}

	else if (pivot == 1) {
		int sign = (y > 0) ? 1 : -1;
		z -= sign;
		x += sign;
	}

	else {
		int sign = (z > 0) ? 1 : -1;
		x -= sign;
		y += sign;
	}
}

bool point::is_valid_coordinates() {
	return (x + y + z == 0);
}
