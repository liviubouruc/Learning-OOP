#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class I_IO // luata din laborator <3
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

class Statie : public I_IO
{
protected:
    static int ID;
    int id;
    vector <Mijloace*> mijloace;
    string adresa;
public:
    Statie(string _ad = "", int _supr = 0, double _chirie = 0) : adresa(_ad), supr(_supr), chirie(_chirie)
    {
        id = ID;
        ID++;
    }
    Statie(const Statie& s) : adresa(s.adresa)
    {
        for (auto ptr : s.mijloace)
            addStatie(ptr);
    }
    Statie& operator =(const Statie& statie)
    {
        if (this == &statie)
            return *this;

        for (int i = 0; i < mijloace.size(); ++i)
            delete mijloace[i];
        mijloace.clear();

        adresa = statie.adresa;

        for (auto ptr : statie.mijloace)
            addStatie(ptr);
        return *this;
    }

    void citire(istream&);
    void afisare(ostream&);
    void addStatie(Contract* c)
    {
        if (ContractInchiriere* co = dynamic_cast<ContractInchiriere*>(c))
            mijloace.push_back(new ContractInchiriere(*co));
        else if (ContractVC* co = dynamic_cast<ContractVC*>(c))
            mijloace.push_back(new ContractVC(*co));
    }

    virtual ~Statie()
    {
        for (int i = 0; i < mijloace.size(); ++i)
            delete mijloace[i];
        mijloace.clear();
    }
};
int Statie::ID = 0;

void Statie::citire(istream& in)
{
    cout << "Adresa: "; in >> adresa;
}
void Statie::afisare(ostream& out)
{
    out << "Adresa " << adresa;
    out << '\n';
}

class StatieU
{

};

class Manager
{
    vector <Statie*> statii;

    static Manager* instance;
    Manager() {}
public:
    static Manager* getInstance() {
        if (instance == nullptr) return new Manager();
        return instance;
    }

    void adaugaStatie(string);

    ~Manager()
    {
        for (int i = 0; i < statii.size(); ++i)
            delete statii[i];
        statii.clear();
    }
};
Manager* Manager::instance = nullptr;

void Manager::adaugaStatie(string tip)
{
    Statie* s = nullptr;
    try {
        if (tip == "urban") s = new StatieU;
        else if (tip == "extrau") s = new StatieEU;
        else throw runtime_error("Tip invalid!\n");
    }
    catch (const exception& ex) { cout << ex.what(); return; }
    cin >> (*s);
    statii.push_back(s);
}

int main()
{
    int var;
    Manager* M = M->getInstance();
    while (1)
    {
        cout << "1.Adauga statie\n";
        cout << "2.Afisare statie\n";
        cout << "3.Afisare toate statii\n";
        cout << "4.Pret\n";
        cout << "5.Inchide\n";
        cin >> var;
        if (var == 1)
        {
            string tip;
            cout << "Tipul statiei: "; cin >> tip;
            M->adaugaStatie(tip);
        }
        else break;
    }
    return 0;
}