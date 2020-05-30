#pragma once

#include <iostream>
#include <cstring>

class Pacient
{
	static int ID;
protected:
	int id;
	std::string nume, prenume, adresa;
	int varsta, colesterol, tensiune;
	std::string dataColesterol, dataTensiune;
public:
	Pacient(std::string = "", std::string = "", std::string = "", int = 0, int = 0, int = 0, std::string = "", std::string = "");
	Pacient(const Pacient&);
	Pacient& operator =(const Pacient&);
	virtual ~Pacient();

	virtual void citire() = 0;
	virtual void afisare() = 0;
	virtual std::string getRiscCardiovascular() = 0;

	int getID() const { return id; }
	std::string getNume() const { return nume; }
};