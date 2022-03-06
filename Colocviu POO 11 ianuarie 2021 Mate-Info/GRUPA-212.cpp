/* LUPU GEORGIANA-ANDREEA, GRUPA 212
    COMPILATOR GNU GCC Compiler
    TUTORE DE LABORATOR: EDUARD GABRIEL SZMETEANCA */


#include <iostream>
#include <vector>
#include <string>
using namespace std;


//Vaccin
class Vaccin
{
    float pret;
    float temperatura_depozitare;
    vector<string> substante;
public:
    Vaccin();

    Vaccin(float, float, vector<string>);

    Vaccin(const Vaccin&);

    Vaccin& operator=(const Vaccin&);

    ~Vaccin();

    virtual void afisareSchemaVaccinare() = 0;

    friend std::istream& operator>>(std::istream& in, Vaccin& schimba);
    friend std::ostream& operator<<(std::ostream& out, const Vaccin& schimba);
};

Vaccin::Vaccin()
{
    this->pret = 0;
    this->temperatura_depozitare = 0;
}

Vaccin::Vaccin(float pret, float temperatura_depozitare, vector<string> substante)
{
    this->pret = pret;
    this->temperatura_depozitare = temperatura_depozitare;
    for(int i = 0; i < substante.size(); i++)
    {
        this->substante.push_back(substante[i]);
    }
}

Vaccin::Vaccin(const Vaccin& other)
{
    this->pret = other.pret;
    this->temperatura_depozitare = other.temperatura_depozitare;
    this->substante.clear();
    for(int i = 0; i < other.substante.size(); i++)
    {
        this->substante.push_back(other.substante[i]);
    }
}

Vaccin& Vaccin::operator=(const Vaccin&)
{

}

Vaccin::~Vaccin()
{
    this->pret = 0;
    this->temperatura_depozitare = 0;
    this->substante.clear();
}



