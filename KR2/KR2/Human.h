#pragma once

#include <iostream>

class Human {
public:
	enum Gender { MAN, WOMAN };
	Human(Gender, std::string);
	virtual void getInfo(std::ostream&) const = 0;
	virtual std::string who() const = 0;
	
	std::string getName() const;
	Gender getGender() const;
protected:
	Gender gender;
	std::string name;
};
