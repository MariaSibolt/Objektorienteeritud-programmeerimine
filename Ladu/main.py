#include <iostream>
#include "lisad.h"
#include <string>
#include <iomanip>


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

    cout << "\nProgrammi lõpp. Vajuta Enter.\n";
    cin.get();
    
    return 0;
}
