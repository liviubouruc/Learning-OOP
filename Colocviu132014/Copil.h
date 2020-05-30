#pragma once

#include "Pacient.h"

class Copil : public Pacient
{
	bool antecedente;
	std::string numeMama, numeTata;
	double proteinaC;
	std::string dataProteinaC;
public:
	Copil(std::string = "", std::string = "", std::string = "", int = 0, int = 0, int = 0, std::string = "", std::string = "", bool = 0, std::string = "", std::string = "", double = 0, std::string = "");
	Copil(const Copil&);
	Copil& operator =(const Copil&);
	~Copil();

	virtual void citire();
	virtual void afisare();
	virtual std::string getRiscCardiovascular();
};