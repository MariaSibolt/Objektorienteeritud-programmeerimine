#include <iostream>
#include "loomad.h"
#include "klassid.h"

using namespace std;

int main()
{ 
    Metsis* metsis1 = new Metsis("Metsis1", 6, 30);
    Hunt* hunt1 = new Hunt("Hunt1", 60, 50);
    Hirv* hirv1 = new Hirv("Hirv1", 60, 50);

    Rebane* rebane1 = new Rebane("Rebane1", 25, 60);

    Karu* karu1 = new Karu("Karu1", 300, 40);
    Hunt* hunt2 = new Hunt("Hunt2", 65, 50);

    cout << "Loomade kohtumised:";

    
    metsis1->kohtub(hunt1);
    metsis1->kohtub(hirv1);
    hunt2->kohtub(hunt1);
    rebane1->kohtub(karu1);

    delete metsis1;
    delete hunt1;
    delete rebane1;
    delete karu1;
    delete hunt2;

    return 0;
}
