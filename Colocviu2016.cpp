#include <iostream>
#include <vector>
#include <set>
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

class Ingredient : public I_IO
{
    string denIng;
    double pret;
    int cant;
    string masIng;
public:
    Ingredient(string _den="", double _pret=0, int _cant=0, string _mas="") :
        denIng(_den), pret(_pret), cant(_cant), masIng(_mas) {}
    void citire(istream&);
    void afisare(ostream&);
    double getPrice() const { return pret; }
    string getName() const { return denIng; }
};

void Ingredient::citire(istream& in)
{
    cout << "Denumire: "; in >> denIng;
    cout << "Pret: "; in >> pret;
    cout << "Cant: "; in >> cant;
    cout << "Masura: "; in >> masIng;
}
void Ingredient::afisare(ostream& out)
{
    out << "Denumire: " << denIng;
    out << "\nPret: " << pret;
    out << "\nCant: " << cant;
    out << "\nMasura: " << masIng;
    out << '\n';
}

class Bautura : public I_IO
{
    string denumire;
    double pret;
public:
    Bautura(string _denumire, double _pret) : denumire(_denumire), pret(_pret) {}

    double getPrice() const { return pret; }
    void citire(istream& in)
    {
        cout << "Denumire bautura: "; in >> denumire;
        cout << "Pret bautura: "; in >> pret;
    }
    void afisare(ostream& out)
    {
        out << "Denumire: " << denumire;
        out << "Pret: " << pret;
        out << '\n';
    }
};

class Pizza : public I_IO
{
protected:
    static int id;
    int cod;
    string nume;
    vector <Ingredient*> ingrediente;
    int nrIng;
    bool veg;
public:
    Pizza(string _nume = "", int _nrIng = 0, bool _veg = 0)
        : nume(_nume), nrIng(_nrIng), veg(_veg)
    {
        id++;
        cod = id;
    }

    void afisareIngrediente();
    double getPret() const
    {
        double pret = 0;
        for (int i = 0; i < ingrediente.size(); ++i) pret += ingrediente[i]->getPrice();
        return pret;
    }

    void citire(istream&);
    void afisare(ostream&);

    virtual ~Pizza()
    {
        for (int i = 0; i < ingrediente.size(); ++i)
            delete ingrediente[i];
        ingrediente.clear();
    }
};
int Pizza::id = 0;

void Pizza::citire(istream& in)
{
    cout << "Nume pizza: "; in >> nume;
    cout << "Vegetariana: "; in >> veg;
    cout << "Numar Ingrediente: "; in >> nrIng;
    for (int i = 0; i < nrIng; ++i)
    {
        Ingredient* ing = nullptr;
        in >> (*ing);
        ingrediente.push_back(ing);
        //Manager* M = M->getInstance();
        Manager::getInstance()->adaugaIng(ing);
    }
}
void Pizza::afisare(ostream& out)
{
    out << "ID: " << id;
    out << "\nNume: " << nume;
    out << "\nVegetariana: " << veg;
    out << "\nNumar ingrediente: " << nrIng;
    out << "\nIngrediente:\n";
    for (int i = 0; i < ingrediente.size(); ++i)
        out << (*ingrediente[i]);
    out << "Pret: " << this->getPret() << '\n';
}

void Pizza::afisareIngrediente()
{
    for (int i = 0; i < ingrediente.size(); ++i)
    {
        cout << (*ingrediente[i]);
        int ct = 0;
        for (int j = 0; j < ingrediente.size(); ++j)
            if (ingrediente[i]->getName() == ingrediente[j]->getName() && i != j) ct++;
        cout << "Apare de " << ct << " ori\n";
    }
}

class PizzaSpec : virtual public Pizza
{
    vector <Ingredient*> ingSpec;
    int nrIngSpec;
public:
    PizzaSpec(int _cod = 0, string _nume = "", int _nrIng = 0, bool _veg = 0, int _nrIngSpec = 0)
        : Pizza(_nume, _nrIng, false), nrIngSpec(_nrIngSpec) 
    {
        id++;
        cod = id;
    }

    void afisareIngrediente();
    double getPret() const
    {
        double pret = 0;
        for (int i = 0; i < ingrediente.size(); ++i) pret += ingrediente[i]->getPrice();
        for (int i = 0; i < ingSpec.size(); ++i) pret += ingSpec[i]->getPrice();
        return pret;
    }

    void citire(istream&);
    void afisare(ostream&);

    ~PizzaSpec()
    {
        for (int i = 0; i < ingSpec.size(); ++i)
            delete ingSpec[i];
        ingSpec.clear();
    }
};

void PizzaSpec::citire(istream& in)
{
    cout << "Nume pizza: "; in >> nume;
    cout << "Vegetariana: "; in >> veg;
    while (veg)
    {
        cout << "Pizza speciala nu poate fi veg! Mai incearca odata!\n";
        in >> veg;
    }
    cout << "Numar Ingrediente: "; in >> nrIng;
    for (int i = 0; i < nrIng; ++i)
    {
        Ingredient* ing = nullptr;
        in >> (*ing);
        ingrediente.push_back(ing);
    }
    cout << "Numar Ingrediente speciale: "; in >> nrIngSpec;
    for (int i = 0; i < nrIng; ++i)
    {
        Ingredient* ing = nullptr;
        in >> (*ing);
        ingSpec.push_back(ing);
    }
}
void PizzaSpec::afisare(ostream& out)
{
    out << "ID: " << id;
    out << "\nNume: " << nume;
    out << "\nVegetariana: " << veg;
    out << "\nNumar ingrediente: " << nrIng;
    out << "\nIngrediente:\n";
    for (int i = 0; i < ingrediente.size(); ++i)
        out << (*ingrediente[i]);
    out << "\nIngrediente speciale:\n";
    for (int i = 0; i < ingSpec.size(); ++i)
        out << (*ingSpec[i]);
    out << "Pret: " << this->getPret() << '\n';
}

