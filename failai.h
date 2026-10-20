#ifndef OOP_PROJECT_FAILAI_H
#define OOP_PROJECT_FAILAI_H

#include <iomanip>
#include <ios>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <type_traits>

#include "studentas.h"
#include "utils.h"

std::string failoPavadinimas(const std::string& pradzia, const int& n);

void generuotiFaila(const int& n);
void rasytiAntraste(std::ostream& out);
template <template <typename...> class Konteineris>
void rasytiStudenta(std::ostream& out, const Studentas<Konteineris>& st) {
    out << std::left << std::setw(utf8Plotis(st.vardas)) << st.vardas << "|";
    out << std::setw(utf8Plotis(st.pavarde)) << st.pavarde << "|";
    out << std::left << std::setw(PLOTIS) << st.galutinis << "|\n";
}
void trintiFaila(const std::string& fileName) ;

template <template <typename...> class Konteineris>
void nuskaitytiStudentus(Konteineris<Studentas<Konteineris>>& grupe, const std::string& filename) {
    std::ifstream ins(filename);
    if (!ins) throw std::runtime_error("Nepavyko atidaryti failo " + filename);

    std::string eilute;
    std::getline(ins, eilute);  // antraste
    std::istringstream antraste(eilute);
    std::string zodis;
    int stulpeliu = 0;
    while (antraste >> zodis)
        stulpeliu++;
    const int pazKiekis = std::max(stulpeliu - 3, 0);  // minus Vardas, Pavardė, Egzaminas

    while (std::getline(ins, eilute)) {
        Studentas<Konteineris> st;
        std::istringstream duomenys(eilute);
        duomenys >> st.vardas >> st.pavarde;
        if constexpr (std::is_same_v<Konteineris<int>, std::vector<int>>) st.paz.reserve(pazKiekis);
        for (int i = 0; i < pazKiekis; i++) {
            int num;
            duomenys >> num;
            st.paz.push_back(num);
        }
        duomenys >> st.exam;
        grupe.push_back(std::move(st));
    }
}

template <template <typename...> class Konteineris>
void isvestiStudentus(const Konteineris<Studentas<Konteineris>>& grupe, const std::string& filename) {
    std::ofstream out(filename);
    out << std::fixed << std::setprecision(2);

    rasytiAntraste(out);
    for (const auto& st : grupe) {
        rasytiStudenta(out, st);
    }
}
bool arFailaiEgzistuoja(int min, int max);

#endif  // OOP_PROJECT_FAILAI_H
