#include "Cabinet.h"
#include "Pacient.h"
#include "AdultSub40.h"
#include "AdultPeste40.h"
#include "Copil.h"

Cabinet* Cabinet::instance = nullptr;

Cabinet::Cabinet(std::string _numeDoctor, std::string _adresa) : numeDoctor(_numeDoctor), adresa(_adresa) {}

Cabinet* Cabinet::getInstance(std::string _numeDoctor, std::string _adresa)
{
	if (instance == nullptr) instance = new Cabinet(_numeDoctor, _adresa);
	return instance;
}

void Cabinet::adaugaPacient(std::string tip)
{
	Pacient* p = nullptr;
	if (tip == "adultsub40") p = new AdultSub40;
	if (tip == "adultpeste40") p = new AdultPeste40;
	if (tip == "copil") p = new Copil();
	p->citire();
	pacienti.push_back(p);
}

void Cabinet::afiseazaPacienti() 
{
	std::cout << "Adulti\n";
	std::cout << "Adulti sub 40 ani:\n";
	for (int i = 0; i < pacienti.size(); i++)
		if (dynamic_cast<AdultSub40*>(pacienti[i])) pacienti[i]->afisare();

	std::cout << "Adulti peste 40 ani:\n";
	for (int i = 0; i < pacienti.size(); i++)
		if (dynamic_cast<AdultPeste40*>(pacienti[i])) pacienti[i]->afisare();

	std::cout << "Copii:\n";
	for (int i = 0; i < pacienti.size(); i++)
		if (dynamic_cast<Copil*>(pacienti[i])) pacienti[i]->afisare();
}

void Cabinet::afiseazaAdultiRiscRidicat() {
	std::cout << "Adulti peste 40 ani cu risc ridicat:\n";
	for (int i = 0; i < pacienti.size(); i++) {
		if (dynamic_cast<AdultPeste40*>(pacienti[i]) && pacienti[i]->getRiscCardiovascular() == "RIDICAT") pacienti[i]->afisare();
	}
}

void Cabinet::afiseazaCopiiRiscRidicat() {
	std::cout << "Copii cu risc ridicat:\n";
	for (int i = 0; i < pacienti.size(); i++)
		if (dynamic_cast<Copil*>(pacienti[i]) && (pacienti[i]->getRiscCardiovascular() == "RIDICAT" || pacienti[i]->getRiscCardiovascular() == "DA")) pacienti[i]->afisare();
}

void Cabinet::afiseazaPacientiNume(std::string nume) {
	for (int i = 0; i < pacienti.size(); i++) {
		if (pacienti[i]->getNume() == nume) pacienti[i]->afisare();
	}
}