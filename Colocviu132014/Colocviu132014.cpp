#include <iostream>
#include "Cabinet.h"

using namespace std;

int main()
{
    Cabinet* C = C->getInstance("George", "Calugareni bl 10");
    int var;
    while (1)
    {
        cout << "1.Info despre toti pacientii\n2.Info despre adulti cu risc ridicat\n3.Info despre copii cu risc ridicat\n4.Info despre pacienti cu un anumit nume\n5.Adauga pacient\n6.Iesi\n";
        cin >> var;
        if (var == 1) C->afiseazaPacienti();
        else if (var == 2) C->afiseazaAdultiRiscRidicat();
        else if (var == 3) C->afiseazaCopiiRiscRidicat();
        else if(var == 4)
        {
            cout << "Introdu numele: ";
            string nume;
            cin >> nume;
            C->afiseazaPacientiNume(nume);
        }
        else if (var == 5)
        {
            cout << "tipul_pacientului date_despre_pacient";
            string tip;
            cin >> tip;
            C->adaugaPacient(tip);
        }
        else break;
    }
    return 0;
}