#include "AdultSub40.h"
#include <iostream>

AdultSub40::AdultSub40(std::string _nume, std::string _prenume, std::string _adresa, int _varsta, int _colesterol, int _tensiune, std::string _dataColesterol, std::string _dataTensiune) : Pacient(_nume, _prenume, _adresa, _varsta, _colesterol, _tensiune, _dataColesterol, _dataTensiune) {}

AdultSub40::AdultSub40(const AdultSub40& other) : Pacient(other) {}

AdultSub40& AdultSub40::operator =(const AdultSub40& other)
{
	if (this == &other) return *this;
	Pacient::operator =(other);
	return *this;
}

AdultSub40::~AdultSub40() {}

void AdultSub40::citire()
{
	std::cin >> nume >> prenume >> adresa;
	std::cin >> varsta >> colesterol >> tensiune;
	std::cin >> dataColesterol >> dataTensiune;
}

std::string AdultSub40::getRiscCardiovascular()
{
	if (colesterol > 240 || tensiune > 139) return "DA";
	return "NU";
}

void AdultSub40::afisare()
{
	std::cout << nume << " " << prenume << ": Risc cardiovascular - " << this->getRiscCardiovascular() << "; Colesterol (" << dataColesterol << "): ";
	std::cout << colesterol << " mg/dl; TA (" << dataTensiune << "): " << tensiune << ";";
	std::cout << '\n';
}