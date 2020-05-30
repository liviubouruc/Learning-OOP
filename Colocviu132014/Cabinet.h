#pragma once

#include <iostream>
#include <cstring>
#include <vector>
#include "Pacient.h"

class Cabinet
{
	std::string numeDoctor, adresa;
	std::vector <Pacient*> pacienti;
	static Cabinet* instance;
	Cabinet(std::string = "", std::string = "");
public:
	static Cabinet* getInstance(std::string, std::string);
	std::string getDoctorName() const { return numeDoctor; }
	std::string getAdress() const { return adresa; }
	
	void adaugaPacient(std::string);
	void afiseazaPacienti();
	void afiseazaAdultiRiscRidicat();
	void afiseazaCopiiRiscRidicat();
	void afiseazaPacientiNume(std::string);
};