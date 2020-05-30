#include <iostream>
#include <vector>

using namespace std;

class I_IO
{
    virtual void read(istream&) = 0;
    virtual void print(ostream&) = 0;

    friend istream& operator >>(istream& in, I_IO& ob)
    {
        ob.read(in);
        return in;
    }
    friend ostream& operator <<(ostream& out, I_IO& ob)
    {
        ob.print(out);
        return out;
    }
};

class Persoana
{
protected:
    string nume, prenume;
    int cnp;
};

class Nemembri : public Persoana
{
    string email;
};

class Membri : public Persoana
{
    int zi, luna, an;
    string membership;
    string sex;

};

class Manager
{
    vector <Persoana*> db;

    static Manager* instance;
    Manager();
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;
public:
    static Manager* getInstance() {
        if (instance == nullptr) instance = new Manager;
        return instance;
    }
};
Manager* Manager::instance = nullptr;

int main()
{
    Manager* M = M->getInstance();
    while (1)
    {
        cout << "1.Toate persoanele\n";
        cout << "2.Membri gold cu pachete\n";
        cout << "3.Toate familiile\n";
        cout << "4.Cei care pierd calitatea de membru premium\n";
    }
    return 0;
}