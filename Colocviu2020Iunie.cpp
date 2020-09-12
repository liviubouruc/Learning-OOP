/*
Bouruc Petru-Liviu 135
MSBuild Visual Studio (cel default de la Visual Studio 2019, c++17)
Lupascu Marian
*/
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

template <class T> /// am gasit aceasta functie template in laborator si mi s-a parut good practice sa o folosesc
void isPositive(T value)
{
    if (value < 0) throw std::runtime_error("Nu poate fi negativ !\n");
}

class InputOutput // am luat-o din laborator, mi s-a parut foarte utila si faina <3
{
public:
    virtual void citire(istream&) = 0;
    virtual void afisare(ostream&) = 0;

    friend istream& operator >>(istream& in, InputOutput& ob)
    {
        ob.citire(in);
        return in;
    }
    friend ostream& operator <<(ostream& out, InputOutput& ob)
    {
        ob.afisare(out);
        return out;
    }

    virtual ~InputOutput() {}
};

class Masca : public InputOutput
{
protected:
    string tip;
public:
    Masca(string _tip) : tip(_tip) {}

    string getTip() const { return tip; }

    virtual ~Masca() {}
};

class MascaChirurgicala : public Masca
{
    string culoare;
    int nrP;
public:
    MascaChirurgicala(string _tip = "", string _col = "", int _nr = 0) : Masca(_tip), culoare(_col), nrP(_nr) {}
    MascaChirurgicala(const MascaChirurgicala& m) : Masca(m.tip), culoare(m.culoare), nrP(m.nrP) {}
    MascaChirurgicala& operator =(const MascaChirurgicala& b)
    {
        if (this == &b)
            return *this;
        tip = b.tip;
        culoare = b.culoare;
        nrP = b.nrP;
        return *this;
    }
    void citire(istream&);
    void afisare(ostream&);
};
void MascaChirurgicala::citire(istream& in)
{
    cout << "Tip: "; in >> tip;
    cout << "Culoare: "; in >> culoare;
    cout << "Nr pliuri: "; in >> nrP;
}

void MascaChirurgicala::afisare(ostream& out)
{
    out << "Tip " << tip;
    out << "\nCuloare " << culoare;
    out << "\nNr pliuri " << nrP;
    out << '\n';
}

class MascaPolicarbonat : public Masca
{
    string tipPrindere;
public:
    MascaPolicarbonat(string _tip = "") : Masca("ff0"), tipPrindere(_tip) {}
    MascaPolicarbonat(const MascaPolicarbonat& m) : Masca(m.tip), tipPrindere(m.tipPrindere) {}
    
    void citire(istream&);
    void afisare(ostream&);
};
void MascaPolicarbonat::citire(istream& in)
{
    cout << "Tip prindere: "; in >> tipPrindere;
}

void MascaPolicarbonat::afisare(ostream& out)
{
    out << "Tip " << tip;
    out << "\nTip prindere " << tipPrindere;
    out << '\n';
}

class Dezinfectant : public InputOutput
{
protected:
    int nrspecii;
    vector <string> ingrediente;
    vector <string> tipS;
    
public:
    Dezinfectant(int _nr = 0, vector<string> _ing = vector<string>(), vector<string> _tip = vector<string>())
        : nrspecii(_nr), ingrediente(_ing), tipS(_tip) {}
    Dezinfectant(const Dezinfectant& b)
    {
        nrspecii = b.nrspecii;
        ingrediente = b.ingrediente;
        tipS = b.tipS;
    }
    Dezinfectant& operator =(const Dezinfectant& b)
    {
        if (this == &b)
            return *this;

        nrspecii = b.nrspecii;
        ingrediente = b.ingrediente;
        tipS = b.tipS;
        return *this;
    }

    void citire(istream&); // antetul functiei de la clasa I_IO, luata din laborator; implementarea in afara clasei
    void afisare(ostream&); // la fel si aici
    virtual double eficienta() = 0;
    virtual int getNrS() = 0;

    virtual ~Dezinfectant() {}
};

