#include "utils_lib.h"

namespace utils {
    int max(int a, int b){
        if (a>b){
            return a;
        }
        return b;
    }
    double max(double a, double b){
        if(a>b){
            return a;
        }
        return b;
    }
    int power(int base, int exponent){
        int result =1;

        for (int i=0; i < exponent; i++){
            result = result * base;
        }
        return result;
    }   
    bool isEven(int number){
        return number % 2 == 0;
    }
}