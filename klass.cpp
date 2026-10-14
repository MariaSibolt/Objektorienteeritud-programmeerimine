#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

class Ristkülik {
private:
    double pikkus;
    double laius;

public:
    Ristkülik(double p, double l) {
        pikkus = p;
        laius = l;
    }

    double getPikkus() const {
        return pikkus;
    }

    double getLaius() const {
        return laius;
    }

    double pindala() const {
        return pikkus * laius;
    }
};

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    vector<Ristkülik> ristkülikud;
    int valik;

    while (true) {
        cout << "\nVali tegevus:\n";
        cout << "1. Loo ristkülik\n";
        cout << "2. Loetle loodud ristkülikud\n";
        cout << "3. Kustuta ristkülikud\n";
        cout << "Sinu valik: ";
        cin >> valik;

        if (valik == 1) {
            double pikkus, laius;

            cout << "Sisesta pikkus: ";
            cin >> pikkus;

            cout << "Sisesta laius: ";
            cin >> laius;

            Ristkülik r(pikkus, laius);
            ristkülikud.push_back(r);

            cout << "Ristkülik loodud.\n";
        }

        else if (valik == 2) {
            if (ristkülikud.empty()) {
                cout << "Ristkülikuid ei ole loodud.\n";
            } else {
                for (int i = 0; i < (int)ristkülikud.size(); i++) {
                    cout << i + 1 << ". ristkülik: ";
                    cout << "pikkus = " << ristkülikud[i].getPikkus();
                    cout << ", laius = " << ristkülikud[i].getLaius();
                    cout << ", pindala = " << ristkülikud[i].pindala() << endl;
                }
            }
        }

        else if (valik == 3) {
            if (ristkülikud.empty()) {
                cout << "Ristkülikuid ei ole, mida kustutada.\n";
            } else {
                double piir;

                cout << "Sisesta pindala piir: ";
                cin >> piir;

                for (int i = (int)ristkülikud.size() - 1; i >= 0; i--) {
                    if (ristkülikud[i].pindala() > piir) {
                        ristkülikud.erase(ristkülikud.begin() + i);
                    }
                }
            }
        }

        else {
            cout << "Vale valik.\n";
        }
    }

    return 0;
}