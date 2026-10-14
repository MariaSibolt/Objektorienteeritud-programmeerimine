#include <iostream>
#include "lisad.h"
#include <string>
#include <iomanip>
#include "stock.h"


using namespace std;

int main()
{
    Item* i1 = new Item("Leib", 1.30);
    Item* i2 = new Item("Piim", 2.5);
    Item* i3 = new Item("Vorst", 3.5);
    Item* i4 = new Item("Leib", 0.9);

    cout << i1->string_out() << endl;
    cout << i2->string_out() << endl;

    
    cout << "leib vs piim"
         << (i1->equals(i2) ? " on sama" : " ei ole sama")
         << endl;

    cout << "leib vs leib"
         << (i1->equals(i4) ? " on sama" : " ei ole sama")
         << endl;

    
    Order* tellimus1 = new Order();

    cout << "\nKauba lisamine tellimusse\n";

    if (tellimus1->add_line(i1, 3))
        cout << "Leib lisatud\n";

    if (tellimus1->add_line(i2, 5))
        cout << "Piim lisatud\n";

    if (tellimus1->add_line(i3, 1))
        cout << "Vorst lisatud\n";

    cout << "\nNegatiivse koguse test\n";

    if (tellimus1->add_line(i1, -5))
        cout << "Lisamine õnnestus\n";
    else
        cout << "Viga: negatiivne kogus ei ole lubatud\n";

    
    cout << "\nTellimuse sisu:\n";
    cout << tellimus1->string_out() << endl;

    
    Order* tellimus2 = new Order();

    if (tellimus2->add_line(i2, 5))
        cout << "Piim lisatud\n";

    if (tellimus2->add_line(i3, 1))
        cout << "Vorst lisatud\n";

    cout << "\nNegatiivse koguse test\n";

    if (tellimus2->add_line(i1, -5))
        cout << "Lisamine õnnestus\n";
    else
        cout << "Viga: negatiivne kogus ei ole lubatud\n";

    cout << "\nTeine tellimus:\n";
    cout << tellimus2->string_out() << endl;
    
    Stock warehouse;
    
    Order* stock_add = new Order();
    stock_add->add_line(i1, 50); // 50 leiba
    stock_add->add_line(i2, 30); // 30 piima
    stock_add->add_line(i3, 25); // 25 vorsti


    warehouse.add(stock_add);
    cout << "Algne laoseis:\n";
    cout << warehouse.string_out() << endl;


    warehouse.remove(tellimus1);
    warehouse.remove(tellimus2);


    cout << "Laoseis peale klientide tellimusi:\n";
    cout << warehouse.string_out() << endl;


    warehouse.thief(i2, 4);
    cout << "Peale vargust:\n";
    cout << warehouse.string_out() << endl;

    if (warehouse.check_stock())
    {
        cout << "Laoseis on korrektne\n";
    }

    else
    {
        cout << "Laoseis EI OLE korrektne\n";
    }

    cout << "\nProgrammi lõpp. Vajuta Enter.\n";
    cin.get();
    
    return 0;
}
