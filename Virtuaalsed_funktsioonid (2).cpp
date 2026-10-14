#include <iostream>
#include <string>
using namespace std;


class Vehicle { 
public:

    //mitte-virtuaalne funktsioon
    void type() {
        cout << "  Vehicle::type (ei ole virtuaalne) -> Üldine sõiduk\n"; //kutsutakse Vehicle::type(), sest arr on Vehicle* tüüpi pointerite massiiv (arr[i]->type();).
    }

    //virtuaalne funktsioon
    virtual void move() {
        cout << "  Vehicle::move (virtuaalne fn) -> Liigub\n"; //kutsutakse objekti tegeliku klassi funktsioon, (Auto::move, Rong::move, Mootorratas::move, Vehicle::move), (arr[i]->move();).
    }

    virtual ~Vehicle() = default;
};

class Auto : public Vehicle { 
public:
    Auto() = default;

    void type() {
        cout << "  Auto::type (ei ole virtuaalne) -> Auto\n";
    }

    void move() override {
        cout << "  Auto::move (virtuaalne fn) -> Maanteel\n";
    }
};

class Rong : public Vehicle {
public:
    Rong() = default;

    void type() {
        cout << "  Rong::type (ei ole virtuaalne) -> Rong\n";
    }

    void move() override {
        cout << "  Rong::move (virtuaalne fn) -> Raudteel\n";
    }
};

class Mootorratas : public Vehicle {
public:
    Mootorratas() = default;

    void type() {
        cout << "  Mootorratas::type (ei ole virtuaalne) -> Mootorratas\n";
    }

    void move() override {
        cout << "  Mootorratas::move (virtuaalne fn) -> Sõiduteel\n";
    }
};

int main() {

    Auto Auto;
    Rong Rong;
    Vehicle vehicle;
    Mootorratas Mootorratas;

    // Vehicle tüüpi pointerite massiiv
    Vehicle* arr[] = { &Auto, &Rong, &Mootorratas, &vehicle };

    string names[] = { "Auto", "Rong", "Mootorratas", "Vehicle" };

    cout << "=== Funktsioonide kutsumine Vehicle* pointerite kaudu ===\n\n";

    for (int i = 0; i < 4; ++i) {

        cout << names[i] << " funktsioonide kutsumine Vehicle* pointeri kaudu:\n";

        cout << "esmalt mittevirtuaalne, siis virtuaalne\n";

        //mitte-virtuaalne funktsioon. Alati kutsutakse Vehicle::type(), nagu enne mainitud
        arr[i]->type();

        //virtuaalne funktsioon. Kutsutakse objekti tegeliku klassi funktsioon, nagu enne mainitud
        arr[i]->move();

        cout << "\n";
    }

    cout << "=== Otse objektidelt kutsumine ===\n\n";

    //kutsutakse funktsioone otse objektist, seega kasutatakse alati selle objekti enda funktsioone

    cout << "Auto.type():            "; Auto.type();
    cout << "Auto.move():            "; Auto.move();

    cout << "\n";

    cout << "Rong.type():          "; Rong.type();
    cout << "Rong.move():          "; Rong.move();

    cout << "\n";
    
    cout << "Mootorratas.type():        "; Mootorratas.type();
    cout << "Mootorratas.move():        "; Mootorratas.move();

    cout << "\n";

    cout << "vehicle.type():        "; vehicle.type();
    cout << "vehicle.move():        "; vehicle.move();

    cout << "\n";

    return 0;
}