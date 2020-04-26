#ifndef MULTIPLICATIONCOMPARISON_LARGEINTEGER_H
#define MULTIPLICATIONCOMPARISON_LARGEINTEGER_H

#include <iostream>
#include <cstddef>
#include <string>
#include <fstream>
#include <deque>
#include <windows.h>
#include <algorithm>
#include <ctime>
#include <random>

template <int maxDigit = 10>
class LargeInteger
{
public:
    LargeInteger() = default;

    explicit LargeInteger(std::deque<int>& other)
    {
        _digits = other;
    }

    explicit LargeInteger(const std::deque<int>& other)
    {
        _digits = other;
    }

    explicit LargeInteger(std::string& str)
    {
        std::reverse(str.begin(), str.end());

        for (char elem : str)
        {
            _digits.push_back(elem - '0');
        }
    }

    explicit LargeInteger(const std::string& str)
    {
        std::string temp = str;
        std::reverse(temp.begin(), temp.end());

        for (char elem : temp)
        {
            _digits.push_back(elem - '0');
        }
    }
public:
    LargeInteger<maxDigit> operator+=(const LargeInteger<maxDigit>& other)
    {
        if (size() < other.size())
        {
            _digits.resize(other.size(), 0);
        }

        int carry = 0;
        size_t i = 0;

        for (; i < other.size(); ++i)
        {
            int sum = digit(i) + other.digit(i) + carry;
            int new_digit = sum % maxDigit;
            _digits[i] = new_digit;
            carry = sum / maxDigit;
        }

        while (carry)
        {
            if (i < size())
            {
                int sum = digit(i) + carry;
                int new_digit = sum % maxDigit;
                _digits[i] = new_digit;
                carry = sum / maxDigit;
            }
            else
            {
                _digits.push_back(carry);
                carry = 0;
            }
            ++i;
        }

        return *this;
    }

    LargeInteger<maxDigit> operator+(const LargeInteger<maxDigit>& other) const
    {
        LargeInteger<maxDigit> res = *this;
        res += other;
        return res;
    }

    LargeInteger<maxDigit>& operator-=(const LargeInteger<maxDigit>& other)
    {
        int carry = 0;
        size_t i = 0;

        for (; i < other.size(); ++i)
        {
            _digits[i] = _digits[i] + carry - other._digits[i];
            if (_digits[i] < 0)
            {
                carry = -1;
                _digits[i] += maxDigit;
            }
            else
            {
                carry = 0;
            }
        }

        for (;i<size() && carry; ++i)
        {
            _digits[i] += carry;
            if (_digits[i] < 0)
            {
                carry = -1;
                _digits[i] += maxDigit;
            }
            else
            {
                carry = 0;
            }
        }

        return *this;
    }

    LargeInteger<maxDigit> operator- (const LargeInteger<maxDigit>& other) const
    {
        LargeInteger<maxDigit> res = *this;
        res -= other;
        return res;
    }

    bool operator==(const LargeInteger<maxDigit>& other)
    {
        if (size() != other.size())
        {
            return false;
        }

        for (size_t i = 0; i < size(); ++i)
        {
            if (_digits[i] != other._digits[i])
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const LargeInteger<maxDigit>& other)
    {
        return !(*this == other);
    }

    int& operator[](size_t index)
    {
        return _digits[index];
    }

    const int& operator[](size_t index) const
    {
        return _digits[index];
    }

    friend std::ostream& operator<< (std::ostream& out, const LargeInteger<maxDigit>& num)
    {
        for (size_t i = 0; i < num.size(); ++i)
        {
            out << num.digit(num.size() - i - 1);
        }

        return out;
    }
public:
    std::pair<LargeInteger<maxDigit>, LargeInteger<maxDigit>> split(size_t cut_size) const
    {
        LargeInteger<maxDigit> a(std::deque<int>(_digits.begin(), _digits.begin() + cut_size));
        LargeInteger<maxDigit> b(std::deque<int>(_digits.begin() + cut_size, _digits.end()));

        if (a.size() > b.size())
        {
            b._digits.push_back(0);
        }
        else if(b.size() > a.size())
        {
            a._digits.push_back(0);
        }

        return std::make_pair(a, b);
    }

    void shift(size_t pwr)    //  an alternative to multiplying by 10^pwr
    {
        for (size_t i = 0; i < pwr; ++i)
        {
            _digits.push_front(0);
        }
    }

    void pushBack(int digit)
    {
        _digits.push_back(digit);
    }
public:
    int digit(size_t index) const
    {
        return _digits[index];
    }

    size_t size() const
    {
        return _digits.size();
    }
private:
    std::deque<int> _digits; //    reversed order, i.e. 123 = {3, 2, 1}
};

#endif //MULTIPLICATIONCOMPARISON_LARGEINTEGER_H
