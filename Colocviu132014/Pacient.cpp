#include "Pacient.h"

int Pacient::ID = 0;

Pacient::Pacient(std::string _nume, std::string _prenume, std::string _adresa, int _varsta, int _colesterol, int _tensiune, std::string _dataColesterol, std::string _dataTensiune)
	: nume(_nume), prenume(_prenume), adresa(_adresa),
	varsta(_varsta), colesterol(_colesterol), tensiune(_tensiune),
	dataColesterol(_dataColesterol), dataTensiune(_dataTensiune) 
{
	ID++;
	id = ID;
}

Pacient::Pacient(const Pacient& other)
{
	nume = other.nume;
	prenume = other.prenume;
	adresa = other.adresa;
	varsta = other.varsta;
	colesterol = other.colesterol;
	tensiune = other.tensiune;
	dataColesterol = other.dataColesterol;
	dataTensiune = other.dataTensiune;
}

Pacient& Pacient::operator =(const Pacient& other)
{
	if (this == &other) return *this;
	nume = other.nume;
	prenume = other.prenume;
	adresa = other.adresa;
	varsta = other.varsta;
	colesterol = other.colesterol;
	tensiune = other.tensiune;
	dataColesterol = other.dataColesterol;
	dataTensiune = other.dataTensiune;
	return *this;
}

Pacient::~Pacient()
{
	nume.clear();
	prenume.clear();
	adresa.clear();
	dataColesterol.clear();
	dataTensiune.clear();
}

