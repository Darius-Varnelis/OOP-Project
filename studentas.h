#ifndef OOP_PROJECT_STUDENTAS_H
#define OOP_PROJECT_STUDENTAS_H

#include <algorithm>
#include <list>
#include <numeric>
#include <string>
#include <type_traits>
#include <vector>

#include "nustatymai.h"
#include "utils.h"

constexpr double ISLAIKYMO_RIBA = 5.0;

template <template <typename...> class Konteineris>
struct Studentas {
    std::string vardas, pavarde;
    Konteineris<int> paz;
    int exam = 0;
    double galutinis = 0.0;
};
template <template <typename...> class Konteineris>
void skaiciuotiGalutini(Studentas<Konteineris>& st) {
    st.galutinis = 0.4 * vidurkis(st.paz) + 0.6 * st.exam;
}
template <template <typename...> class Konteineris>
void rusiuotiStudentus(Konteineris<Studentas<Konteineris>>& grupe, Rusiuoti r, Tvarka t) {
    auto maziau = [r](const Studentas<Konteineris>& a, const Studentas<Konteineris>& b) {
        switch (r) {
            case Rusiuoti::Varda:   return a.vardas < b.vardas;
            case Rusiuoti::Pavarde: return a.pavarde < b.pavarde;
            case Rusiuoti::Pazymi:  return a.galutinis < b.galutinis;
        }
        return false;
    };
    auto cmp = [maziau, t](const Studentas<Konteineris>& a, const Studentas<Konteineris>& b) {
        return t == Tvarka::Didejimo ? maziau(a, b) : maziau(b, a);
    };
    if constexpr (std::is_same_v<Konteineris<int>, std::list<int>>) {
        grupe.sort(cmp);
    } else {
        std::sort(grupe.begin(), grupe.end(), cmp);
    }
}

template <template <typename...> class Konteineris>
void skirstytiStudentus(Konteineris<Studentas<Konteineris>>& grupe, Konteineris<Studentas<Konteineris>>& nuskriaustukai,
                        Konteineris<Studentas<Konteineris>>& kietukai) {
    for (auto& st : grupe) {
        (st.galutinis < ISLAIKYMO_RIBA ? nuskriaustukai : kietukai).push_back(std::move(st));
    }
}

#endif  // OOP_PROJECT_STUDENTAS_H