void Dezinfectant::citire(istream& in)
{
    cout << "NrSpecii: "; in >> nrspecii;
    int nrIng;
    cout << "Nr ing "; in >> nrIng;
    for (int i = 0; i < nrIng; ++i)
    {
        string ingred;
        cout << "Ingredient: " << ingred;
        ingrediente.push_back(ingred);
    }
    int nrtipuri;
    cout << "Nr tipuri "; in >> nrtipuri;
    for (int i = 0; i < nrtipuri; ++i)
    {
        string tipp;
        cout << "Tip: " << tipp;
        ingrediente.push_back(tipp);
    }
}
void Dezinfectant::afisare(ostream& out)
{
    out << "NrSpecii: " << nrspecii;
    out << '\n';
    for (int i = 0; i < ingrediente.size(); ++i) out << ingrediente[i] << " ";
    for (int i = 0; i < tipS.size(); ++i) out << tipS[i] << " ";
    out << '\n';
}


class DezinfectantBacterii : virtual public Dezinfectant
{
protected:
    static const double TotalBacterii;
public:
    DezinfectantBacterii(int _nr = 0, vector<string> _ing = vector<string>(), vector<string> _tip = vector<string>())
        : Dezinfectant(_nr, _ing, _tip) {}
    DezinfectantBacterii(const Dezinfectant& d) : Dezinfectant() {}
    void citire(istream&); // antetul functiei de la clasa I_IO, luata din laborator; implementarea in afara clasei
    void afisare(ostream&); // la fel si aici

    double eficienta();
    int getNrS() { return nrspecii; }

    virtual ~DezinfectantBacterii() {}
};
const double DezinfectantBacterii::TotalBacterii = 1e9;

void DezinfectantBacterii::citire(istream& in)
{
    Dezinfectant::citire(in);
}
void DezinfectantBacterii::afisare(ostream& out)
{
    Dezinfectant::afisare(out);
}
double DezinfectantBacterii::eficienta()
{
    return nrspecii / TotalBacterii;
}

class DezinfectantiFungi : virtual public Dezinfectant
{
protected:
    static const double TotalBacterii;
public:
    DezinfectantiFungi(int _nr = 0, vector<string> _ing = vector<string>(), vector<string> _tip = vector<string>())
        : Dezinfectant(_nr, _ing, _tip) {}
    DezinfectantiFungi(const DezinfectantiFungi& d) : Dezinfectant(d) {}
    void citire(istream&); // antetul functiei de la clasa I_IO, luata din laborator; implementarea in afara clasei
    void afisare(ostream&); // la fel si aici
    double eficienta();
    int getNrS() { return nrspecii; }
    virtual ~DezinfectantiFungi() {}
};
const double DezinfectantiFungi::TotalBacterii = 1.5*1e6;

void DezinfectantiFungi::citire(istream& in)
{
    Dezinfectant::citire(in);
}
void DezinfectantiFungi::afisare(ostream& out)
{
    Dezinfectant::afisare(out);
}
double DezinfectantiFungi::eficienta()
{
    return nrspecii / TotalBacterii;
}

class DezinfectantiVirusuri : virtual public Dezinfectant
{
protected:
    static const double TotalBacterii;
public:
    DezinfectantiVirusuri(int _nr = 0, vector<string> _ing = vector<string>(), vector<string> _tip = vector<string>())
        : Dezinfectant(_nr, _ing, _tip) {}
    DezinfectantiVirusuri(const DezinfectantiVirusuri& d) : Dezinfectant(d) {}
    void citire(istream&); // antetul functiei de la clasa I_IO, luata din laborator; implementarea in afara clasei
    void afisare(ostream&); // la fel si aici
    double eficienta();
    int getNrS() { return nrspecii; }
    virtual ~DezinfectantiVirusuri() {}
};
const double DezinfectantiVirusuri::TotalBacterii = 1e8;

void DezinfectantiVirusuri::citire(istream& in)
{
    Dezinfectant::citire(in);
}
void DezinfectantiVirusuri::afisare(ostream& out)
{
    Dezinfectant::afisare(out);
}
double DezinfectantiVirusuri::eficienta()
{
    return nrspecii / TotalBacterii;
}

