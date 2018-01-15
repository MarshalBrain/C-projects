#pragma once

#include "Human.h"

#include <string>

class Child : public Human {
public:
	Child(Gender, std::string, Human* m, Human* f);

	void getInfo(std::ostream&) const;
	std::string who() const;

	const Human& getMother() const;
	const Human& getFather() const;
private:
	Human* mother;
	Human* father;
};

