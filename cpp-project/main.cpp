#include <vector>
#include "multiplicator.h"

template <int maxDigit = 10>
double measureTime(LargeInteger<maxDigit> algo(const LargeInteger<maxDigit>&, const LargeInteger<maxDigit>&),
                   const LargeInteger<maxDigit>& first, const LargeInteger<maxDigit>& second, short times)
{
    /*  Function to measure time of a test
     *  Tests all of the given algorithms
     *  Uses QueryPerformance to maximize accuracy on small numbers
     */

    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    LARGE_INTEGER start, end;
    double time = 0;

    for (short i = 0; i < times; ++i)
    {
        QueryPerformanceCounter(&start);
        LargeInteger<maxDigit> res = algo(first, second);
        QueryPerformanceCounter(&end);
        time += static_cast<double>(end.QuadPart - start.QuadPart) / 10000;
    }

    return time / times;
}

void research(size_t testSize)
{
    /*  Tests runtime of the given algorithms
     *  Uses cases of number of digits up to size testSize
     *  Writes data to the .csv file for further inspections
     */

    std::ofstream file;
    file.open("../../tables/testResults.csv");
    file << "Size," << "schoolMult," << "dacMult," << "karatsubaMult" << std::fixed << std::endl;

    //    log step + last number
    for (size_t num = 1; num <= testSize; num == testSize || num * 2 < testSize ? num *= 2 : num = testSize)
    {
        std::cout << num << std::endl;

        file << num << ',';

        std::string str1 = Multiplicator<>::randomiser(num);
        std::string str2 = Multiplicator<>::randomiser(num);

        LargeInteger<> first(str1);
        LargeInteger<> second(str2);

        file << measureTime<>(Multiplicator<>::schoolMult, first, second, 3) << ',';
        file << measureTime<>(Multiplicator<>::dacMult, first, second, 3) << ',';
        file << measureTime<>(Multiplicator<>::karatsubaMult, first, second, 3) << std::endl;
    }

    file.close();
}

void binaryTest()
{
    //  Simple test for non-decimal numbers

    std::string str1 = "101101101101";
    std::string str2 = "101001100011";
    std::string strRes = "11101101010110100100111";

    LargeInteger<2> first(str1);
    LargeInteger<2> second(str2);
    LargeInteger<2> resMult(strRes);

    LargeInteger<2> res1 = Multiplicator<2>::schoolMult(first,second);
    LargeInteger<2> res2 = Multiplicator<2>::dacMult(first, second);
    LargeInteger<2> res3 = Multiplicator<2>::karatsubaMult(first, second);

    if (res1 == resMult && res2 == resMult && res3 == resMult)
        std::cout << "Passed! Result is:\n" << res3 << std::endl;
    else
        std::cout << "Error!\n";
}

void realTest()
{
    /*  Test with a special .csv with 1000 randomly generated tests
     *  .csv has 3 columns: first number, second number, result of their multiplication
     *  .csv was created in python, where integers don't have size limits
     *  That's why tests are claimed to be true/real
     */

    std::ifstream file;
    file.open("../../tables/realTest.csv");

    std::string str1, str2, strRes;

    while (getline(file, str1, ',') && getline(file, str2, ',') && getline(file, strRes))
    {
        LargeInteger<> first(str1);
        LargeInteger<> second(str2);
        LargeInteger<> res(strRes);

        LargeInteger<> res1 = Multiplicator<>::schoolMult(first,second);
        LargeInteger<> res2 = Multiplicator<>::dacMult(first, second);
        LargeInteger<> res3 = Multiplicator<>::karatsubaMult(first, second);

        if (res1 != res2 || res2 != res3 || res1 != res)
        {
            std::cout << "Error!\n";
            return;
        }
    }

    std::cout <<"Real test is passed!\n";

    file.close();
}

void randomTest(const int numOfDigits)
{
    /* Tests the behaviour of functions
     * for a given number of digits
     */

    std::string str1 = Multiplicator<>::randomiser(numOfDigits);
    std::string str2 = Multiplicator<>::randomiser(numOfDigits);

    LargeInteger<> first(str1);
    LargeInteger<> second(str2);

    LargeInteger<> res1 = Multiplicator<>::schoolMult(first,second);
    LargeInteger<> res2 = Multiplicator<>::dacMult(first, second);
    LargeInteger<> res3 = Multiplicator<>::karatsubaMult(first, second);

    if (res1 == res2 && res2 == res3 && res1 == res3)
        std::cout << "Passed! Result is:\n" << res1 << '\n';
    else
        std::cout << "Error!\n";
}

void customTest()
{
    /*  A template for a test
    *   Choose any base(put a number inside <>)
    *   Decide, whether you want a number to be random
    */

    std::cout << "I created a test!\n";

    std::string str1 = "12345"; /*Multiplicator<>::randomiser(numOfDigits);*/
    std::string str2 = "54321"; /*Multiplicator<>::randomiser(numOfDigits);*/

    LargeInteger<6> first(str1);
    LargeInteger<6> second(str2);

    LargeInteger<6> res1 = Multiplicator<6>::schoolMult(first,second);
    LargeInteger<6> res2 = Multiplicator<6>::dacMult(first, second);
    LargeInteger<6> res3 = Multiplicator<6>::karatsubaMult(first, second);

    std::cout << res1 << std::endl;
}



int main()
{
    std::srand(time(nullptr));  //  creates a seed for randomizing

    binaryTest();
    randomTest(100);
    customTest();
    realTest();    //   Takes some time to do, see its description

    research(500);
}

