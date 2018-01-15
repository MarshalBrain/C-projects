#include "Parent.h"

#include <string>

Parent::Parent(Gender g, std::string n, int id) : Human(g, n), ID(id), name(n) {}

int Parent::getID() const {
	return ID;
}

std::string Parent::who() const {
	return "Parent";
}

void Parent::getInfo(std::ostream& out) const {
	out << "Name: " << name << "\tGender: " << (getGender() == MAN ? "M" : "W") << "\tID: " << ID << std::endl;
}