void PizzaSpec::afisareIngrediente()
{
    for (int i = 0; i < ingrediente.size(); ++i)
        cout << (*ingrediente[i]);
    for (int i = 0; i < ingSpec.size(); ++i)
        cout << (*ingSpec[i]);
}

class Oferta : public I_IO
{
    Bautura* b;
    Pizza* p;
public:
    Oferta() {}

    void citire(istream&);
    void afisare(ostream&);
    
    ~Oferta()
    {
        delete b;
        delete p;
    }
};

void Oferta::citire(istream& in)
{
    Pizza* p = nullptr;
    string tip;
    cout << "Tip pizza [simpla speciala]: "; in >> tip;
    try {
        if (tip == "simpla") p = new Pizza();
        else if (tip == "speciala") p = new PizzaSpec();
        else throw(runtime_error("Tip gresit!\n"));
    }
    catch (const exception& ex) { cout << ex.what(); }
    in >> (*p);

    in >> (*b);
}
void Oferta::afisare(ostream& out)
{
    out << "Pizza:\n";
    out << (*p);
    out << "Bautura:\n";
    out << (*b);
    out << "Pret: " << p->getPret() + b->getPrice() << '\n';
}

class Manager
{
private:
    vector <Pizza*> pizze;
    vector <Oferta*> oferte;
    set <Ingredient*> ingrediente;

    static Manager* instance;
    Manager() {}
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

public:
    static Manager* getInstance() {
        if (instance == nullptr) instance = new Manager;
        return instance;
    }

    void adaugaPizza();
    void afisarePizza();
    void afisareIngPizza();
    void adaugareOferta();
    void afisareOferte();
    void afisareIngrediente();
    void adaugaIng(Ingredient* ing) { ingrediente.insert(ing); }

    ~Manager()
    {
        for (int i = 0; i < pizze.size(); ++i)
            delete pizze[i];
        pizze.clear();
        for (int i = 0; i < oferte.size(); ++i)
            delete oferte[i];
        oferte.clear();
    }
};

Manager* Manager::instance = nullptr;

void Manager::afisareIngrediente()
{
    for (int i = 0; i < pizze.size(); ++i) pizze[i]->afisareIngrediente();
}

void Manager::adaugaPizza()
{
    Pizza* p = nullptr;
    string tip;
    cout << "Tip pizza [simpla speciala]: "; cin >> tip;
    try {
        if (tip == "simpla") p = new Pizza();
        else if (tip == "speciala") p = new PizzaSpec();
        else throw(runtime_error("Tip gresit!\n"));
    }
    catch (const exception& ex) { cout << ex.what(); }
    cin >> (*p);
    pizze.push_back(p);
}

void Manager::afisarePizza()
{
    for(int i = 0; i < pizze.size(); ++i)
        if (dynamic_cast<Pizza*>(pizze[i]))
        {
            cout << "Pizze simple:\n";
            cout << (*pizze[i]);
        }
    for (int i = 0; i < pizze.size(); ++i)
        if (dynamic_cast<PizzaSpec*>(pizze[i]))
        {
            cout << "Pizze speciale:\n";
            cout << (*pizze[i]);
        }
}
void Manager::afisareIngPizza()
{
    string tip;
    cout << "Tip [simpla speciala]: "; cin >> tip;
    if (tip == "simpla") {
        for (int i = 0; i < pizze.size(); ++i)
            if (dynamic_cast<Pizza*>(pizze[i])) pizze[i]->afisareIngrediente();
    }
    else if (tip == "simpla") {
        for (int i = 0; i < pizze.size(); ++i)
            if (dynamic_cast<PizzaSpec*>(pizze[i])) pizze[i]->afisareIngrediente();
    }
}

void Manager::adaugareOferta()
{
    Oferta* o = nullptr;
    cin >> (*o);
    oferte.push_back(o);
}
void Manager::afisareOferte()
{
    for (int i = 0; i < oferte.size(); ++i) cout << (*oferte[i]);
}

int main()
{
    Manager* M = M->getInstance();
    int var;
    while (1)
    {
        cout << "1.Afisare ingrediente\n";
        cout << "2.Afisare sortimente\n";
        cout << "3.Afisare ingrediente pizza\n";
        cout << "4.Afisare oferte speciale\n";
        cout << "5.Adauga pizza\n";
        cout << "6.Adauga oferta\n";
        cout << "7.Inchide\n";
        cin >> var;
        if (var == 1) M->afisareIngrediente();
        else if (var == 2) M->afisarePizza();
        else if (var == 3) M->afisareIngPizza();
        else if (var == 4) M->afisareOferte();
        else if (var == 5) M->adaugaPizza();
        else if (var == 6) M->adaugareOferta();
        else if (var == 7) break;
        else cout << "Numar invalid\n";
    }
}