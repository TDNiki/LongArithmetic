#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>


std::string getStringNumber(const long len)
{
    std::string result;
    for (long i = 0; i < len; i++) {
        result.push_back(char(48 + rand() % 10));
    }
    return result;
}

std::vector<long> stringToVecotr(const std::string str, const long digitlen)
{
    long len = str.length();
    std::vector<long> result(len / digitlen, 0);

}


int main()
{
    srand(0);

    long len = 4;
    std::string firstString = getStringNumber(len);
    std::string secondString = getStringNumber(len);
    std::cout << firstString << " " << secondString << std::endl;

    int digit_len = 2;
    std::vector<long> firstVector = stringToVector(firstString, digit_len);
    std::vector<long> secondVector = stringToVector(secondString, digit_len);
    printVector(firstVector);
    printVector(secondVector);

    long base = std::pow(10, digit_len);
    std::vector<long> result naiveMult(firstVector, secondVector, base);
    printVector(result);
    std::cout << hashFunction(result);

    return 0;
}