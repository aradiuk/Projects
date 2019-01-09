#include "math_functions.hpp"

double Sqrt(double num)
{
    double error = num * 0.000001;
    double x = num;

    while (x - num / x > error) {
        x = (x + num / x ) / 2;
    }

    return x;
}
