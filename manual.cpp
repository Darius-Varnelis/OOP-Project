//
// Created by Darc on 10/13/2026.
//

#include "manual.h"
#include "studentas.h"
#include "utils.h"
#include <iostream>
#include <sstream>
using std::string;

namespace pagalba {
    void rasytiAntraste(std::ostream& out, Statistika statistika) {
        out << std::left << std::setw(PLOTIS) << "Vardas" << "|";
        out << std::setw(utf8Plotis("Pavardė")) << "Pavardė" << "|";
        if (statistika == Statistika::Vidurkis) {
            out << std::setw(PLOTIS) << "Galutinis (vidurkis)" << "|\n";
        } else if (statistika == Statistika::Mediana) {
            out << std::setw(PLOTIS) << "Galutinis (mediana)" << "|\n";
        } else if (statistika == Statistika::Abu) {
            out << std::setw(PLOTIS) << "Galutinis (vidurkis)" << "|" << "Galutinis (mediana)" << "|\n";
        }
    }
    void rasytiStudenta(std::ostream& out, const Studentas& st, Statistika statistika) {
        out << std::left << std::setw(utf8Plotis(st.vardas)) << st.vardas << "|";
        out << std::setw(utf8Plotis(st.pavarde)) << st.pavarde << "|";
        if (statistika == Statistika::Vidurkis) {
            out << std::setw(PLOTIS)<< std::fixed << std::setprecision(2) << st.galutinis<< "|\n";
        } else if (statistika == Statistika::Mediana) {
            out << std::setw(PLOTIS)<< std::fixed << std::setprecision(2) << 0.4*mediana(st.paz)+0.6*st.exam  << "|\n";
        } else if (statistika == Statistika::Abu) {
            out << std::setw(PLOTIS)<< std::fixed << std::setprecision(2) << st.galutinis<< "|" <<std::setw(PLOTIS)<< 0.4*mediana(st.paz)+0.6*st.exam << "|\n";
        }
    }
}

bool iSkaiciu(const string& tekstas, int& rezultatas) {
    try {
        size_t pabaiga;
        int sk = std::stoi(tekstas, &pabaiga);
        if (tekstas.find_first_not_of(" \t\r", pabaiga) != string::npos) return false;
        rezultatas = sk;
        return true;
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}

int ivestiSk(const string& klausimas, int nuo, int iki) {
    string eilute;
    std::cout << klausimas;
    while (std::getline(std::cin, eilute)) {
        int sk;
        if (!iSkaiciu(eilute, sk)) {
            std::cout << "Įvesta netinkama reikšmė (ne skaičius arba per didelis skaičius), bandykite vėl.\n";
        } else if (sk < nuo || sk > iki) {
            if (iki == BE_RIBOS) {
                std::cout << "Skaičius turi būti ne mažesnis nei " << nuo << ".\n";
            } else {
                std::cout << "Skaičius turi būti nuo " << nuo << " iki " << iki << ".\n";
            }
        } else {
            return sk;
        }
        std::cout << klausimas;
    }
    std::cout << "Įvedamas skaičius " << nuo << std::endl;
    return nuo;
}

bool taipArNe(const string& klausimas) {
    string eilute;
    std::cout << klausimas << " [y/n]: ";
    while (std::getline(std::cin, eilute)) {
        if (eilute == "y") {
            return true;
        }
        if (eilute == "n") {
            return false;
        }
        std::cout << "Įveskite \"n\" arba \"y\"\n";
        std::cout << klausimas;
    }
    std::cout << "Nepavyko nuskaityti atsakymo, priskiaramas [n] atsakynas" << std::endl;
    return false;
}

int nustatymai(const string& klausimas, const string& pasirinkimai) {
    std::cout << klausimas << '\n';
    std::istringstream ss(pasirinkimai);
    string pasirinkimas;
    int i = 0;
    while (std::getline(ss, pasirinkimas, ';')) {
        std::cout << "[" << i << "] - " << pasirinkimas << '\n';
        i++;
    }
    return ivestiSk("Įveskite savo pasirinkimą (nuo 0 iki "+std::to_string(i-1)+"): ", 0, i);
}