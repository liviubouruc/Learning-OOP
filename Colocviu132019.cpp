#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Bilet
{
protected:
    static int index;
    int stPlecare, stSosire;
    int zi, luna, an;
    int ora, minut;
    int codTren, durata, distanta;
    float pret;
    int cod;
public:
    Bilet(int _sp = 0, int _ss = 0, int _z = 0, int _l = 0, int _a = 0, int _h = 0, int _m = 0, int _c = 0, int _du = 0, int _di = 0, float _p = 0) :
        stPlecare(_sp), stSosire(_ss), zi(_z), luna(_l), an(_a), ora(_h), minut(_m), codTren(_c), durata(_du), distanta(_di), pret(_p) {
        index++; cod = index;
    }
    static inline int getIndex() { return index; }
    inline int getCodTren() const { return codTren; }
    inline int getDistanta() const { return distanta; }
    virtual string getSerie() = 0;
    virtual void setPret() = 0;
    virtual void citire(istream& in);
    virtual void afisare(ostream& out) const;
    friend istream& operator >> (istream& in, Bilet& b);
    friend ostream& operator << (ostream& out, const Bilet& b);

};

int Bilet::index = 0;

void Bilet::citire(istream& in)
{
    cout << "Introduceti urmatoarele date: \n";
    cout << "Statie plecare: ";
    in >> stPlecare;
    cout << "Statie sosire: ";
    in >> stSosire;
    cout << "Data plecarii (zi/luna/an): ";
    in >> zi >> luna >> an;
    cout << "Ora plecarii: ";
    in >> ora >> minut;
    cout << "Cod tren: ";
    in >> codTren;
    cout << "Durata calatorie: ";
    in >> durata;
    cout << "Distanta calatorie: ";
    in >> distanta;
}

/*istream& operator >> (istream& in, Bilet& b)
{
    b.citire(in);
    return in;
}*/

void Bilet::afisare(ostream& out) const
{
    out << "Date bilet: \n";
    out << "Statie plecare: " << stPlecare << '\n';
    out << "Statie sosire: " << stSosire << '\n';
    out << "Data plecarii (zi/luna/an): " << zi << " " << luna << " " << an << '\n';
    out << "Ora plecarii: " << ora << " " << minut << '\n';
    out << "Cod tren: " << codTren << '\n';
    out << "Durata calatorie: " << durata << '\n';
    out << "Distanta calatorie: " << distanta << '\n';
}

/*ostream& operator << (ostream& out, const Bilet& b)
{
    b.afisare(out);
    return out;
}
*/

///////////

class BiletRegio : virtual public Bilet
{
public:
    BiletRegio(int _sp = 0, int _ss = 0, int _z = 0, int _l = 0, int _a = 0, int _h = 0, int _m = 0, int _c = 0, int _du = 0, int _di = 0, float _p = 0) :
        Bilet(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p) {}

};

///////////

class BiletInterRegio : virtual public Bilet
{
protected:
    int loc;
public:
    BiletInterRegio(int _sp = 0, int _ss = 0, int _z = 0, int _l = 0, int _a = 0, int _h = 0, int _m = 0, int _c = 0, int _du = 0, int _di = 0, float _p = 0, int _lo = 0) :
        Bilet(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p), loc(_lo) {}

};

///////////

class Bilet1 : virtual public Bilet
{
protected:
    string meniu;
public:
    Bilet1(int _sp = 0, int _ss = 0, int _z = 0, int _l = 0, int _a = 0, int _h = 0, int _m = 0, int _c = 0, int _du = 0, int _di = 0, float _p = 0, string _me = "") :
        Bilet(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p), meniu(_me) {}

};

///////////

class Bilet2 : virtual public Bilet
{
public:
    Bilet2(int _sp = 0, int _ss = 0, int _z = 0, int _l = 0, int _a = 0, int _h = 0, int _m = 0, int _c = 0, int _du = 0, int _di = 0, float _p = 0) :
        Bilet(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p) {}


};

