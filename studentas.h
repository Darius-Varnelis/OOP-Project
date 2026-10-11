#ifndef OOP_PROJECT_STUDENTAS_H
#define OOP_PROJECT_STUDENTAS_H

#include <numeric>
#include <string>
#include <vector>

enum class Rusiuoti{Varda,Pavarde,Pazymi};
enum class Struktura{Vector,List};
constexpr double ISLAIKYMO_RIBA = 5.0;

struct Studentas {
    std::string vardas, pavarde;
    std::vector<int> paz;
    int exam = 0;
    double galutinis = 0.0;
};


void skaiciuotiGalutini(Studentas& st);
void rusiuotiStudentus(std::vector<Studentas>& grupe, Rusiuoti r);
void skirstytiStudentus(std::vector<Studentas>& grupe, std::vector<Studentas>& nuskriaustukai, std::vector<Studentas>& kietukai);

#endif  // OOP_PROJECT_STUDENTAS_H