class DezinfectantTot : public DezinfectantiFungi, public DezinfectantBacterii, public DezinfectantiVirusuri
{
public:
    DezinfectantTot(int _nr = 0, vector<string> _ing = vector<string>(), vector<string> _tip = vector<string>())
        : Dezinfectant(_nr, _ing, _tip) {}
    DezinfectantTot(const DezinfectantTot& d) : Dezinfectant(d) {}
    void citire(istream&); // antetul functiei de la clasa I_IO, luata din laborator; implementarea in afara clasei
    void afisare(ostream&); // la fel si aici
    double eficienta();
    int getNrS() { return nrspecii; }
};

void DezinfectantTot::citire(istream& in)
{
    Dezinfectant::citire(in);
}
void DezinfectantTot::afisare(ostream& out)
{
    Dezinfectant::afisare(out);
}
double DezinfectantTot::eficienta()
{
    return (DezinfectantBacterii::getNrS() + DezinfectantiFungi::getNrS() + DezinfectantiVirusuri::getNrS()) / (DezinfectantiVirusuri::TotalBacterii + DezinfectantBacterii::TotalBacterii + DezinfectantiFungi::TotalBacterii);
}

class Achizitie : public InputOutput
{
    int zi, luna, an;
    string nume;
    vector <Dezinfectant*> dezinfectanti;
    vector <Masca*> masti;
public:
    Achizitie(int _zi = 0, int _luna = 0, int _an = 0, string _nume = "")
        : zi(_zi), luna(_luna), an(_an) {}
    Achizitie(const Achizitie& a) : zi(a.zi), luna(a.luna), an(a.an)
    {
        for (auto ptr : a.dezinfectanti) // din lab
                addDezinf(ptr);
        for (auto ptr : a.masti)
            addMasca(ptr);
    }
    Achizitie& operator =(const Achizitie& a)
    {
        if (this == &a)
            return *this;

        for (int i = 0; i < dezinfectanti.size(); ++i) // din lab astea de mai jos
            delete dezinfectanti[i];
        dezinfectanti.clear();
        for (auto ptr : a.dezinfectanti)
            addDezinf(ptr);

        for (int i = 0; i < masti.size(); ++i)
            delete masti[i];
        masti.clear();
        for (auto ptr : a.masti)
            addMasca(ptr);

        return *this;
    }

    Achizitie& operator+=(Dezinfectant* ob) { // din laborator
        dezinfectanti.push_back(ob);
        return *this;
    }
    Achizitie& operator+=(Masca* ob) { // din laborator
        masti.push_back(ob);
        return *this;
    }

    double getTotal()
    {
        double t = 0;
        for (int i = 0; i < masti.size(); ++i)
            if (dynamic_cast<MascaPolicarbonat*>(masti[i])) t += 20;
            else if (dynamic_cast<MascaChirurgicala*>(masti[i]))
            {
                if (masti[i]->getTip() == "ffp1") t += 5;
                else if (masti[i]->getTip() == "ffp2") t += 10;
                else if (masti[i]->getTip() == "ffp3") t += 15;
            }
        for (int i = 0; i < masti.size(); ++i)
            if (dezinfectanti[i]->eficienta() < 0.9) t += 10;
            else if (dezinfectanti[i]->eficienta() < 0.95) t += 20;
            else if (dezinfectanti[i]->eficienta() < 0.975) t += 30;
            else if (dezinfectanti[i]->eficienta() < 0.99) t += 40;
            else if (dezinfectanti[i]->eficienta() < 0.9999) t += 50;
        return t;
    }

    bool operator<(Achizitie& rhs) const { // din lab, nu am mai avut timp sa vad de ce nu merge:(
        //return getTotal() < rhs.getTotal();
        return 1;
    }
    bool operator==(Achizitie& rhs) const { // si asta la fel
        //return getTotal() == rhs.getTotal();
        return 0;
    }

