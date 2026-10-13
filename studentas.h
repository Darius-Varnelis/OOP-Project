#ifndef OOP_PROJECT_STUDENTAS_H
#define OOP_PROJECT_STUDENTAS_H

#include <algorithm>
#include <list>
#include <numeric>
#include <string>
#include <vector>

enum class Rusiuoti{Varda,Pavarde,Pazymi};
enum class Struktura{Vector,List};
enum class Rezimas{Ranka,Failas,Generavimas, Benchmark};
enum class Statistika {Mediana, Vidurkis, Abu};
enum class Isvedimas {Konsole, Failas};
constexpr double ISLAIKYMO_RIBA = 5.0;

struct Studentas {
    std::string vardas, pavarde;
    std::vector<int> paz;
    int exam = 0;
    double galutinis = 0.0;
};


void skaiciuotiGalutini(Studentas& st);
template <typename Konteineris>
void rusiuotiStudentus(Konteineris& grupe, Rusiuoti r) {
    auto cmp = [r](const Studentas& a, const Studentas& b) {
        switch (r) {
            case Rusiuoti::Varda:    return a.vardas < b.vardas;
            case Rusiuoti::Pavarde:   return a.pavarde < b.pavarde;
            case Rusiuoti::Pazymi: return a.galutinis < b.galutinis;
        }
        return false;
    };
    if constexpr (std::is_same_v<Konteineris, std::list<Studentas>>) {
        grupe.sort(cmp);
    }
    else {
        std::sort(grupe.begin(), grupe.end(), cmp);
    }
}

template <typename Konteineris>
void skirstytiStudentus(Konteineris& grupe, Konteineris& nuskriaustukai, Konteineris& kietukai) {
    for (Studentas& st : grupe) {
        (st.galutinis < ISLAIKYMO_RIBA ? nuskriaustukai : kietukai).push_back(std::move(st));
    }
}

#endif  // OOP_PROJECT_STUDENTAS_H
