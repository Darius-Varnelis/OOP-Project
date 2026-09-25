#ifndef OOP_PROJECT_UTILS_H
#define OOP_PROJECT_UTILS_H

#include <limits>
#include <string>

constexpr int MIN_PAZ = 0;
constexpr int MAX_PAZ = 10;
constexpr int BE_RIBOS = std::numeric_limits<int>::max();
constexpr int PLOTIS = 20;

// Simbolių (ne baitų) skaičius UTF-8 eilutėje
size_t utf8_ilgis(const std::string& tekstas);

// setw plotis, kompensuojantis daugiabaičius UTF-8 simbolius
int utf8_plotis(const std::string& tekstas);

#endif  // OOP_PROJECT_UTILS_H
