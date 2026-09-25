#include "failai.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>

#include "utils.h"

using std::string;
using std::vector;

namespace {

void rasytiAntraste(std::ostream& out) {
    out << std::left << std::setw(PLOTIS) << "Vardas" << "|";
    out << std::setw(utf8_plotis("Pavardė")) << "Pavardė" << "|";
    out << std::setw(PLOTIS) << "Galutinis" << "|\n";
}

void rasytiStudenta(std::ostream& out, const studentas& st) {
    out << std::left << std::setw(utf8_plotis(st.vardas)) << st.vardas << "|";
    out << std::setw(utf8_plotis(st.pavarde)) << st.pavarde << "|";
    out << std::right << std::setw(PLOTIS) << st.galutinis << "|\n";
}

}  // namespace

string failoPavadinimas(const string& pradzia, int n) {
    return pradzia + std::to_string(n) + ".txt";
}

void generuotiFaila(const int n) {
    const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(static_cast<std::mt19937::result_type>(seed));
    std::uniform_int_distribution<int> pazymiu_dist(MIN_PAZ, MAX_PAZ);
    std::uniform_int_distribution<int> nd_dist(1, 20);
    const int nd_kiekis = nd_dist(gen);

    const string pavadinimas = failoPavadinimas("kursiokai", n);
    std::cout << "Generuojamas failas " << pavadinimas << "\n";
    std::ofstream output(pavadinimas);

    output << std::left << std::setw(PLOTIS) << "Vardas";
    output << std::setw(utf8_plotis("Pavardė")) << "Pavardė";
    for (int i = 0; i < nd_kiekis; i++) {
        output << std::setw(PLOTIS) << "ND" + std::to_string(i + 1);
    }
    output << std::setw(PLOTIS) << "Egzaminas" << "\n";

    for (int i = 0; i < n; i++) {
        output << std::left << std::setw(PLOTIS) << "Vardenis" + std::to_string(i + 1);
        output << std::setw(PLOTIS) << "Pavardenis" + std::to_string(i + 1);
        output << std::right;
        for (int j = 0; j < nd_kiekis; j++) {
            output << std::setw(PLOTIS) << pazymiu_dist(gen);
        }
        output << std::setw(PLOTIS) << pazymiu_dist(gen) << "\n";
    }
}

void nuskaitytiStudentus(vector<studentas>& grupe, const string& filename) {
    std::ifstream ins(filename);
    if (!ins) throw std::runtime_error("Nepavyko atidaryti failo " + filename);

    string eilute;
    std::getline(ins, eilute);  // antraste
    std::istringstream antraste(eilute);
    string zodis;
    int stulpeliu = 0;
    while (antraste >> zodis) stulpeliu++;
    const int paz_kiekis = std::max(stulpeliu - 3, 0);  // minus Vardas, Pavardė, Egzaminas

    while (std::getline(ins, eilute)) {
        studentas st;
        std::istringstream duomenys(eilute);
        duomenys >> st.vardas >> st.pavarde;
        st.paz.reserve(paz_kiekis);
        for (int i = 0; i < paz_kiekis; i++) {
            int num;
            duomenys >> num;
            st.paz.push_back(num);
        }
        duomenys >> st.exam;
        grupe.push_back(std::move(st));
    }
}

void isvestiStudentus(const vector<studentas>& grupe, const int n) {
    std::ofstream nuskriaustukai(failoPavadinimas("nuskriaustukai", n));
    std::ofstream kietukai(failoPavadinimas("kietukai", n));
    nuskriaustukai << std::fixed << std::setprecision(2);
    kietukai << std::fixed << std::setprecision(2);

    rasytiAntraste(nuskriaustukai);
    rasytiAntraste(kietukai);
    for (const studentas& st : grupe) {
        rasytiStudenta(st.galutinis < ISLAIKYMO_RIBA ? nuskriaustukai : kietukai, st);
    }
}
