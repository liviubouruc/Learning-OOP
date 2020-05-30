#include <iostream>
#include <vector>

using namespace std;

class I_IO
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
};

class Abonament : public I_IO
{
protected:
    static int ID;
    int id;
    double pret;
    int nr_minute, nr_sms;
public:
    Abonament(double _pret = 0, int _nr_m = 0, int _nr_sms = 0) : pret(_pret), nr_minute(_nr_m), nr_sms(_nr_sms) 
    {
        ID++;
        id = ID;
    }

    void citire(istream&);
    void afisare(ostream&);
};
int Abonament::ID = 0;

void Abonament::citire(istream& in)
{
    cout << "Pretul: "; in >> pret;
    cout << "Nr minute: "; in >> nr_minute;
    cout << "Nr sms: "; in >> nr_sms;
}
void Abonament::afisare(ostream& out)
{
    out << "id: " << id;
    out << "\nPret: " << pret;
    out << "\nNr minute Nr SMS: " << nr_minute << " " << nr_sms;
    out << '\n';
}

class AbonamentVedere : public Abonament
{
public:
    AbonamentVedere(double _pret = 0, int _nr_m = 0, int _nr_sms = 0) : Abonament(_pret/2.5, 3*_nr_m, 0) {}
    void citire(istream& in) { Abonament::citire(in); }
    void afisare(ostream& out) { Abonament::afisare(out); }
};

class AbonamentAuz : public Abonament
{
public:
    AbonamentAuz(double _pret = 0, int _nr_m = 0, int _nr_sms = 0) : Abonament(_pret, 2*_nr_m, 9999999) {}
    void citire(istream& in) { Abonament::citire(in); }
    void afisare(ostream& out) { Abonament::afisare(out); }
};

class Abonat : public I_IO
{
    static int auxCT;
    string nume;
    int nr_tel;
    string abonament;
    Abonament* ab;
public:
    Abonat(string _nume = "", string tip = "") : nume(_nume), abonament(tip) 
    {
        auxCT++;
        nr_tel = auxCT;
    }

    string getType() const { return abonament; }
    int getNr() const { return nr_tel; }

    void citire(istream&);
    void afisare(ostream&);
};
int Abonat::auxCT = 0;

void Abonat::afisare(ostream& out)
{
    out << "Nume: " << nume;
    out << "\nNr tel: " << nr_tel;
    out << '\n';
}

class Retea
{
    vector <Abonament*> abonamente;
    vector <Abonat*> abonati;
    static Retea* instance;
    Retea() {}
public:
    static Retea* getInstance() {
        if (instance == nullptr) return new Retea();
        return instance;
    }

    void addAbonament(string);
    void Register(string, string);
    void afis();
    void CreateApel(int, int);
    void CreateSMS(int, int);

    ~Retea()
    {
        for (int i = 0; i < abonamente.size(); ++i)
            delete abonamente[i];
        abonamente.clear();
    }
};
Retea* Retea::instance = nullptr;

void Retea::addAbonament(string tip)
{
    Abonament* a = nullptr;
    if (tip == "simplu") a = new Abonament;
    if (tip == "auz") a = new AbonamentAuz;
    if (tip == "vaz") a = new AbonamentVedere;
    cin >> (*a);
    abonamente.push_back(a);
}
void Retea::Register(string nume, string tip)
{
    Abonat* A = new Abonat(nume, tip);
    abonati.push_back(A);
}

void Retea::afis()
{
    for(int i = 0; i < abonamente.size(); ++i)
        if (dynamic_cast<Abonament*>(abonamente[i]))
        {
            cout << "Tip: simplu\n";
            cout << (*abonamente[i]);
            cout << "Abonati:\n";
            for (int j = 0; j < abonati.size(); ++i)
                if (abonati[i]->getType() == "simplu" /*abonament[i]->getId() == abonati[i]->getABId()*/) cout << (*abonati[i]);
        }
    for (int i = 0; i < abonamente.size(); ++i)
        if (dynamic_cast<AbonamentAuz*>(abonamente[i]))
        {
            cout << "Tip: auz\n";
            cout << (*abonamente[i]);
            cout << "Abonati:\n";
            for (int j = 0; j < abonati.size(); ++i)
                if (abonati[i]->getType() == "auz") cout << (*abonati[i]);
        }
    for (int i = 0; i < abonamente.size(); ++i)
        if (dynamic_cast<AbonamentVedere*>(abonamente[i]))
        {
            cout << "Tip: vaz\n";
            cout << (*abonamente[i]);
            cout << "Abonati:\n";
            for (int j = 0; j < abonati.size(); ++i)
                if (abonati[i]->getType() == "vaz") cout << (*abonati[i]);
        }
}

void Retea::CreateApel(int sursa, int dest)
{
    for (int i = 0; i < abonati.size(); ++i)
        if (abonati[i]->getNr() == sursa);
}
void Retea::CreateSMS(int sursa, int dest)
{
    for (int i = 0; i < abonati.size(); ++i)
        if (abonati[i]->getNr() == sursa);
}

int main()
{
    Retea* R = R->getInstance();
    int var;
    while (1)
    {
        cout << "1.Adaugare abonament\n";
        cout << "2.Adaugare abonat\n";
        cout << "3.Afisare abonati si abonamente\n";
        cout << "4.Efectueaza SMS sau Apel\n";
        cout << "5.Nr apeluri si sms-uri\n";
        cout << "6.Castig\n";
        cout << "7.Inchide\n";
        cin >> var;
        if (var == 1)
        {
            string tip;
            cout << "Tip [simplu, auz, vaz]: ";
            cin >> tip;
            R->addAbonament(tip);
        }
        else if (var == 2)
        {
            string nume, tip;
            cout << "Nume: "; cin >> nume;
            cout << "Tip [simplu, auz, vaz]: "; cin >> tip;
            R->Register(nume, tip);
        }
        else if (var == 3) R->afis();
        else if (var == 4)
        {
            string tip;
            cout << "sms sau apel: "; cin >> tip;
            int tel_sursa, tel_dest;
            cout << "Nr tel sursa: "; cin >> tel_sursa;
            cout << "Nr tel destinatar: "; cin >> tel_dest;
            try {
                if (tip == "sms") R->CreateSMS(tel_sursa, tel_dest);
                else if (tip == "apel") R->CreateApel(tel_sursa, tel_dest);
                else throw(runtime_error("Tip incorect!\n"));
            }
            catch (const exception& ex) { cout << ex.what(); }
        }
    }
    return 0;
}