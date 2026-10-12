#ifndef OOP_PROJECT_FAILAI_H
#define OOP_PROJECT_FAILAI_H

#include <iomanip>
#include <ios>
#include <string>
#include <vector>
#include <fstream>

#include "studentas.h"

std::string failoPavadinimas(const std::string& pradzia, const std::string& n);


void generuotiFaila(const std::string& n);
void rasytiAntraste(std::ostream& out);
void rasytiStudenta(std::ostream& out, const Studentas& st);

template <typename Konteineris>
void nuskaitytiStudentus(Konteineris& grupe, const std::string& filename) {
    std::ifstream ins(filename);
    if (!ins) throw std::runtime_error("Nepavyko atidaryti failo " + filename);

    std::string eilute;
    std::getline(ins, eilute);  // antraste
    std::istringstream antraste(eilute);
    std::string zodis;
    int stulpeliu = 0;
    while (antraste >> zodis) stulpeliu++;
    const int pazKiekis = std::max(stulpeliu - 3, 0);  // minus Vardas, Pavardė, Egzaminas

    while (std::getline(ins, eilute)) {
        Studentas st;
        std::istringstream duomenys(eilute);
        duomenys >> st.vardas >> st.pavarde;
        st.paz.reserve(pazKiekis);
        for (int i = 0; i < pazKiekis; i++) {
            int num;
            duomenys >> num;
            st.paz.push_back(num);
        }
        duomenys >> st.exam;
        grupe.push_back(std::move(st));
    }
}

template <typename Konteineris>
void isvestiStudentus(const Konteineris& grupe, const std::string& filename) {
    std::ofstream out(filename);
    out << std::fixed << std::setprecision(2);

    rasytiAntraste(out);
    for (const Studentas& st : grupe) {
        rasytiStudenta(out, st);
    }
}
bool arFailaiEgzistuoja(int min, int max);

#endif  // OOP_PROJECT_FAILAI_H
