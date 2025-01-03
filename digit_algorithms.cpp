#include <vector>

std::vector<long long> add(std::vector<long long> &first, std::vector<long long> &second, const long long base)
// Суммирование
{
    const long long len1 = first.size();
    const long long len2 = first.size();
    long long len = std::max(len1, len2);
    std::vector<long long> result(first);
    result.resize(len + 1, 0);
    for (long long i = 0; i < len2; i++) {
        result[i] += second[i];
        result[i + 1] += result[i] / base;
        result[i] %= base;
    }

    while (result[result.size() - 1] == 0) result.pop_back();

    return result;
}

std::vector<long long> sub(std::vector<long long> &first, std::vector<long long> &second, const long long base)
// Вычитание
{
    const long long len1 = first.size();
    const long long len2 = first.size();
    std::vector<long long> result(first);
    for (long long i = 0; i < len1 - 1; i++) {
        result[i] += base - (i < len2 ? second[i] : 0);
        result[i + 1] += result[i] / base - 1;
        result[i] %= base;
    }
    result[len1 - 1] -= (len1 - 1 < len2 ? second[len1 - 1] : 0);
    while (result[result.size() - 1] == 0) result.pop_back();

    return result;
}



std::vector<long long> naiveMult(std::vector<long long> &first, std::vector<long long> &second, const long long base)
// Перемножение столбиком
{
    const long long len1 = first.size();
    const long long len2 = second.size();
    std::vector<long long> result(len1 + len2 + 1, 0);

    for (long long i = 0; i < len1; i++) {
        for (long long j = 0; j < len2; j++) {
            result[i + j] += first[i] * second[j];
            result[i + j + 1] += result[i + j] / base;
            result[i + j] %= base;
        }
    }

    while (result[result.size() - 1] == 0) result.pop_back(); // Убирает нули с конца

    return result;
}

std::vector<long long> karatsubaMult(std::vector<long long> &first, std::vector<long long> &second, const long long base)
// Метод карацубы
{
    
    const long long len1 = first.size();
    const long long len2 = first.size();
    long long len = std::max(len1, len2); // Все будет относительно максимального числа
    // Если длина числа нечетная, то нужно довести до четного состояния
    len = (len % 2 == 0) ? len : len + 1;

    // Далее идет алгоритм из разряда разделяй и властвуй.
    /*Для маленьких чисел данный алгоритм не имеет смысла, т.к. даже наивный алгоритм целесообразнее (быстрее)*/
    if (len <= 10) return naiveMult(first, second, base); // Литерал нужно подобрать, протестировав данные

    long long halflen = len / 2;
    std::vector<long long> firstLow(first); // малый разряд, наполняем разрядами из числа first
    firstLow.resize(halflen, 0); // Оставляем только пол массива, заполняем нулями
    std::vector<long long> SecondLow(second); // малый разряд
    SecondLow.resize(halflen, 0);
    std::vector<long long> FirstHigh(len1 > halflen ? first.begin() + halflen : first.end(), first.end()); // Старший разряд, нужно начать с половинки, для этого надо проверить
    FirstHigh.resize(halflen, 0);
    std::vector<long long> SecondHigh(len2 > halflen ? second.begin() + halflen : second.end(), second.end()); // Старший разряд, нужно начать с половинки, для этого надо проверить
    SecondHigh.resize(halflen, 0);

    std::vector<long long> multLow = karatsubaMult(firstLow, SecondLow, base);
    std::vector<long long> multHigh = karatsubaMult(FirstHigh, SecondHigh, base);

    std::vector<long long> firstSum = add(firstLow, FirstHigh, base);
    std::vector<long long> SecondSum = add(SecondLow, SecondHigh, base);

    std::vector<long long> multMid = karatsubaMult(firstSum, SecondSum, base);

    multMid = sub(multMid, multLow, base);
    multMid = sub(multMid, multHigh, base);

    std::vector<long long> result(2 * len, 0);

    for (long long i = 0; i < 2 * len - 1; i++) {
        result[i] += (i < multLow.size()) ? multLow[i] : 0;
        result[i] += (i >= halflen && i < halflen + multMid.size()) ? multMid[i - halflen] : 0;
        result[i] += (i >= len && i < len + multHigh.size()) ? multHigh[i - len] : 0;
        result[i + 1] += result[i] / base;
        result[i] %= base;
    }

    result[2 * len - 1] += multHigh[len - 1];
    while (result[result.size() - 1] == 0) result.pop_back();

    return result;
}