///////////

class BiletRegio1 : public BiletRegio, public Bilet1
{
public:
    BiletRegio1(int _sp = 0, int _ss = 0, int _z = 0, int _l = 0, int _a = 0, int _h = 0, int _m = 0, int _c = 0, int _du = 0, int _di = 0, float _p = 0, string _me = "") :
        BiletRegio(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p), Bilet1(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p, _me) {}
    string inline getSerie() { return "RI-" + cod; }
    void setPret() { pret = 0.39 * distanta; pret += pret / 5; }
    void citire(istream& in);
    void afisare(ostream& out) const;
    //friend istream& operator >> (istream& in, BiletRegio1& p);
    //friend ostream& operator << (ostream& out, const BiletRegio1& p);

};


void BiletRegio1::citire(istream& in)
{
    Bilet::citire(in);
    cout << "Meniu: ";
    in >> meniu;
}

/*istream& operator >> (istream& in, BiletRegio1& b)
{
    b.citire(in);
    return in;
}
*/
void BiletRegio1::afisare(ostream& out) const
{
    Bilet::afisare(out);
    out << "Meniu: " << meniu << '\n';
}
/*
ostream& operator << (ostream& out, const BiletRegio1& b)
{
    b.afisare(out);
    return out;
}*/



///////////

class BiletRegio2 : public BiletRegio, public Bilet2
{
public:
    BiletRegio2(int _sp = 0, int _ss = 0, int _z = 0, int _l = 0, int _a = 0, int _h = 0, int _m = 0, int _c = 0, int _du = 0, int _di = 0, float _p = 0) :
        BiletRegio(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p), Bilet2(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p) {}
    string inline getSerie() { return "RII-" + cod; }
    void setPret() { pret = 0.39 * distanta; }
    void citire(istream& in);
    void afisare(ostream& out) const;
    //friend istream& operator >> (istream& in, BiletRegio2& p);
    //friend ostream& operator << (ostream& out, const BiletRegio2& p);
};



void BiletRegio2::citire(istream& in)
{
    Bilet::citire(in);
}

/*istream& operator >> (istream& in, BiletRegio2& b)
{
    b.citire(in);
    return in;
}*/

void BiletRegio2::afisare(ostream& out) const
{
    Bilet::afisare(out);

}

/*ostream& operator << (ostream& out, const BiletRegio2& b)
{
    b.afisare(out);
    return out;
}*/


///////////

class BiletInterRegio1 : public BiletInterRegio, public Bilet1
{
public:
    BiletInterRegio1(int _sp = 0, int _ss = 0, int _z = 0, int _l = 0, int _a = 0, int _h = 0, int _m = 0, int _c = 0, int _du = 0, int _di = 0, float _p = 0, int _lo = 0, string _me = "") :
        BiletInterRegio(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p, _lo), Bilet1(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p, _me) {}
    string inline getSerie() { return "IRI-" + cod; }
    void setPret() { pret = 0.7 * distanta; pret += pret / 5; }
    void citire(istream& in);
    void afisare(ostream& out) const;
    // friend istream& operator >> (istream& in, BiletInterRegio1& p);
    // friend ostream& operator << (ostream& out, const BiletInterRegio1& p);
};

void BiletInterRegio1::citire(istream& in)
{
    Bilet::citire(in);
    cout << "Meniu: ";
    in >> meniu;
    cout << "Loc: ";
    in >> loc;
}

/*istream& operator >> (istream& in, BiletInterRegio1& b)
{
    b.citire(in);
    return in;
}*/

void BiletInterRegio1::afisare(ostream& out) const
{
    Bilet::afisare(out);
    out << "Meniu: " << meniu << '\n';
    out << "Loc: " << loc << '\n';
}

/*ostream& operator << (ostream& out, const BiletInterRegio1& b)
{
    b.afisare(out);
    return out;
}*/


///////////

