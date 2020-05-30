#include "AdultPeste40.h"
#include <iostream>

AdultPeste40::AdultPeste40(std::string _nume, std::string _prenume, std::string _adresa, int _varsta, int _colesterol, int _tensiune, std::string _dataColesterol, std::string _dataTensiune, bool _fumator, std::string _sedentarism) : Pacient(_nume, _prenume, _adresa, _varsta, _colesterol, _tensiune, _dataColesterol, _dataTensiune), fumator(_fumator), sedentarism(_sedentarism) {}

AdultPeste40::AdultPeste40(const AdultPeste40& other) : Pacient(other) 
{
	fumator = other.fumator;
	sedentarism = other.sedentarism;
}

AdultPeste40& AdultPeste40::operator =(const AdultPeste40& other)
{
	if (this == &other) return *this;
	Pacient::operator =(other);
	fumator = other.fumator;
	sedentarism = other.sedentarism;
	return *this;
}

AdultPeste40::~AdultPeste40() { sedentarism.clear(); }

void AdultPeste40::citire()
{
	std::cin >> nume >> prenume >> adresa;
	std::cin >> varsta >> colesterol >> tensiune;
	std::cin >> dataColesterol >> dataTensiune;
	std::cin >> fumator >> sedentarism;
}

std::string AdultPeste40::getRiscCardiovascular()
{
	int simptome = 0;
	if (colesterol > 240 || tensiune > 139) simptome++;
	if (fumator == 1 && sedentarism == "ridicat") simptome++;
	
	if (simptome == 2) return "RIDICAT";
	if (simptome == 1) return "DA";
	return "NU";
}

void AdultPeste40::afisare()
{
	std::cout << nume << " " << prenume << ": Risc cardiovascular - " << this->getRiscCardiovascular() << "; Colesterol (" << dataColesterol << "): ";
	std::cout << colesterol << " mg/dl; TA (" << dataTensiune << "): " << tensiune << "; Fumator: ";
	std::cout << (fumator == 1 ? "da; Sedentarism: " : "nu; Sedentarism: ") << sedentarism;
	std::cout << '\n';
}