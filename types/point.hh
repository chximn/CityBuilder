#pragma once
#include <string>

class point {
private:
	int x, y, z;

public:
	point(): x(0), y(0), z(0) {}
	point(point const &) = default;
	point(int, int, int);
	point(int);

	int get_x() const;
	int get_y() const;
	int get_z() const;

	void set_x(int);
	void set_y(int);
	void set_z(int);

	std::string to_string() const;

	bool operator==(point const &) const;
	bool operator!=(point const &) const;

	void translate(point const &);
	void rotate();
};
