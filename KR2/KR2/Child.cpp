#include "Child.h"

Child::Child(Gender g, std::string n, Human* m, Human* f) : Human(g, n), mother(m), father(f) {}

void Child::getInfo(std::ostream& out) const {
	out << "Name: " << name << "\tGender: " << (getGender() == MAN ? "M" : "W") << '\t';
	out << "Mother: ";
	if (!mother) out << "---\t";
	else out << mother->getName() << '\t';

	out << "Father: ";
	if (!father) out << "---\t";
	else out << father->getName() << '\t';
	out << std::endl;
}

std::string Child::who() const {
	return "Child";
}

const Human& Child::getMother() const {
	return *mother;
}

const Human& Child::getFather() const {
	return *father;
}