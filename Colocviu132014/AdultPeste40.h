#pragma once

#include "Pacient.h"

class AdultPeste40 : public Pacient
{
	bool fumator;
	std::string sedentarism;
public:
	AdultPeste40(std::string = "", std::string = "", std::string = "", int = 0, int = 0, int = 0, std::string = "", std::string = "", bool = 0, std::string = "");
	AdultPeste40(const AdultPeste40&);
	AdultPeste40& operator =(const AdultPeste40&);
	~AdultPeste40();

	virtual void citire();
	virtual void afisare();
	virtual std::string getRiscCardiovascular();
};