std::istream& operator>>(std::istream& in, Vaccin& v)
{
    int nr_substante;
    in >> v.pret >> v.temperatura_depozitare >> nr_substante;
    for(int i = 0; i < nr_substante; i++)
    {
        string substanta;
        in >> substanta;
        v.substante.push_back(substanta);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Vaccin& v)
{
    out << "Pret: " << v.pret << "\nTemperatura de depozitare: " << v.temperatura_depozitare << "\nSubstantele care intra in componenta: ";
    for(int i = 0; i < v.substante.size(); i++)
    {
        out << v.substante[i] << ' ';
    }
    out << endl;
    return out;
}



//VaccinAntigripal
class VaccinAntigripal : public Vaccin
{
    string tulpina;
    bool respecta_recomandarile;
public:
    VaccinAntigripal();

    VaccinAntigripal(float, float, vector<string>, string, bool);

    VaccinAntigripal(const VaccinAntigripal&);

    VaccinAntigripal& operator=(const VaccinAntigripal&);

    ~VaccinAntigripal();

    void afisareSchemaVaccinare();

    friend std::istream& operator>>(std::istream& in, VaccinAntigripal& schimba);
    friend std::ostream& operator<<(std::ostream& out, const VaccinAntigripal& schimba);
};

VaccinAntigripal::VaccinAntigripal()
    : Vaccin()
{
    this->tulpina = "";
    this->respecta_recomandarile = false;
}

VaccinAntigripal::VaccinAntigripal(float pret, float temperatura_depozitare, vector<string> substante, string tulpina, bool respecta_recomandarile)
    : Vaccin(pret, temperatura_depozitare, substante)
{
    this->tulpina = tulpina;
    this->respecta_recomandarile = respecta_recomandarile;
}

VaccinAntigripal::VaccinAntigripal(const VaccinAntigripal& other)
{
    this->tulpina = other.tulpina;
    this->respecta_recomandarile = other.respecta_recomandarile;
}

VaccinAntigripal& VaccinAntigripal::operator=(const VaccinAntigripal&)
{

}

VaccinAntigripal::~VaccinAntigripal()
{
    this->tulpina = "";
    this->respecta_recomandarile = false;
}

void VaccinAntigripal::afisareSchemaVaccinare()
{
    cout << "Adulti: 0.5 ml \nCopii si adolescenti: 0.3 ml \nVaccinul se administreaza odata la 2 ani" << endl << endl;
}

std::istream& operator>>(std::istream& in, VaccinAntigripal& v)
{
    in >> *(Vaccin*)(&v);
    in >> v.tulpina >> v.respecta_recomandarile;
    return in;
}

std::ostream& operator<<(std::ostream& out, const VaccinAntigripal& v)
{
    out << "Vaccin Antigripal\n";
    out << *(Vaccin*)(&v);
    out << "\nTulpina virusului: " << v.tulpina;
    if(v.respecta_recomandarile == true)
    {
        out << "\nRespecta recomandarile OMS.";
    }
    else
    {
        out << "\nNu respecta recomandarile OMS.";
    }
    out << endl;
    return out;
}





//VaccinAntihepatic
class VaccinAntihepatic : public Vaccin
{
    char tip_hepatita;
    string mod_vaccinare;
public:
    VaccinAntihepatic();

    VaccinAntihepatic(float, float, vector<string>, char, string);

    VaccinAntihepatic(const VaccinAntihepatic&);

    VaccinAntihepatic& operator=(const VaccinAntihepatic&);

    ~VaccinAntihepatic();

    void afisareSchemaVaccinare();

    friend std::istream& operator>>(std::istream& in, VaccinAntihepatic& schimba);
    friend std::ostream& operator<<(std::ostream& out, const VaccinAntihepatic& schimba);
};

VaccinAntihepatic::VaccinAntihepatic()
    : Vaccin()
{
    this->tip_hepatita = '-';
    this->mod_vaccinare = "";
}

VaccinAntihepatic::VaccinAntihepatic(float pret, float temperatura_depozitare, vector<string> substante, char tip_hepatita, string mod_vaccinare)
    : Vaccin(pret, temperatura_depozitare, substante)
{
    this->tip_hepatita = tip_hepatita;
    this->mod_vaccinare = mod_vaccinare;
}

VaccinAntihepatic::VaccinAntihepatic(const VaccinAntihepatic& other)
{
    this->tip_hepatita = other.tip_hepatita;
    this->mod_vaccinare = other.mod_vaccinare;
}

VaccinAntihepatic& VaccinAntihepatic::operator=(const VaccinAntihepatic&)
{

}

VaccinAntihepatic::~VaccinAntihepatic()
{
    this->tip_hepatita = '-';
    this->mod_vaccinare = "";
}

void VaccinAntihepatic::afisareSchemaVaccinare()
{
    if(this->tip_hepatita == 'A' || this->tip_hepatita == 'B')
        cout << "Copii sub 1 an: 2 injectari pe luna, iar a treia injectare dupa 6 luni \n Adulti: conform schemei recomandate de medic";
    else if(this->tip_hepatita == 'C')
        cout << "Vaccinul se administreaza doar la recomandarea medicului";
    else
        cout << "Nu este specificat tipul hepatitei.";
    cout << endl << endl;
}

std::istream& operator>>(std::istream& in, VaccinAntihepatic& v)
{
    in >> *(Vaccin*)(&v);
    in >> v.tip_hepatita >> v.mod_vaccinare;
    return in;
}

std::ostream& operator<<(std::ostream& out, const VaccinAntihepatic& v)
{
    out << "Vaccin Antihepatic\n";
    out << *(Vaccin*)(&v);
    out << "\nTipul de hepatita: " << v.tip_hepatita << "\nModul de vaccinare: " << v.mod_vaccinare;
    out << endl;
    return out;
}




//VaccinAntiSarsCov2
class VaccinAntiSarsCov2 : public Vaccin
{
    vector<string> reactii_adverse;
    float rata_eficienta;
    vector<string> lista_medicamente_contraindicate;
public:
    VaccinAntiSarsCov2();

    VaccinAntiSarsCov2(float, float, vector<string>, vector<string>, float, vector<string>);

    VaccinAntiSarsCov2(const VaccinAntiSarsCov2&);

    VaccinAntiSarsCov2& operator=(const VaccinAntiSarsCov2&);

    ~VaccinAntiSarsCov2();

    void afisareSchemaVaccinare();

    friend std::istream& operator>>(std::istream& in, VaccinAntiSarsCov2& schimba);
    friend std::ostream& operator<<(std::ostream& out, const VaccinAntiSarsCov2& schimba);
};

VaccinAntiSarsCov2::VaccinAntiSarsCov2()
    : Vaccin()
{
    rata_eficienta = 0;
}

VaccinAntiSarsCov2::VaccinAntiSarsCov2(float pret, float temperatura_depozitare, vector<string> substante, vector<string> reactii_adverse, float rata_eficienta, vector<string> lista_medicamente_contraindicate)
    : Vaccin(pret, temperatura_depozitare, substante)
{
    for(int i = 0; i < reactii_adverse.size(); i++)
    {
        this->reactii_adverse.push_back(reactii_adverse[i]);
    }
    this->rata_eficienta = rata_eficienta;
    for(int i = 0; i < lista_medicamente_contraindicate.size(); i++)
    {
        this->lista_medicamente_contraindicate.push_back(lista_medicamente_contraindicate[i]);
    }
}

VaccinAntiSarsCov2::VaccinAntiSarsCov2(const VaccinAntiSarsCov2& other)
{
    for(int i = 0; i < other.reactii_adverse.size(); i++)
    {
        this->reactii_adverse.push_back(other.reactii_adverse[i]);
    }
    this->rata_eficienta = other.rata_eficienta;
    for(int i = 0; i < other.lista_medicamente_contraindicate.size(); i++)
    {
        this->lista_medicamente_contraindicate.push_back(other.lista_medicamente_contraindicate[i]);
    }
}

VaccinAntiSarsCov2& VaccinAntiSarsCov2::operator=(const VaccinAntiSarsCov2&)
{

}

VaccinAntiSarsCov2::~VaccinAntiSarsCov2()
{
    this->reactii_adverse.clear();
    this->rata_eficienta = 0;
    this->lista_medicamente_contraindicate.clear();
}

void VaccinAntiSarsCov2::afisareSchemaVaccinare()
{
    cout << "Pentru cei cu varsta peste 16 ani: 2 doze la 21 zile" << endl << endl;
}

std::istream& operator>>(std::istream& in, VaccinAntiSarsCov2& v)
{
    int nr_reactii_adverse, nr_medicamente_contraindicate;
    in >> *(Vaccin*)(&v);
    in >> nr_reactii_adverse;
    for(int i = 0; i < nr_reactii_adverse; i++)
    {
        string reactie_adversa;
        in >> reactie_adversa;
        v.reactii_adverse.push_back(reactie_adversa);
    }
    in >> v.rata_eficienta;
    in >> nr_medicamente_contraindicate;
    for(int i = 0; i < nr_medicamente_contraindicate; i++)
    {
        string medicament_contraindicat;
        in >> medicament_contraindicat;
        v.lista_medicamente_contraindicate.push_back(medicament_contraindicat);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const VaccinAntiSarsCov2& v)
{
    out << "Vaccin Anti Sars-Cov-2\n";
    out << *(Vaccin*)(&v);
    out << "\nEficienta: " << v.rata_eficienta;
    out << "\nReactiile adverse: ";
    for(int i = 0; i < v.reactii_adverse.size(); i++)
    {
        out << v.reactii_adverse[i] << " ";
    }
    out << "\nMedicamente contraindicate in primele 6 luni: ";
    for(int i = 0; i < v.lista_medicamente_contraindicate.size(); i++)
    {
        out << v.lista_medicamente_contraindicate[i] << " ";
    }
    out << endl;
    return out;
}



//Comanda
class Comanda
{
    static int nr_comenzi;
    int id_comanda;
    string data;
    string nume_client;
    Vaccin* vaccin_comandat;
    int cantitate;
public:
    Comanda();

    Comanda(string, string, string, int);

    Comanda(const Comanda&);

    Comanda& operator=(const Comanda&);

    ~Comanda();

    friend std::istream& operator>>(std::istream& in, Comanda& schimba);
    friend std::ostream& operator<<(std::ostream& out, const Comanda& schimba);
};

Comanda::Comanda()
{
    Comanda::nr_comenzi++;
    this->id_comanda = Comanda::nr_comenzi;
    this->data = "00-00-0000";
    this->nume_client = "";
    this->vaccin_comandat = nullptr;
    this->cantitate = 0;
}

Comanda::Comanda(string data, string nume_client, string tip_vaccin, int cantitate)
{
    Comanda::nr_comenzi++;
    this->id_comanda = Comanda::nr_comenzi;
    this->data = data;
    this->nume_client = nume_client;
    if(tip_vaccin == "Antigripal")
    {
        vaccin_comandat = new VaccinAntigripal;
    }
    else if(tip_vaccin == "Antihepatic")
    {
        vaccin_comandat = new VaccinAntihepatic;
    }
    else if(tip_vaccin == "AntiSarsCov2")
    {
        vaccin_comandat = new VaccinAntiSarsCov2;
    }
    this->cantitate = cantitate;
}

Comanda::Comanda(const Comanda& other)
{
    Comanda::nr_comenzi ++;
    this->id_comanda = Comanda::nr_comenzi;
    this->data = other.data;
    this->nume_client = other.nume_client;
    if(vaccin_comandat != nullptr)
        delete this->vaccin_comandat;
    if(VaccinAntigripal* p = dynamic_cast<VaccinAntigripal*>(other.vaccin_comandat))
        this->vaccin_comandat = new VaccinAntigripal(*p);

    else if(VaccinAntihepatic* p = dynamic_cast<VaccinAntihepatic*>(other.vaccin_comandat))
        this->vaccin_comandat = new VaccinAntihepatic(*p);

    else if(VaccinAntiSarsCov2* p = dynamic_cast<VaccinAntiSarsCov2*>(other.vaccin_comandat))
        this->vaccin_comandat = new VaccinAntiSarsCov2(*p);

    this->cantitate = other.cantitate;
}

Comanda& Comanda::operator=(const Comanda&)
{

}

Comanda::~Comanda()
{
    if(vaccin_comandat != nullptr)
        delete vaccin_comandat;

    this->data = "00-00-0000";
    this->nume_client = "";
    this->cantitate = 0;
}

std::istream& operator>>(std::istream& in, Comanda& c)
{
    return in;
}

std::ostream& operator<<(std::ostream& out, const Comanda& c)
{
    out << "Id comanda: " << c.id_comanda << "\nData comenzii: " << c.data << "\nClientul " << c.nume_client;
    out << " a comandat " << c.cantitate << " vaccinuri de tip: ";
    if(VaccinAntigripal* p = dynamic_cast<VaccinAntigripal*>(c.vaccin_comandat))
        out << "VaccinAntigripal";

    else if(VaccinAntihepatic* p = dynamic_cast<VaccinAntihepatic*>(c.vaccin_comandat))
        out << "VaccinAntihepatic";

    else if(VaccinAntiSarsCov2* p = dynamic_cast<VaccinAntiSarsCov2*>(c.vaccin_comandat))
        out << "VaccinAntiSarsCov2";
    else
        out << "necunoscut";
    return out;
}



class ListaComenzi
{
    vector<Comanda> comenzi;
public:
    ListaComenzi& operator+(const Comanda&);
    friend std::ostream& operator<<(std::ostream& out, const ListaComenzi& l);
    Comanda& operator[](int);
};


ListaComenzi& ListaComenzi::operator+(const Comanda& c)
{
    comenzi.push_back(c);
    return *this;
}

std::ostream& operator<<(std::ostream& out, const ListaComenzi& schimba)
{

    return out;
}

Comanda& ListaComenzi::operator[](int index)
{
    return comenzi[index];
}


void meniu()
{
	cout<< "---------------------" << endl;
	cout << "1. Adauga un nou vaccin" << endl;
	cout << "2. Afiseaza toate vaccinurile" << endl;
	cout << "3. Afiseaza numele producatorilor pentru toate vaccinurile" << endl;
	cout << "4. Adauga o comanda noua" << endl;
	cout << "5. Afiseaza toate comenzile " << endl;
	cout << "6. Valoarea comenzilor dintr-o zi " << endl;
	cout << "7. Afisati schema de vaccinare pentru un vaccin" << endl;
	cout << "8. Exporta comenzile intr-un .txt" << endl;
	cout << "9. Iesire " << endl;
	cout << "---------------------" << endl;
}

int Comanda::nr_comenzi = 0;

int main()
{
    int optiune;
    vector<Vaccin*> vaccinuri;
    ListaComenzi lista_comenzi;
    do
    {
        meniu();
        cout << "Optiune: ";
        cin >> optiune;
        if(optiune == 1)
        {
            string tip_vaccin;
            cout << "Tipul vaccinului (Antigripal / Antihepatic / AntiSarsCov2): ";
            cin >> tip_vaccin;
            if(tip_vaccin == "Antigripal")
            {
                VaccinAntigripal vaccin;
                cin >> vaccin;
                vaccinuri.push_back(new VaccinAntigripal(vaccin));
            }
            else if (tip_vaccin == "Antihepatic")
            {
                VaccinAntihepatic vaccin;
                cin >> vaccin;
                vaccinuri.push_back(new VaccinAntihepatic(vaccin));
            }
            else if (tip_vaccin == "AntiSarsCov2")
            {
                VaccinAntiSarsCov2 vaccin;
                cin >> vaccin;
                vaccinuri.push_back(new VaccinAntiSarsCov2(vaccin));
            }
            else
                cout << "Introduceti corect tipul vaccinului";
        }
        else if (optiune == 2)
        {
            for(int i = 0; i < vaccinuri.size(); i++)
            {
                if(VaccinAntigripal* p = dynamic_cast<VaccinAntigripal*>(vaccinuri[i]))
                {
                    cout << *(VaccinAntigripal*)(vaccinuri[i]);
                }
                else if(VaccinAntihepatic* p = dynamic_cast<VaccinAntihepatic*>(vaccinuri[i]))
                {
                    cout << *(VaccinAntihepatic*)(vaccinuri[i]);
                }
                else if(VaccinAntiSarsCov2* p = dynamic_cast<VaccinAntiSarsCov2*>(vaccinuri[i]))
                {
                    cout << *(VaccinAntiSarsCov2*)(vaccinuri[i]);
                }
            }
        }
        else if (optiune == 3)
        {

        }
        else if (optiune == 4)
        {
            Comanda temp_comanda;
            cin >> temp_comanda;
            lista_comenzi = lista_comenzi + temp_comanda;
        }
        else if (optiune == 5)
        {

        }
        else if (optiune == 6)
        {

        }
        else if (optiune == 7)
        {

        }
        else if (optiune == 8)
        {

        }

    } while (optiune != 9);

}
