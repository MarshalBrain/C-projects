#pragma once

#include "Human.h"

class Parent : public Human {
public:
	Parent(Gender, std::string, int);

	void getInfo(std::ostream&) const;
	std::string who() const;

	int getID() const;
private:
	int ID;
	std::string name;
};