    string Nume() const { return nume; }
    int getLuna() const { return luna; }
    int getZi() const { return zi; }
    int getAn() const { return an; }

    void addDezinf(Dezinfectant* d)
    {
        if (DezinfectantBacterii* ob = dynamic_cast<DezinfectantBacterii*>(d)) /// invatat la lab
            dezinfectanti.push_back(new DezinfectantBacterii(*ob));
        else if (DezinfectantiFungi* ob = dynamic_cast<DezinfectantiFungi*>(d))
            dezinfectanti.push_back(new DezinfectantiFungi(*ob));
        else if (DezinfectantiVirusuri* ob = dynamic_cast<DezinfectantiVirusuri*>(d))
            dezinfectanti.push_back(new DezinfectantiVirusuri(*ob));
        else if (DezinfectantTot* ob = dynamic_cast<DezinfectantTot*>(d))
            dezinfectanti.push_back(new DezinfectantTot(*ob));
    }
    void addMasca(Masca* m)
    {
        if (MascaChirurgicala* ob = dynamic_cast<MascaChirurgicala*>(m)) /// invatat la lab
            masti.push_back(new MascaChirurgicala(*ob));
        else if (MascaPolicarbonat* ob = dynamic_cast<MascaPolicarbonat*>(m))
            masti.push_back(new MascaPolicarbonat(*ob));
    }

    void citire(istream&)
    {
        int nrMasti;
        cin >> nrMasti;
        for (int i = 0; i < nrMasti; ++i)
        {
            string tip;
            Masca* p = nullptr;
            try {
                if (tip == "poli") p = new MascaPolicarbonat;
                else if (tip == "chir") p = new MascaChirurgicala;
                else throw runtime_error("Tip invalid!\n");
            }
            catch (const exception& ex) {
                cout << ex.what();
                delete p;
                return;
            }
            cin >> (*p);
            //Manager::getInstance()->operator+=(*p);
            masti.push_back(p);
        }
        int nrDez;
        cin >> nrDez;
        for (int i = 0; i < nrDez; ++i)
        {
            string tip;
            cout << "Tip dezinf [bacterii virursuri funghi tot] "; cin >> tip;
            Dezinfectant* p = nullptr;
            try {
                if (tip == "bacterii") p = new DezinfectantBacterii;
                else if (tip == "virursuri") p = new DezinfectantiVirusuri;
                else if (tip == "funghi") p = new DezinfectantiFungi;
                else if (tip == "tot") p = new DezinfectantTot;
                else throw runtime_error("Tip invalid!\n");
            }
            catch (const exception& ex) {
                cout << ex.what();
                delete p;
                return;
            }
            cin >> (*p);
            //Manager::getInstance()->operator+=(*p);
            dezinfectanti.push_back(p);
        }
    }
    void afisare(ostream&) {}

    ~Achizitie();
};
Achizitie::~Achizitie()
{
    for (int i = 0; i < dezinfectanti.size(); ++i) // din lab astea de mai jos
        delete dezinfectanti[i];
    for (int i = 0; i < masti.size(); ++i)
        delete masti[i];
}

class Manager
{
    vector <Achizitie*> achizitii;
    vector <Dezinfectant*> dezins;
    vector <Masca*> mastii;

    static Manager* instance;
    Manager() {}
    Manager(const Manager& ob) = delete;// si liniile acestea cu delete tot din laborator<3
    Manager(Manager&& ob) noexcept = delete;
    Manager& operator=(const Manager& ob) = delete;
    Manager& operator=(Manager&& ob) = delete; 
public:
    static Manager* getInstance() {
        if (instance == nullptr) return new Manager();
        return instance;
    }

