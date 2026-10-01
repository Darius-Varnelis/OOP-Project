#ifndef OOP_PROJECT_UTILS_H
#define OOP_PROJECT_UTILS_H

#include <limits>
#include <numeric>
#include <string>
#include <vector>

constexpr int MIN_PAZ = 0;
constexpr int MAX_PAZ = 10;
constexpr int BE_RIBOS = std::numeric_limits<int>::max();
constexpr int PLOTIS = 20;

// Simbolių (ne baitų) skaičius UTF-8 eilutėje
size_t utf8Ilgis(const std::string& tekstas);

// setw plotis, kompensuojantis daugiabaičius UTF-8 simbolius
int utf8Plotis(const std::string& tekstas);

// Skaičiaus įvedimas per konsolę
int ivestiSk(const std::string& klausimas, int nuo, int iki);

// Funkcija, gražinanti loginę reikšmę taip ar ne klausimui
bool taipArNe(const std::string& klausimas);

template <typename T>
double vidurkis(const std::vector<T>& v) {
    if (v.empty()) return 0.0;
    return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}


#endif  // OOP_PROJECT_UTILS_H
