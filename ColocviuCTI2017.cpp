#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class I_IO // luata din laborat <3
{
public:
    virtual void citire(istream&) = 0;
    virtual void afisare(ostream&) = 0;

    friend istream& operator >>(istream& in, I_IO& ob)
    {
        ob.citire(in);
        return in;
    }
    friend ostream& operator <<(ostream& out, I_IO& ob)
    {
        ob.afisare(out);
        return out;
    }

    virtual ~I_IO() {}
};

class Contract : public I_IO
{
protected:
    string nume_client;
public:
    Contract(string _n_c = "") : nume_client(_n_c) {}

    void citire(istream& in)
    {
        cout << "Nume client: "; in >> nume_client;
    }
    void afisare(ostream& out)
    {
        cout << "Nume client: " << nume_client;
        out << '\n';
    }

    virtual ~Contract() {}
};

class ContractInchiriere : public Contract
{
    int luna1, an1, luna2, an2;
public:
    ContractInchiriere(string _n_c = "", int _l1 = 0, int _a1 = 0, int _l2 = 0, int _a2 = 0)
        : Contract(_n_c), luna1(_l1), an1(_a1), luna2(_l2), an2(_a2) {}

    void citire(istream& in)
    {
        Contract::citire(in);
        cout << "Luna an inceput "; in >> luna1 >> an1;
        cout << "\nLuna an sf "; in >> luna2 >> an2;
    }
    void afisare(ostream& out)
    {
        Contract::afisare(out);
        out << "Luna an inceput " << luna1 << an1;
        out << "\nLuna an sf " << luna2 << an2;
        out << '\n';
    }
};

class ContractVC : public Contract
{
    int luna1, an1, luna2, an2;
public:
    ContractVC(string _n_c = "", int _l1 = 0, int _a1 = 0, int _l2 = 0, int _a2 = 0)
        : Contract(_n_c), luna1(_l1), an1(_a1), luna2(_l2), an2(_a2) {}

    void citire(istream& in)
    {
        Contract::citire(in);
        cout << "Luna an tranzactie "; in >> luna1 >> an1;
        cout << "\nLuna an achitare "; in >> luna2 >> an2;
    }
    void afisare(ostream& out)
    {
        Contract::afisare(out);
        out << "Luna an tranzactie " << luna1 << an1;
        out << "\nLuna an achitare " << luna2 << an2;
        out << '\n';
    }
};

class Proprietate : public I_IO
{
protected:
    static int ID;

    vector <Contract*> contracte;
    int id;
    string adresa;
    int supr;
    double chirie;
public:
    Proprietate(string _ad = "", int _supr = 0, double _chirie = 0) : adresa(_ad), supr(_supr), chirie(_chirie)
    {
        id = ID;
        ID++;
    }
    Proprietate(const Proprietate& pr) : adresa(pr.adresa), supr(pr.supr), chirie(pr.chirie)
    {
        for (auto ptr : pr.contracte)
            addContract(ptr);
    }
    Proprietate& operator =(const Proprietate& proprietate)
    {
        if (this == &proprietate)
            return *this;

        for (int i = 0; i < contracte.size(); ++i)
            delete contracte[i];
        contracte.clear();

        adresa = proprietate.adresa;
        chirie = proprietate.chirie;
        supr = proprietate.supr;

        for (auto ptr : proprietate.contracte)
            addContract(ptr);
        return *this;
    }

    void citire(istream&);
    void afisare(ostream&);
    void citesteContract();
    void afisContracte();
    bool libera(int, int) { return 0; }
    bool vanduta(int, int) { return 0; }
    bool inchiriata(int, int) { return 0; }
    double getSuma(int, int);

    void addContract(Contract* c)
    {
        if (ContractInchiriere* co = dynamic_cast<ContractInchiriere*>(c))
            contracte.push_back(new ContractInchiriere(*co));
        else if (ContractVC* co = dynamic_cast<ContractVC*>(c))
            contracte.push_back(new ContractVC(*co));
    }

    virtual ~Proprietate()
    {
        for (int i = 0; i < contracte.size(); ++i)
            delete contracte[i];
        contracte.clear();
    }
};
int Proprietate::ID = 0;

void Proprietate::citire(istream& in)
{
    cout << "Adresa: "; in >> adresa;
    cout << "Suprafata: "; in >> supr;
    cout << "Chirie: "; in >> chirie;
}
void Proprietate::afisare(ostream& out)
{
    out << "Adresa " << adresa;
    out << "\nSupr " << supr;
    out << "\nChirie mp " << chirie;
    out << '\n';
}

void Proprietate::citesteContract()
{
    Contract* c = nullptr;
    string tip;
    cout << "Tipul contractului: [inchiriere vc] "; cin >> tip;
    if (tip == "inchiriere") c = new ContractInchiriere;
    else if (tip == "vc") c = new ContractVC;
    cin >> (*c);
    contracte.push_back(c);
}
void Proprietate::afisContracte()
{
    cout << "Contracte de inchiriere:\n";
    for (int i = 0; i < contracte.size(); ++i)
        if (dynamic_cast<ContractInchiriere*>(contracte[i]))
            cout << (*contracte[i]);
    cout << "Contracte de vanzare-cumparare:\n";
    for (int i = 0; i < contracte.size(); ++i)
        if (dynamic_cast<ContractVC*>(contracte[i]))
            cout << (*contracte[i]);
}


double Proprietate::getSuma(int luna, int an)
{
    return 0;
}

