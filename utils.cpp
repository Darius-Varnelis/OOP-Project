#include "utils.h"
#include <stdexcept>
#include <string>
#include<iostream>
#include <numeric>
#include <vector>
using std::string;

namespace {
    bool i_skaiciu(const string& tekstas, int& rezultatas) {
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
}
size_t utf8_ilgis(const std::string& tekstas) {
    size_t ilgis = 0;
    for (unsigned char c : tekstas) {
        if ((c & 0xC0) != 0x80) ilgis++;
    }
    return ilgis;
}

int utf8_plotis(const std::string& tekstas) {
    return static_cast<int>(PLOTIS + tekstas.size() - utf8_ilgis(tekstas));
}

int ivesti_sk(const string& klausimas, int nuo, int iki) {
    string eilute;
    std::cout << klausimas;
    while (std::getline(std::cin, eilute)) {
        int sk;
        if (!i_skaiciu(eilute, sk)) {
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

bool taiparne(const string& klausimas) {
    string eilute;
    std::cout << klausimas;
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



