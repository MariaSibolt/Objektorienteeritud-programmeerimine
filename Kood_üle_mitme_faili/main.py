#include <iostream>
#include "utils_lib.h"

using namespace std;

int main() {
    cout << "max(3,7)=" << utils::max(3, 7) << endl;
    cout << "max(2.5, 1.2)=" << utils::max(2.5, 1.2) << endl;

    cout << "power(5)=" << utils::power(5) << endl;
    cout << "power(2, 5)=" << utils::power(2, 5) << endl;

    for (int i = 1; i <= 10; i++){
        cout << i << "isEven?";

        if (utils::isEven(i)) {
            cout << "true" << endl;
        }else {
            cout << "false" << endl;
        }
    }
    return 0;
}
