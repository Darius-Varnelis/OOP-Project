#ifndef OOP_PROJECT_STUDENTAS_H
#define OOP_PROJECT_STUDENTAS_H

#include <numeric>
#include <string>
#include <vector>

enum class Rusiuoti{Varda,Pavarde,Pazymi};
constexpr double ISLAIKYMO_RIBA = 5.0;

struct studentas {
    std::string vardas, pavarde;
    std::vector<int> paz;
    int exam = 0;
    double galutinis = 0.0;
};

template <typename T>
double vidurkis(const std::vector<T>& v) {
    if (v.empty()) return 0.0;
    return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}
void skaiciuotiGalutini(studentas& st);
void rusiuotiStudentus(std::vector<studentas>& grupe, Rusiuoti& r);

#endif  // OOP_PROJECT_STUDENTAS_H
