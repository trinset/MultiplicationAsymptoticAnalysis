#ifndef MULTIPLICATIONCOMPARISON_MULTIPLICATOR_H
#define MULTIPLICATIONCOMPARISON_MULTIPLICATOR_H

#include "large-integer.h"

template <int maxDigit = 10>
class Multiplicator
{
public:
    static std::string randomiser(size_t my_size)
    {
        std::string str;

        if (my_size)
        {
            str += (char)(rand() % (maxDigit - 1) + 1 + 48);
        }

        for (size_t i = 1; i < my_size; ++i)
        {
            str += (char)(rand() % maxDigit + 48);
        }

        return str;
    }
public:
    static LargeInteger<maxDigit> schoolMult (const LargeInteger <maxDigit>& num1, const LargeInteger <maxDigit>& num2)
    {
        LargeInteger<maxDigit> temp;

        for (size_t k = 0; k < num2.size(); ++k)
        {
            int carry = 0;

            for (size_t i = 0; i < num1.size(); ++i)
            {
                if (i + k >= temp.size())
                {
                    temp.pushBack((num1.digit(i) * num2.digit(k) + carry) % maxDigit);
                    carry = (num1.digit(i) * num2.digit(k) + carry) / maxDigit;
                }
                else
                {
                    temp[i + k] += num1.digit(i) * num2.digit(k) + carry;
                    carry = temp.digit(i + k) / maxDigit;
                    temp[i + k] %= maxDigit;
                }
            }

            if (carry)
                temp.pushBack(carry);
        }

        return temp;
    }

    static LargeInteger<maxDigit> dacMult(const LargeInteger <maxDigit>& num1, const LargeInteger <maxDigit>& num2)
    {
        if (num1.size() <= 80)
            return schoolMult(num1, num2);

        size_t m = num1.size() / 2;

        /*  Splits numbers into two halves
         * a = <a2, a1>, where a1 * 10^(n/2) and a2
         * b = <b2, b1>, where b1 * 10^(n/2) and b2
         */

        auto a = num1.split(m);
        auto b = num2.split(m);

        LargeInteger<maxDigit> a1b1 = dacMult(a.second, b.second);
        LargeInteger<maxDigit> a1b2 = dacMult(a.second, b.first);
        LargeInteger<maxDigit> a2b1 = dacMult(a.first, b.second);
        LargeInteger<maxDigit> a2b2 = dacMult(a.first, b.first);

        a1b2 += a2b1;
        a1b2.shift(m);
        a1b1.shift(2 * m);

        return a1b1 + a1b2 + a2b2;
    }

    static LargeInteger<maxDigit> karatsubaMult(const LargeInteger<maxDigit>& num1, const LargeInteger<maxDigit>& num2)
    {
        if (num1.size() <= 20)
        {
            return schoolMult (num1, num2);
        }

        size_t m = num1.size () / 2;

        /*  Splits numbers into two halves
         * a = a1 * 10^(n/2) and a2
         * b = b1 * 10^(n/2) and b2
         */

        auto a = num1.split(m);
        auto b = num2.split(m);

        LargeInteger<maxDigit> a1_a2 = a.first + a.second;
        LargeInteger<maxDigit> b1_b2 = b.first + b.second;
        LargeInteger<maxDigit> a1b1 = karatsubaMult(a.second, b.second);
        LargeInteger<maxDigit> a2b2 = karatsubaMult(a.first, b.first);
        LargeInteger<maxDigit> a1_a2b1_b2 = karatsubaMult(a1_a2, b1_b2);

        a1_a2b1_b2 -= a1b1;
        a1_a2b1_b2 -= a2b2;

        a1_a2b1_b2.shift(m);
        a1b1.shift(2 * m);

        return a1b1 + a1_a2b1_b2 + a2b2;

    }
};

#endif //MULTIPLICATIONCOMPARISON_MULTIPLICATOR_H
