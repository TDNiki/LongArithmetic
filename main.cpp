#include <iostream>
#include <vector>
#include <string>
#include <cmath>


std::string getStringNumber(const long len)
{
    std::string result;
    for (long i = 0; i < len; i++) {
        result.push_back(char(48 + rand() % 10));
    }
    return result;
}

std::vector<long> stringToVector(const std::string str, const long digitlen)
{
    long len = str.length();
    std::vector<long> result(long(std::ceil(len / double(digitlen))), 0);

    for (long i = 0; i < len / digitlen; i++) {
        result[i] = std::stol(str.substr(len - (i + 1) * digitlen, digitlen));
    }

    if (len % digitlen > 0) {
        result[len / digitlen] = std::stol(str.substr(0, len % digitlen));
    }

    return result;
}

void printVector(const std::vector<long> vec)
{
    for (long i = 0; i < vec.size(); i++) std::cout << vec[i] << ' ';
    std::cout << std::endl;
}

long hashFunction(const std::vector<long> vec)
{
    long result = 0;
    long q = 123456789;
    long temp;
    for (long i = 0; i < vec.size(); i++) {
        temp = vec[i];
        while (temp > 0) {
            result += temp % 10;
            result %= q;
            temp /= 10;
        }
        
    }
    return result;
}

std::vector<long> karatsubaMult(std::vector<long> &first, std::vector<long> &second, const long base)
{
    
    const long len1 = first.size();
    const long len2 = first.size();
    long len = std::max(len1, len2); // Все будет относительно максимального числа
    // Если длина числа нечетная, то нужно довести до четного состояния
    len = len % 2 == 0 ? len : len + 1;

    // Далее идет алгоритм из разряда разделяй и властвуй.
    /*Для маленьких чисел данный алгоритм не имеет смысла, т.к. даже наивный алгоритм целесообразнее (быстрее)*/
    if (len <= 10) return naiveMult(first, second, base); // Литерал нужно подобрать, протестировав данные

    //13-19
}

std::vector<long> naiveMult(std::vector<long> &first, std::vector<long> &second, const long base)
// Перемножение столбиком
{
    const long len1 = first.size();
    const long len2 = second.size();
    std::vector<long> result(len1 + len2, 0);

    for (long i = 0; i < len1; i++) {
        for (long j = 0; j < len2; j++) {
            result[i + j] += first[i] * second[j];
            result[i + j + 1] += result[i + j] / base;
            result[i + j] %= base;
        }
    }

    while (result[result.size() - 1] == 0) result.pop_back(); // Убиравет нули с конца, странно, надо узнать зачем
    return result;
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
    std::vector<long> result =  naiveMult(firstVector, secondVector, base);
    printVector(result);
    std::cout << hashFunction(result);

    return 0;
}