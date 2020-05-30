#include <iostream>
#include <vector>

using namespace std;

class Zbor
{
protected:
    int id, durata, zi, luna, an;
    string oras, destinatie;
public:
    Zbor(int _id = 0, int _durata = 0, int _zi = 0, int _luna = 0, int _an = 0, string _oras = "", string _destinatie = "") :
        id(_id), durata(_durata), zi(_zi), luna(_luna), an(_an), oras(_oras), destinatie(_destinatie) {}
    virtual void citire(istream&);
    virtual void afisare(ostream&);
    friend istream& operator >>(istream&, Zbor&);
    friend ostream& operator <<(ostream&, Zbor&);
    virtual string getType() const { return "zbor"; }

    virtual ~Zbor() {}
};
istream& operator >>(istream& in, Zbor& zbor)
{
    zbor.citire(in);
    return in;
}
ostream& operator <<(ostream& out, Zbor& zbor)
{
    zbor.afisare(out);
    return out;
}


void Zbor::citire(istream& in)
{
    cout << "Introduceti urmatoarele date: \n";
    cout << "Id: ";
    in >> id;
    cout << "Durata: ";
    in >> durata;
    cout << "Data plecarii (zi/luna/an): ";
    in >> zi >> luna >> an;
    cout << "Oras plecare: ";
    in >> oras;
    cout << "Destinatie: ";
    in >> destinatie;
}

void Zbor::afisare(ostream& out)
{
    out << "Date zbor: \n";
    out << "Id: " << id << '\n';
    out << "Durata: " << durata << '\n';
    out << "Data plecarii (zi/luna/an): " << zi << " " << luna << " " << an << '\n';
    out << "Oras plecare: " << oras << '\n';
    out << "Destinatie: " << destinatie << '\n';
}

/////////////

class ZborTemporar : virtual public Zbor
{
protected:
    int perioadaActiva;
public:
    ZborTemporar(int _id = 0, int _durata = 0, int _zi = 0, int _luna = 0, int _an = 0, string _oras = "", string _destinatie = "", int _perioadaActiva = 0) :
        Zbor(_id, _durata, _zi, _luna, _an, _oras, _destinatie), perioadaActiva(_perioadaActiva) {}
    void citire(istream&);
    void afisare(ostream&);
    string getType() const { return "zborTemporar"; }
    virtual ~ZborTemporar() {}
};

void ZborTemporar::citire(istream& in)
{
    Zbor::citire(in);
    cout << "Perioada activa: ";
    in >> perioadaActiva;
}

void ZborTemporar::afisare(ostream& out)
{
    Zbor::afisare(out);
    out << "Perioada activa: " << perioadaActiva << '\n';
}

/////////////

class ZborPromotie : virtual public Zbor
{
protected:
    int discount; //20 (%)
public:
    ZborPromotie(int _id = 0, int _durata = 0, int _zi = 0, int _luna = 0, int _an = 0, string _oras = "", string _destinatie = "", int _discount = 0) :
        Zbor(_id, _durata, _zi, _luna, _an, _oras, _destinatie), discount(_discount) {}
    void citire(istream&);
    void afisare(ostream&);
    string getType() const { return "zborPromotie"; }
    virtual ~ZborPromotie() {}
};


void ZborPromotie::citire(istream& in)
{
    Zbor::citire(in);
    cout << "Discount: ";
    in >> discount;
}

void ZborPromotie::afisare(ostream& out)
{
    Zbor::afisare(out);
    out << "Discount: " << discount << '\n';
}

/////////////

class ZborTemporarPromotie : public ZborTemporar, public ZborPromotie
{
public:
    ZborTemporarPromotie(int _id = 0, int _durata = 0, int _zi = 0, int _luna = 0, int _an = 0, string _oras = "", string _destinatie = "", int _perioadaActiva = 0, int _discount = 0) :
        ZborTemporar(_id, _durata, _zi, _luna, _an, _oras, _destinatie, _perioadaActiva),
        ZborPromotie(_id, _durata, _zi, _luna, _an, _oras, _destinatie, _discount) {}
    void citire(istream&);
    void afisare(ostream&);
    string getType() const { return "zborTemporarPromotie"; }
    ~ZborTemporarPromotie() {}
};

void ZborTemporarPromotie::citire(istream& in)
{
    ZborTemporar::citire(in);
    cout << "Discount: ";
    in >> discount;
}

void ZborTemporarPromotie::afisare(ostream& out)
{
    ZborTemporar::afisare(out);
    out << "Discount: " << discount << '\n';
}

/////////////

class Rute
{
private:
    string plecare, destinatie; //segm zbor
    int nrCurse, pret;
    vector <Zbor*> zboruri;
public:
    Rute(string _plecare = "", string _destinatie = "", int _nrCurse = 0, int _pret = 0) :
        plecare(_plecare), destinatie(_destinatie), nrCurse(_nrCurse), pret(_pret) {}

    void adaugaZbor();
    string getPlecare() const { return plecare; }
    string getDest() const { return destinatie; }
    void afiseazaZboruri();
    bool noDiscount();
    friend istream& operator >>(istream&, Rute&);
    friend ostream& operator <<(ostream&, Rute&);

