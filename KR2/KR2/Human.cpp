#include "Human.h"

Human::Human(Gender g, std::string n) : gender(g), name(n) {};

Human::Gender Human::getGender() const {
	return gender;
}

std::string Human::getName() const {
	return name;
}