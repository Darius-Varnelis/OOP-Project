#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

using std::cin;
using std::cout;
using std::string;
using std::vector;

constexpr int MIN_PAZ = 0;
constexpr int MAX_PAZ = 10;
constexpr int BE_RIBOS = std::numeric_limits<int>::max();
constexpr int PLOTIS = 20;

size_t utf8_ilgis(const string& tekstas) {
    size_t ilgis = 0;
    for (unsigned char c : tekstas) {
        if ((c & 0xC0) != 0x80) ilgis++;
    }
    return ilgis;
}

int utf8_plotis(const string& tekstas) {
    return static_cast<int>(PLOTIS + tekstas.size() - utf8_ilgis(tekstas));
}

struct studentas {
    string vardas, pavarde;
    vector<int> paz;
    int exam = 0;
    double galutinis = 0.0;
};

double vidurkis(const vector<int>& paz) {
    if (paz.empty()) return 0.0;
    return std::accumulate(paz.begin(), paz.end(), 0.0) / paz.size();
}

void skaiciuotiGalutini(studentas& st) {
    st.galutinis = (0.4*vidurkis(st.paz))+(0.6*st.exam)    ;
}

void nuskaitytiStudentus(vector<studentas>& grupe, const string& filename) {
    std::ifstream ins(filename);
    if (!ins) throw std::runtime_error("Nepavyko atidaryti failo " + filename);

    string eilute;
    std::getline(ins, eilute);                        // antraste
    std::istringstream antraste(eilute);
    string zodis;
    int stulpeliu = 0;
    while (antraste >> zodis) stulpeliu++;
    int paz_kiekis = std::max(stulpeliu - 3, 0);      // minus Vardas, Pavardė, Egzaminas

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
void isvestiStudentus(vector<studentas>& grupe, const int n) {
    std::ofstream nuskriaustukai("nuskriaustukai" +std::to_string(n) +".txt");
    std::ofstream kietukai("kietukai" +std::to_string(n)+" .txt");
    nuskriaustukai << std::left << std::setw(PLOTIS) << "Vardas" << "|";
    nuskriaustukai << std::setw(utf8_plotis("Pavardė")) << "Pavardė" << "|";
    nuskriaustukai << std::setw(PLOTIS) << "Galutinis" << "|\n";
    kietukai << std::left << std::setw(PLOTIS) << "Vardas" << "|";
    kietukai << std::setw(utf8_plotis("Pavardė")) << "Pavardė" << "|";
    kietukai << std::setw(PLOTIS) << "Galutinis" << "|\n" ;
    for (studentas st : grupe) {
        if (st.galutinis < 5.0) {
            nuskriaustukai << std::left << std::setw(utf8_plotis(st.vardas)) << st.vardas << "|";
            nuskriaustukai << std::left << std::setw(utf8_plotis(st.pavarde)) << st.pavarde << "|";
            nuskriaustukai << std::right << std::setw(PLOTIS) << std::setprecision(2) << std::fixed<<  st.galutinis << "|\n";
        } else {
            kietukai << std::left << std::setw(utf8_plotis(st.vardas)) << st.vardas << "|";
            kietukai << std::left << std::setw(utf8_plotis(st.pavarde)) << st.pavarde << "|";
            kietukai << std::right << std::setw(PLOTIS) << std::setprecision(2) << std::fixed<<st.galutinis << "|\n";
        }

    }

}

void generuotiFaila(const int n) {
    const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(static_cast<std::mt19937::result_type>(seed));
    std::uniform_int_distribution<int> pazymiu_dist(MIN_PAZ, MAX_PAZ);
    std::uniform_int_distribution<int> nd(1,20);
    int nd_kiekis = nd(gen);
    cout << "Generuojamas failas kursiokai" + std::to_string(n) + ".txt\n";
    std::ofstream output;
    output.open("kursiokai" + std::to_string(n) + ".txt");

    output << std::left << std::setw(PLOTIS) << "Vardas";
    output << std::left << std::setw(utf8_plotis("Pavardė")) << "Pavardė";
    for (int i=0; i<nd_kiekis; i++) {
        output << std::left << std::setw(PLOTIS) << "ND" + std::to_string(i+1);
    }
    output << std::left << std::setw(PLOTIS) << "Egzaminas\n";

    for (int i = 0; i < n; i++) {
        output << std::left <<std::setw(PLOTIS) << "Vardenis" + std::to_string(i+1) ;
        output << std::left << std::setw(PLOTIS) << "Pavardenis" + std::to_string(i+1);
        for (int j=0; j<nd_kiekis; j++) {
            output << std::right << std::setw(PLOTIS) << pazymiu_dist(gen) ;
            }
        output << std::right << std::setw(PLOTIS) <<pazymiu_dist(gen) <<"\n" ;
        }


}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    const int minfailas = 1000;
    const int maxfailas = 10000000;
    for (int i =minfailas; i<=maxfailas; i=i*10) {
        generuotiFaila(i);
    }
    for (int i =minfailas; i<=maxfailas; i=i*10) {
        vector<studentas> grupe;
        nuskaitytiStudentus(grupe,"kursiokai"+std::to_string(i)+".txt");
        for (studentas& st : grupe) {
            skaiciuotiGalutini(st);
        }
        isvestiStudentus(grupe, i);
    }
}