class Casa : public Proprietate
{
    int niveluri, supr_curte;
public:
    Casa(string _ad = "", int _supr = 0, double _chirie = 0, int _niv = 0, int _s_c = 0)
        : Proprietate(_ad, _supr, _chirie), niveluri(_niv), supr_curte(_s_c) {}
    Casa(const Casa& casa) : Proprietate(casa), niveluri(casa.niveluri), supr_curte(casa.supr_curte) {}
    void citire(istream&);
    void afisare(ostream&);
};

void Casa::citire(istream& in)
{
    Proprietate::citire(in);
    cout << "Niveluri: "; in >> niveluri;
    cout << "Supr curte: "; in >> supr_curte;
}
void Casa::afisare(ostream& out)
{
    Proprietate::afisare(out);
    out << "Niveluri " << niveluri << " Supr curte " << supr_curte;
    out << '\n';
}

class Apartament : public Proprietate
{
    int etaj, nr_camere;
public:
    Apartament(string _ad = "", int _supr = 0, double _chirie = 0, int _etaj = 0, int _nr_c = 0)
        : Proprietate(_ad, _supr, _chirie), etaj(_etaj), nr_camere(_nr_c) {}
    Apartament(const Apartament& ap) : Proprietate(ap), etaj(ap.etaj), nr_camere(ap.nr_camere) {}
    void citire(istream&);
    void afisare(ostream&);
};

void Apartament::citire(istream& in)
{
    Proprietate::citire(in);
    cout << "Etaj: "; in >> etaj;
    cout << "Nr camere: "; in >> nr_camere;
}
void Apartament::afisare(ostream& out)
{
    Proprietate::afisare(out);
    out << "Etaj " << etaj << " Camere " << nr_camere;
    out << '\n';
}

class Manager
{
    vector <Proprietate*> proprietati;

    static Manager* instance;
    Manager() {}
public:
    static Manager* getInstance() {
        if (instance == nullptr) return new Manager();
        return instance;
    }

    void citesteProp(string);
    void citesteContract();
    void afisare();
    void afisPropData(int, int);
    double getLei(int, int);

    ~Manager()
    {
        for (int i = 0; i < proprietati.size(); ++i)
            delete proprietati[i];
        proprietati.clear();
    }
};
Manager* Manager::instance = nullptr;

void Manager::citesteProp(string tip)
{
    Proprietate* p = nullptr;
    try {
        if (tip == "casa") p = new Casa;
        else if (tip == "apartament") p = new Apartament;
        else throw runtime_error("Tip invalid!\n");
    }
    catch (const exception& ex) { cout << ex.what(); return; }
    cin >> (*p);
    proprietati.push_back(p);
}

void Manager::citesteContract()
{
    int idC;
    try {
        cout << "Id-ul case contractului: "; cin >> idC;
        if (idC >= proprietati.size()) throw runtime_error("ID invalid!\n");
        proprietati[idC]->citesteContract();
    }
    catch (const exception& ex) { cout << ex.what(); }
}

void Manager::afisare()
{
    cout << "Case:\n";
    for (int i = 0; i < proprietati.size(); ++i)
        if (dynamic_cast<Casa*>(proprietati[i]))
        {
            cout << (*proprietati[i]);
            cout << "Contractele proprietatii:\n";
            proprietati[i]->afisContracte();
        }
    cout << "Apartamente:\n";
    for (int i = 0; i < proprietati.size(); ++i)
        if (dynamic_cast<Apartament*>(proprietati[i]))
        {
            cout << (*proprietati[i]);
            cout << "Contractele proprietatii:\n";
            proprietati[i]->afisContracte();
        }
}

void Manager::afisPropData(int luna, int an)
{
    cout << "Proprietati libere\n";
    for (int i = 0; i < proprietati.size(); ++i)
        if (proprietati[i]->libera(luna, an)) cout << (*proprietati[i]);
    cout << "Proprietati inchiriate\n";
    for (int i = 0; i < proprietati.size(); ++i)
        if (proprietati[i]->inchiriata(luna, an)) cout << (*proprietati[i]);
    cout << "Proprietati vandute\n";
    for (int i = 0; i < proprietati.size(); ++i)
        if (proprietati[i]->vanduta(luna, an)) cout << (*proprietati[i]);
}

double Manager::getLei(int luna, int an)
{
    double sum = 0;
    for (int i = 0; i < proprietati.size(); ++i)
        sum += proprietati[i]->getSuma(luna, an);
    return sum;
}

int main()
{
    int var;
    Manager* M = M->getInstance();
    while (1)
    {
        cout << "1.Adauga n proprietati\n";
        cout << "2.Adauga n contracte\n";
        cout << "3.Proprietati si contracte grupate\n";
        cout << "4.Proprietati grupate dupa situatie\n";
        cout << "5.Suma totala\n";
        cout << "6.Inchide\n";
        cin >> var; cout << '\n';
        if (var == 1)
        {
            int n;
            cout << "Introdu numarul de proprietati: ";
            cin >> n;
            cout << "Pentru fiecare proprietate introdu tipul, [casa apartament]";
            while (n--)
            {
                string tip_prop;
                cin >> tip_prop;
                M->citesteProp(tip_prop);
            }
        }
        else if (var == 2)
        {
            int n;
            cout << "Introdu nr de contracte: ";
            cin >> n;
            while (n--) M->citesteContract();
        }
        else if (var == 3) M->afisare();
        else if (var == 4)
        {
            int luna, an;
            cout << "Introdu data [luna an] ";
            cin >> luna >> an;
            M->afisPropData(luna, an);
        }
        else if (var == 5)
        {
            int luna, an;
            cout << "Introdu data [luna an] ";
            cin >> luna >> an;
            cout << M->getLei(luna, an) << '\n';
        }
        else break;
    }
    return 0;
}