    void adaugaDezinf();
    void adaugaMasca()
    {
        string tip;
        cout << "Tip masca [poli chir] "; cin >> tip;
        Masca* p = nullptr;
        try {
            if (tip == "poli") p = new MascaPolicarbonat;
            else if (tip == "chir") p = new MascaChirurgicala;
            else throw runtime_error("Tip invalid!\n");
        }
        catch (const exception& ex) {
            cout << ex.what();
            delete p;
            return;
        }
        cin >> (*p);
        //Manager::getInstance()->operator+=(*p);
        mastii.push_back(p);
    }
    void adaugaAchiz()
    {
        Achizitie* a = new Achizitie();
        cin >> (*a);
        achizitii.push_back(a);
    }
    void dezinfCelMaiEf()
    {
        int Max = 0, pozMax = 0;
        for(int i = 0; i < dezins.size(); ++i)
            if (dezins[i]->eficienta() > Max)
            {
                Max = dezins[i]->eficienta();
                pozMax = i;
            }
        cout << (*dezins[pozMax]);
    }
    void getVenitLuna()
    {
        int lun;
        cin >> lun;
        double s = 0;
        for (int i = 0; i < achizitii.size(); ++i)
            if (achizitii[i]->getLuna() == lun) s += achizitii[i]->getTotal();
        cout << s << '\n';
    }
    void venitSlab()
    {
        int zi, luna, an;
        int aux = achizitii[0]->getTotal();
        for (int i = 1; i < achizitii.size(); i++)
            if (achizitii[i]->getTotal() < aux)
            {
                aux = achizitii[i]->getTotal();
                zi = achizitii[i]->getZi();
                luna = achizitii[i]->getLuna();
                an = achizitii[i]->getAn();
            }
        cout << zi << " " << luna << " " << an << '\n';
    }
    void tva()
    {
        double sum = 0;
        for (int i = 0; i < achizitii.size(); ++i) sum += achizitii[i]->getTotal();
        cout << sum * 0.19 << '\n';
    }

    Manager& operator+=(Achizitie* a) { // din laborator
        achizitii.push_back(a);
        return *this;
    }


    ~Manager()
    {
        for (int i = 0; i < achizitii.size(); ++i)
            delete achizitii[i];
        achizitii.clear();
        for (int i = 0; i < mastii.size(); ++i)
            delete mastii[i];
        mastii.clear();
        for (int i = 0; i < dezins.size(); ++i)
            delete dezins[i];
        dezins.clear();
    }
};
Manager* Manager::instance = nullptr;

void Manager::adaugaDezinf()
{
    string tip;
    cout << "Tip dezinf [bacterii virursuri funghi tot] "; cin >> tip;
    Dezinfectant* p = nullptr;
    try {
        if (tip == "bacterii") p = new DezinfectantBacterii;
        else if (tip == "virursuri") p = new DezinfectantiVirusuri;
        else if (tip == "funghi") p = new DezinfectantiFungi;
        else if (tip == "tot") p = new DezinfectantTot;
        else throw runtime_error("Tip invalid!\n");
    }
    catch (const exception& ex) { 
        cout << ex.what(); 
        delete p;
        return; 
    }
    cin >> (*p);
    //Manager::getInstance()->operator+=(*p);
    dezins.push_back(p);
}

int main()
{
    int var;
    Manager* M = M->getInstance();
    while (1)
    {
        cout << "1.Adauga dezinf\n";
        cout << "2.Adauga masca\n";
        cout << "3.Adauga achiz\n";
        cout << "4.Cel mai ef dezinf\n";
        cout << "5.Venit pe luna\n";
        cout << "6.Venit pe masti\n";
        cout << "7.Modif reteta\n";
        cout << "8.Cel mai fidel\n";
        cout << "9.Cea mai slaba zi\n";
        cout << "10.TVA\n";
        cout << "11.inchide\n";
        cin >> var;
        try {
            isPositive(var);
        }
        catch (const exception& ex) {
            cout << ex.what();
            continue;
        }
        if (var == 1) M->adaugaDezinf();
        else if (var == 2) M->adaugaMasca();
        else if (var == 3) M->adaugaAchiz();
        else if (var == 4) M->dezinfCelMaiEf();
        else if (var == 5) M->getVenitLuna();
        else if(var == 9) M->venitSlab();
        else if (var == 10) M->tva();
        else if(var == 11) break;
    }
    if (Manager::getInstance() != nullptr) { // din laborator
        delete Manager::getInstance();
    }
    return 0;
}