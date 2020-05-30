#include "Copil.h"
#include <iostream>

Copil::Copil(std::string _nume, std::string _prenume, std::string _adresa, int _varsta, int _colesterol, int _tensiune, std::string _dataColesterol, std::string _dataTensiune, bool _antecedente, std::string _numeMama, std::string _numeTata, double _proteinaC, std::string _dataProteinaC) : Pacient(_nume, _prenume, _adresa, _varsta, _colesterol, _tensiune, _dataColesterol, _dataTensiune), antecedente(_antecedente), numeMama(_numeMama), numeTata(_numeTata), proteinaC(_proteinaC), dataProteinaC(_dataProteinaC) {}

Copil::Copil(const Copil& other) : Pacient(other)
{
	antecedente = other.antecedente;
	numeMama = other.numeMama;
	numeTata = other.numeTata;
	proteinaC = other.proteinaC;
	dataProteinaC = other.dataProteinaC;
}

Copil& Copil::operator =(const Copil& other)
{
	if (this == &other) return *this;
	Pacient::operator =(other);
	antecedente = other.antecedente;
	numeMama = other.numeMama;
	numeTata = other.numeTata;
	proteinaC = other.proteinaC;
	dataProteinaC = other.dataProteinaC;
	return *this;
}

Copil::~Copil() 
{
	numeMama.clear();
	numeTata.clear();
	dataProteinaC.clear();
}

void Copil::citire()
{
	std::cin >> nume >> prenume >> adresa;
	std::cin >> varsta >> colesterol >> tensiune;
	std::cin >> dataColesterol >> dataTensiune;
	std::cin >> antecedente >> numeMama >> numeTata;
	std::cin >> proteinaC >> dataProteinaC;
}

std::string Copil::getRiscCardiovascular()
{
	int simptome = 0;
	if (colesterol > 240 || tensiune > 139) simptome++;
	if (antecedente) simptome++;

	if (simptome == 2) return "RIDICAT";
	if (simptome == 1) return "DA";
	return "NU";
}

void Copil::afisare()
{
	std::cout << nume << " " << prenume << ": Risc cardiovascular - " << this->getRiscCardiovascular() << "; Colesterol (" << dataColesterol << "): ";
	std::cout << colesterol << " mg/dl; TA (" << dataTensiune << "): " << tensiune << "; ProteinaC C reactiva (" << dataProteinaC << "): ";
	std::cout << proteinaC << " mg/dl; Antecedente familie: " << (antecedente == 1 ? "da;" : "nu;");
	std::cout << '\n';
}