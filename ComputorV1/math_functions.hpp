#ifndef MATH_FUNCTIONS_HPP_
#define MATH_FUNCTIONS_HPP_

template<class T>
T Pow(T num, int pow)
{
    T result = 1;

    while (pow > 0) {
        result *= num;
        --pow;
    }

    return result;
}

double Sqrt(double num);

#endif /* MATH_FUNCTIONS_HPP_ */