    ~Rute()
    {
        for (int i = 0; i < zboruri.size(); ++i)
            delete zboruri[i];
        zboruri.clear();
    }
};

istream& operator >>(istream& in, Rute& ruta)
{
    cout << "Plecare: "; in >> ruta.plecare;
    cout << "Sosire: "; in >> ruta.destinatie;
    cout << "Pret: "; in >> ruta.pret;
    return in;
}
ostream& operator <<(ostream& out, Rute& ruta)
{
    out << ruta.plecare << "->" << ruta.destinatie;
    out << "\nPretul: " << ruta.pret << '\n';       
    return out;
}

void Rute::afiseazaZboruri()
{
    for (int i = 0; i < zboruri.size(); ++i) cout << (*zboruri[i]);
}

bool Rute::noDiscount()
{
    for (int i = 0; i < zboruri.size(); ++i)
        if (dynamic_cast<ZborPromotie*>(zboruri[i]) || dynamic_cast<ZborTemporarPromotie*>(zboruri[i])) return 0;
    return 1;
}

void Rute::adaugaZbor()
{
    string s;
    Zbor* z = nullptr;
    cout << "Introdu tip zbor:(zbor, zborTemporar, zborPromotie, zborTemporarPromotie) ";
    cin >> s;

    if (s == "zbor")
        z = new Zbor;
    else if (s == "zborTemporar")
        z = new ZborTemporar;
    else if (s == "zborPromotie")
        z = new ZborPromotie;
    else if (s == "zborTemporarPromotie")
        z = new ZborTemporarPromotie;

    cin >> (*z);
    zboruri.push_back(z);
}


/////////////

class Manager
{
private:
    vector <Rute*> rute;

    static Manager* instance;
    Manager() {}
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

public:
    static Manager* getInstance();

    void adaugaRuta();
    void afiseazaRute();
    void adaugaZbor(string, string);
    void afisareZboruriIntreDate(int, int, int, int, int, int);
    void afiseazaZboruriCurente(int, int, int);
    void afisRuteFaraDiscount();

    ~Manager()
    {
        for (int i = 0; i < rute.size(); ++i)
            delete rute[i];
        rute.clear();
    }
};

Manager* Manager::instance = nullptr;

Manager* Manager::getInstance()
{
    if (instance == nullptr) instance = new Manager();
    return instance;
}

void Manager::adaugaRuta()
{
    Rute* r = new Rute;
    cin >> (*r);
    rute.push_back(r);
}

void Manager::afiseazaRute()
{
    for (int i = 0; i < rute.size(); ++i) cout << (*rute[i]);
}

void Manager::adaugaZbor(string plecare, string dest)
{
    for (int i = 0; i < rute.size(); ++i)
        if (rute[i]->getPlecare() == plecare && rute[i]->getDest() == dest) rute[i]->adaugaZbor();
}

void Manager::afisareZboruriIntreDate(int zi1, int luna1, int an1, int zi2, int luna2, int an2)
{
    for (int i = 0; i < rute.size(); ++i) rute[i]->afiseazaZboruri();
}

void Manager::afiseazaZboruriCurente(int zi, int luna, int an)
{
    for (int i = 0; i < rute.size(); ++i) rute[i]->afiseazaZboruri();
}

void Manager::afisRuteFaraDiscount()
{
    for (int i = 0; i < rute.size(); ++i)
        if (rute[i]->noDiscount()) cout << (*rute[i]);
}

int main()
{
    Manager* M = M->getInstance();
    int var;
    while (1)
    {
        cout << "1.Adauga ruta\n";
        cout << "2.Afiseaza rute\n";
        cout << "3.Adauga cursa pe ruta\n";
        cout << "4.Curse intre 2 date";
        cout << "5.Curse active";
        cout << "6.Rute care nu au avut discount\n";
        cout << "7.Inchide\n";
        cin >> var;
        if (var == 1) M->adaugaRuta();
        else if (var == 2) M->afiseazaRute();
        else if (var == 3)
        {
            string auxPlecare, auxDest;
            cout << "Pe ce ruta? [plecare destinatie]\n";
            cin >> auxPlecare >> auxDest;
            M->adaugaZbor(auxPlecare, auxDest);
        }
        else if (var == 4)
        {
            int z1, luna1, an1, zi2, luna2, an2;
            cout << "Introdu z1 luna1 an1 zi2 luna2 an2: ";
            cin >> z1 >> luna1 >> an1 >> zi2 >> luna2 >> an2;
            M->afisareZboruriIntreDate(z1, luna1, an1, zi2, luna2, an2);
        }
        else if (var == 5)
        {
            int zi, luna, an;
            cout << "Introdu data curenta [zi luna an]: ";
            cin >> zi >> luna >> an;
            M->afiseazaZboruriCurente(zi, luna, an);
        }
        else if (var == 6) M->afisRuteFaraDiscount();
        else if (var == 7) break;
    }
    return 0;
}