class BiletInterRegio2 : public BiletInterRegio, public Bilet2
{
public:
    BiletInterRegio2(int _sp = 0, int _ss = 0, int _z = 0, int _l = 0, int _a = 0, int _h = 0, int _m = 0, int _c = 0, int _du = 0, int _di = 0, float _p = 0, int _lo = 0) :
        BiletInterRegio(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p, _lo), Bilet2(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p) {}
    string inline getSerie() { return "IRII-" + cod; }
    void setPret() { pret = 0.7 * distanta; }
    void citire(istream& in);
    void afisare(ostream& out) const;
    //friend istream& operator >> (istream& in, BiletInterRegio2& p);
    //friend ostream& operator << (ostream& out, const BiletInterRegio2& p);
};


void BiletInterRegio2::citire(istream& in)
{
    Bilet::citire(in);
    cout << "Loc: ";
    in >> loc;
}

/*istream& operator >> (istream& in, BiletInterRegio2& b)
{
    b.citire(in);
    return in;
}*/

void BiletInterRegio2::afisare(ostream& out) const
{
    Bilet::afisare(out);
    out << "Loc: " << loc << '\n';
}

/*ostream& operator << (ostream& out, const BiletInterRegio2& b)
{
    b.afisare(out);
    return out;
}*/

///////////

class Manager
{
private:
    static Manager* instance;
    Manager() {}
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;
    vector<Bilet*> bilete;
public:
    static Manager* getInstance();
    void adaugareBilet();
    void afisareBileteTren();
    void afisareBileteDistanta();
    void anulareBilet();
    void freeBilete();
    ~Manager();

};

Manager* Manager::instance = nullptr;

Manager* Manager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Manager();
    }
    return instance;
}

void Manager::adaugareBilet()
{
    string s;
    Bilet* b = nullptr;
    cout << "Introdu tip bilet: ";
    cin >> s;
    if (s == "Regio1")
        b = new BiletRegio1;
    else if (s == "Regio2")
        b = new BiletRegio2;
    else if (s == "InterRegio1")
        b = new BiletInterRegio1;
    else if (s == "InterRegio2")
        b = new BiletInterRegio2;
    cin >> (*b);
    bilete.push_back(b);
}

void Manager::afisareBileteTren()
{
    int cod, i;
    cout << "Introduceti cod tren: ";
    cin >> cod;
    for (i = 0; i < bilete.size(); i++)
        if (bilete[i]->getCodTren() == cod)
            cout << *(bilete[i]);
}

void Manager::afisareBileteDistanta()
{
    int distanta, i;
    cout << "Introduceti distanta: ";
    cin >> distanta;
    for (i = 0; i < bilete.size(); i++)
        if (bilete[i]->getDistanta() > distanta)
            cout << *(bilete[i]);
}

void Manager::anulareBilet()
{
    int i;
    string serie;
    cout << "Introduceti serie bilet: ";
    cin >> serie;
    for (i = 0; i < bilete.size(); i++)
        if (bilete[i]->getSerie() == serie)
            bilete.erase(bilete.begin() + i);
}

void Manager::freeBilete()
{
    if (bilete.size() != 0)
    {
        for (int i = 0; i < bilete.size(); i++)
            delete bilete[i];
        bilete.clear();
    }

}

Manager::~Manager()
{
    freeBilete();
}


int main()
{

    int cereri, i, cerere;
    Manager* M = M->getInstance();
    cout << "Introduceti numar cereri: ";
    cin >> cereri;
    cout << "Optiuni: \n 1. Eliberare bilet nou \n 2. Listare bilete dupa cod tren \n 3. Listare bilete mai mare decat o distanta \n 4. Anulare bilet\n";
    for (i = 0; i < cereri; i++)
    {
        cout << "Introduceti cerere: ";
        cin >> cerere;
        if (cerere == 1)
            M->adaugareBilet();
        else if (cerere == 2)
            M->afisareBileteTren();
        else if (cerere == 3)
            M->afisareBileteDistanta();
        else if (cerere == 4)
            M->anulareBilet();
        else cout << "Tasta gresita";
    }

    return 0;
}


