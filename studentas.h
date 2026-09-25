#ifndef OOP_PROJECT_STUDENTAS_H
#define OOP_PROJECT_STUDENTAS_H

#include <string>
#include <vector>

constexpr double ISLAIKYMO_RIBA = 5.0;

struct studentas {
    std::string vardas, pavarde;
    std::vector<int> paz;
    int exam = 0;
    double galutinis = 0.0;
};

double vidurkis(const std::vector<int>& paz);
void skaiciuotiGalutini(studentas& st);

#endif  // OOP_PROJECT_STUDENTAS_H
