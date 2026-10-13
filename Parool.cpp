#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    string parool = "salakala";
    string sisestus;
    int katsed = 3;

    while (katsed > 0) {
        cout << "Sisestage parool: ";
        cin >> sisestus;

        if(sisestus == parool) {
            cout << "Parool on õige" << endl;
            return 0;
        } 
        else {
            katsed--;

            if(katsed > 0) {
                cout << "Vale parool. Katseid järel: "
                     << katsed << endl;
            }
            else {
                cout << "Lukus. Liiga palju valesid katseid." << endl;
            }
        }
    }
    return 0;
}