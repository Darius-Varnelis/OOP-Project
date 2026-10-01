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
    out << std::setw(utf8Plotis("Pavardė")) << "Pavardė" << "|";
    out << std::setw(PLOTIS) << "Galutinis" << "|\n";
}

void rasytiStudenta(std::ostream& out, const Studentas& st) {
    out << std::left << std::setw(utf8Plotis(st.vardas)) << st.vardas << "|";
    out << std::setw(utf8Plotis(st.pavarde)) << st.pavarde << "|";
    out << std::right << std::setw(PLOTIS) << st.galutinis << "|\n";
}

}  // namespace

string failoPavadinimas(const string& pradzia, int n) {
    return pradzia + std::to_string(n) + ".txt";
}

void generuotiFaila(const int n) {
    const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(static_cast<std::mt19937::result_type>(seed));
    std::uniform_int_distribution<int> pazymiuDist(MIN_PAZ, MAX_PAZ);
    std::uniform_int_distribution<int> ndDist(1, 20);
    const int ndKiekis = ndDist(gen);

    const string pavadinimas = failoPavadinimas("kursiokai", n);
    std::cout << "Generuojamas failas " << pavadinimas << "\n";
    std::ofstream output(pavadinimas);

    output << std::left << std::setw(PLOTIS) << "Vardas";
    output << std::setw(utf8Plotis("Pavardė")) << "Pavardė";
    for (int i = 0; i < ndKiekis; i++) {
        output << std::setw(PLOTIS) << "ND" + std::to_string(i + 1);
    }
    output << std::setw(PLOTIS) << "Egzaminas" << "\n";

    for (int i = 0; i < n; i++) {
        output << std::left << std::setw(PLOTIS) << "Vardenis" + std::to_string(i + 1);
        output << std::setw(PLOTIS) << "Pavardenis" + std::to_string(i + 1);
        output << std::right;
        for (int j = 0; j < ndKiekis; j++) {
            output << std::setw(PLOTIS) << pazymiuDist(gen);
        }
        output << std::setw(PLOTIS) << pazymiuDist(gen) << "\n";
    }
}

void nuskaitytiStudentus(vector<Studentas>& grupe, const string& filename) {
    std::ifstream ins(filename);
    if (!ins) throw std::runtime_error("Nepavyko atidaryti failo " + filename);

    string eilute;
    std::getline(ins, eilute);  // antraste
    std::istringstream antraste(eilute);
    string zodis;
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

void isvestiStudentus(const vector<Studentas>& grupe, const string& filename) {
    std::ofstream out(filename);
    out << std::fixed << std::setprecision(2);

    rasytiAntraste(out);
    for (const Studentas& st : grupe) {
        rasytiStudenta(out, st);
    }
}
bool arFailaiEgzistuoja(int min, int max) {
    for (int i = min; i <= max; i *= 10) {
        std::ifstream file(failoPavadinimas("kursiokai", i));
        if (!file.is_open()) {
            return false;
        }
    }
    return true;
}