/*
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;


class Bilet
{
protected:
    static int nr;
    string statie_plecare, statie_sosire;
    int zi, luna, an;
    int ora, minut;
    int cod_tren, durata, dist;
    bool anulat;
    int cod;
public:
    Bilet(string _s_p = "", string _s_s = "", int _zi = 0, int _luna = 0, int _an = 0, int _ora = 0, int _minut = 0, int _c_t = 0, int _durata = 0, int _dist = 0)
        : statie_plecare(_s_p), statie_sosire(_s_s), zi(_zi), luna(_luna), an(_an), ora(_ora), minut(_minut),
          cod_tren(_c_t), durata(_durata), dist(_dist) 
    {
        anulat = 0;
        nr++;
        cod = nr;
    }

    virtual string getSerie() = 0;
    void anuleaza() { anulat = 1; }
    bool valabil() const { return !anulat; }
    int getCodTren() const { return cod_tren; } 
    int getDist() const { return dist; }
    virtual void read(istream& in)
    {
        in >> statie_plecare;
        in >> statie_sosire;
        in >> zi >> luna >> an;
        in >> ora >> minut;
        in >> cod_tren >> durata >> dist;
    }
    virtual void print(ostream& out)
    {
        out << "Statia de plecare: " << statie_plecare << "\nStatie sosire: " << statie_sosire;
        out << "\nData [zi luna an ora minut]: " << zi << luna << an << ora << minut;
        out << "\nCod tren: " << cod_tren << "Durata: " << durata << "Distanta: " << dist;
        out << '\n';
    }
    friend istream& operator >>(istream& in, Bilet& bilet)
    {
        bilet.read(in);
        return in;
    }
    friend ostream& operator <<(ostream& out, Bilet& bilet)
    {
        bilet.print(out);
        return out;
    }

    virtual ~Bilet() {}
};
int Bilet::nr = 0;


class BiletInter : virtual public Bilet
{
protected:
    int loc_rezervat;
public:
    BiletInter(string _s_p = "", string _s_s = "", int _zi = 0, int _luna = 0, int _an = 0, int _ora = 0, int _minut = 0, int _c_t = 0, int _durata = 0, int _dist = 0, int _l_r = 0)
        : Bilet(_s_p, _s_s, _zi, _luna, _an, _ora, _minut, _c_t, _durata, _dist),
          loc_rezervat(_l_r) {}
    virtual ~BiletInter() {}
};

class BiletRegio : virtual public Bilet
{
public:
    BiletRegio(string _s_p = "", string _s_s = "", int _zi = 0, int _luna = 0, int _an = 0, int _ora = 0, int _minut = 0, int _c_t = 0, int _durata = 0, int _dist = 0)
        : Bilet(_s_p, _s_s, _zi, _luna, _an, _ora, _minut, _c_t, _durata, _dist) {}
    virtual ~BiletRegio() {}
};

class BiletClsI : virtual public Bilet
{
protected:
    string meniu;
public:
    BiletClsI(string _s_p = "", string _s_s = "", int _zi = 0, int _luna = 0, int _an = 0, int _ora = 0, int _minut = 0, int _c_t = 0, int _durata = 0, int _dist = 0, string _meniu = "") 
        : Bilet(_s_p, _s_s, _zi, _luna, _an, _ora, _minut, _c_t, _durata, _dist), 
          meniu(_meniu) {}
    virtual ~BiletClsI() {}
};

class BiletClsII : virtual public Bilet
{
public:
    BiletClsII(string _s_p = "", string _s_s = "", int _zi = 0, int _luna = 0, int _an = 0, int _ora = 0, int _minut = 0, int _c_t = 0, int _durata = 0, int _dist = 0)
        : Bilet(_s_p, _s_s, _zi, _luna, _an, _ora, _minut, _c_t, _durata, _dist)  {}
    virtual ~BiletClsII() {}
};

class BiletRegioClsI : public BiletClsI, public BiletRegio
{
public:
    BiletRegioClsI(string _s_p = "", string _s_s = "", int _zi = 0, int _luna = 0, int _an = 0, int _ora = 0, int _minut = 0, int _c_t = 0, int _durata = 0, int _dist = 0, string _meniu = "") 
        : Bilet(_s_p, _s_s, _zi, _luna, _an, _ora, _minut, _c_t, _durata, _dist), /// asta trebuie?
          BiletRegio(_s_p, _s_s, _zi, _luna, _an, _ora, _minut, _c_t, _durata, _dist),
          BiletClsI(_s_p, _s_s, _zi, _luna, _an, _ora, _minut, _c_t, _durata, _dist, _meniu) {}

    string getSerie()
    {
        string aux = "RI-" + cod;
        return aux;
    }
    void read(istream& in)
    {
        Bilet::read(in);
        in >> meniu;
    }
    void print(ostream& out)
    {
        Bilet::print(out);
        out << "Meniu: " << meniu;
        out << "\nPret: " << double(0.39*dist + 0.2*0.39*dist);
        out << '\n';
    }
};

class BiletRegioClsII : public BiletClsII, public BiletRegio
{
public:
    BiletRegioClsII(string _s_p = "", string _s_s = "", int _zi = 0, int _luna = 0, int _an = 0, int _ora = 0, int _minut = 0, int _c_t = 0, int _durata = 0, int _dist = 0)
        : Bilet(_s_p, _s_s, _zi, _luna, _an, _ora, _minut, _c_t, _durata, _dist),
          BiletRegio(_s_p, _s_s, _zi, _luna, _an, _ora, _minut, _c_t, _durata, _dist),
          BiletClsII(_s_p, _s_s, _zi, _luna, _an, _ora, _minut, _c_t, _durata, _dist) {}

    string getSerie()
    {
        string aux = "RII-" + cod;
        return aux;
    }
    void read(istream& in)
    {
        Bilet::read(in);
    }
    void print(ostream& out)
    {
        Bilet::print(out);
        out << "\nPret: " << double(0.39 * dist + 0.2);
    }
};

class BiletInterClsI : public BiletClsI, public BiletInter
{
public:
    BiletInterClsI(string _s_p = "", string _s_s = "", int _zi = 0, int _luna = 0, int _an = 0, int _ora = 0, int _minut = 0, int _c_t = 0, int _durata = 0, int _dist = 0, int _l_r = 0, string _meniu = "")
        : Bilet(_s_p, _s_s, _zi, _luna, _an, _ora, _minut, _c_t, _durata, _dist),
          BiletInter(_s_p, _s_s, _zi, _luna, _an, _ora, _minut, _c_t, _durata, _dist, _l_r),
          BiletClsI(_s_p, _s_s, _zi, _luna, _an, _ora, _minut, _c_t, _durata, _dist, _meniu) {}

    string getSerie()
    {
        string aux = "IRI-" + cod;
        return aux;
    }
    void read(istream& in)
    {
        Bilet::read(in);
        in >> loc_rezervat;
        in >> meniu;
    }
    void print(ostream& out)
    {
        Bilet::print(out);
        out << "Loc rezervat: " << loc_rezervat;
        out << "\nMeniu: " << meniu;
        out << "\nPret: " << double(0.7 * dist + 0.2 * 0.7 * dist);
        out << '\n';
    }
};

class BiletInterClsII : public BiletClsII, public BiletInter
{
public:
    BiletInterClsII(string _s_p = "", string _s_s = "", int _zi = 0, int _luna = 0, int _an = 0, int _ora = 0, int _minut = 0, int _c_t = 0, int _durata = 0, int _dist = 0, int _l_r = 0)
        : Bilet(_s_p, _s_s, _zi, _luna, _an, _ora, _minut, _c_t, _durata, _dist),
          BiletInter(_s_p, _s_s, _zi, _luna, _an, _ora, _minut, _c_t, _durata, _dist, _l_r),
          BiletClsII(_s_p, _s_s, _zi, _luna, _an, _ora, _minut, _c_t, _durata, _dist) {}

    string getSerie()
    {
        string aux = "IRII-" + cod;
        return aux;
    }
    void read(istream& in)
    {
        Bilet::read(in);
        cin >> loc_rezervat;
    }
    void print(ostream& out)
    {
        Bilet::print(out);
        cout << "Loc rezervat: " << loc_rezervat;
        cout << "\nPret: " << double(0.7 * dist);
        cout << '\n';
    }
};

class Manager //singleton
{
    vector <Bilet*> bilete;
    static Manager* instance;
    Manager() {}
public:
    static Manager* getInstance() {
        if (instance == nullptr) instance = new Manager();
        return instance;
    }

    void adaugaBilet(string tip, int cls);
    void afisBiletTren(int);
    void afisBiletDist(int);
    void anuleaza(string);

    ~Manager()
    {
        for (int i = 0; i < bilete.size(); ++i) delete bilete[i];
        bilete.clear();
    }
};

Manager* Manager::instance = nullptr;

void Manager::adaugaBilet(string tip, int cls)
{
    Bilet* b = nullptr;
    if (tip == "regio" && cls == 1) b = new BiletRegioClsI;
    if (tip == "regio" && cls == 2) b = new BiletRegioClsII;
    if (tip == "inter" && cls == 1) b = new BiletInterClsI;
    if (tip == "inter" && cls == 2) b = new BiletInterClsII;
    cin >> (*b);
    bilete.push_back(b);
}

void Manager::afisBiletTren(int cod)
{
    for (int i = 0; i < bilete.size(); ++i)
        if (bilete[i]->getCodTren() == cod && bilete[i]->valabil()) cout << *(bilete[i]);
}
void Manager::afisBiletDist(int distanta)
{
    for (int i = 0; i < bilete.size(); ++i)
        if (bilete[i]->getDist() >= distanta && bilete[i]->valabil()) cout << *(bilete[i]);
}
void Manager::anuleaza(string seria)
{
    for (int i = 0; i < bilete.size(); ++i)
        if (bilete[i]->getSerie() == seria) bilete[i]->anuleaza();
}

int main()
{
    Manager* M = M->getInstance();
    int var;
    while (1)
    {
        cout << "1.Elibereaza bilet\n";
        cout << "2.Lista biletelor eliberate pentru un tren\n";
        cout << "3.Bilete eliberate pentru o distanta data\n";
        cout << "4.Anulare bilet.\n";
        cout << "5.Inchide\n";
        cin >> var;
        if (var == 1)
        {
            string tip;
            int cls;
            cout << "Tip: regio sau inter ?\n";
            cin >> tip;
            cout << "\nClasa: 1 sau 2 ?\n";
            cin >> cls; cout << '\n';
            //Manager::getInstance()->adaugaBilet(tip, cls);
            M->adaugaBilet(tip, cls);
        }
        else if (var == 2)
        {
            int cod;
            cout << "Codul trenului: ";
            cin >> cod; cout << '\n';
            //Manager::getInstance()->afisBiletTren(cod);
            M->afisBiletTren(cod);
        }
        else if (var == 3)
        {
            int distanta;
            cout << "Distanta: ";
            cin >> distanta; cout << '\n';
            M->afisBiletDist(distanta);
            //Manager::getInstance()->afisBiletDist(distanta);
        }
        else if (var == 4)
        {
            string serie;
            cout << "Seria: ";
            cin >> serie; cout << '\n';
            M->anuleaza(serie);
            //Manager::getInstance()->anuleaza(serie);
        }
        else if (var == 5) break;
        else cout << "Numar invalid!\n";
    }
    return 0;
}*/