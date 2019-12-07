#include "house_ref.hh"

std::string house_ref_name::to_string() const {
	return name;
}

std::string house_ref_index::to_string() const {
	return "maison[" + std::to_string(index) + "]";
}

std::string house_ref_coordinates::to_string() const {
	return coordinates.to_string();;
}
