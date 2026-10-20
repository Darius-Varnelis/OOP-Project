
#ifndef OOP_PROJECT_RESULTS_H
#define OOP_PROJECT_RESULTS_H
#include <string>
#include <vector>

struct Rezultatai {
    int dydis;
    std::vector<double> nuskaitymai, galutiniai, rusiavimai, dalijimaiMano, dalijimai1, dalijimai2, isvedimaiNuskriaustuku, isvedimaiKietuku,
        bendri;
};
void spausdintiLentele(const std::string& filename, const std::vector<Rezultatai>& visi);

#endif  // OOP_PROJECT_RESULTS_H
