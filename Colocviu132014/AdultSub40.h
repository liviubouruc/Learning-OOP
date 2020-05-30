#pragma once

#include "Pacient.h"

class AdultSub40 : public Pacient
{
public:
	AdultSub40(std::string = "", std::string = "", std::string = "", int = 0, int = 0, int = 0, std::string = "", std::string = "");
	AdultSub40(const AdultSub40&);
	AdultSub40& operator =(const AdultSub40&);
	~AdultSub40();

	virtual void citire();
	virtual void afisare();
	virtual std::string getRiscCardiovascular();
};