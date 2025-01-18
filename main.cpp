#include <iostream>
#include <vector>
#include <string>
#include "BigDigit.h"
#include <cmath>
#include <chrono>


std::string getStringNumber(const long long len)
{
    std::string result;
    for (long long i = 0; i < len; i++) {
        result.push_back(char(48 + rand() % 10));
    }
    return result;
}

std::vector<long long> stringToVector(const std::string str, const long long digitlen)
{
    long long len = str.length();
    std::vector<long long> result(long(std::ceil(len / double(digitlen))), 0);

    for (long long i = 0; i < len / digitlen; i++) {
        result[i] = std::stol(str.substr(len - (i + 1) * digitlen, digitlen));
    }

    if (len % digitlen > 0) {
        result[len / digitlen] = std::stol(str.substr(0, len % digitlen));
    }

    return result;
}

void printVector(const std::vector<long long> vec)
{
    for (long long i = 0; i < vec.size(); i++) std::cout << vec[i] << ' ';
    std::cout << std::endl;
}

long long hashFunction(const std::vector<long long> vec)
{
    long long result = 0;
    long long q = 123456789;
    long long temp;
    for (long long i = 0; i < vec.size(); i++) {
        temp = vec[i];
        while (temp > 0) {
            result += temp % 10;
            result %= q;
            temp /= 10;
        }
        
    }
    return result;
}


int main()
{
    const long long len = 100000;
    const long long tests = 100; //50;
    const long long digit_len = 1;
    const long long base = std::pow(10, digit_len);

        srand(0);
        std::string firstString = getStringNumber(len);
        std::string secondString = getStringNumber(len);
        //std::cout << firstString << " " << secondString << std::endl; //DEBUG
        std::vector<long long> firstVector = stringToVector(firstString, digit_len);
        std::vector<long long> secondVector = stringToVector(secondString, digit_len);
        //printVector(firstVector); //DEBUG
        //printVector(secondVector); //DEBUG

        auto start = std::chrono::high_resolution_clock::now();
        for (long long j = 0; j < tests; j++) {
            std::vector<long long> result =  dftMult(firstVector, secondVector, base);
            //printVector(result); //DEBUG
            //std::cout << i << " | " << "HashSum: " << hashFunction(result) << std::endl; //DEBUG
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - start);
        //std::cout << "---------------------------------------------------" << std::endl;
        //std::cout << "TIME TEST: " << duration.count() / tests << std::endl; //DEBUG
        std::cout << duration.count() / tests << std::endl;

    return 0;
}