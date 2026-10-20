//
// Created by Darc on 10/13/2026.
//

#ifndef OOP_PROJECT_MANUAL_H
#define OOP_PROJECT_MANUAL_H
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <random>

#include "nustatymai.h"
#include "studentas.h"
#include "utils.h"
#include "failai.h"

namespace pagalba {
void rasytiAntraste(std::ostream& out, Statistika statistika);
template <template <typename...> class Konteineris>
void rasytiStudenta(std::ostream& out, const Studentas<Konteineris>& st, Statistika statistika) {
    out << std::left << std::setw(utf8Plotis(st.vardas)) << st.vardas << "|";
    out << std::setw(utf8Plotis(st.pavarde)) << st.pavarde << "|";
    if (statistika == Statistika::Vidurkis) {
        out << std::setw(PLOTIS) << std::fixed << std::setprecision(2) << st.galutinis << "|\n";
    } else if (statistika == Statistika::Mediana) {
        out << std::setw(PLOTIS) << std::fixed << std::setprecision(2) << 0.4 * mediana(st.paz) + 0.6 * st.exam
            << "|\n";
    } else if (statistika == Statistika::Abu) {
        out << std::setw(PLOTIS) << std::fixed << std::setprecision(2) << st.galutinis << "|" << std::setw(PLOTIS)
            << 0.4 * mediana(st.paz) + 0.6 * st.exam << "|\n";
    }
}
template <template <typename...> class Konteineris>
void rasytiGrupe(std::ostream& out, const Konteineris<Studentas<Konteineris>>& grupe, Statistika statistika) {
    rasytiAntraste(out, statistika);
    for (const auto& st : grupe) {
        rasytiStudenta(out, st, statistika);
    }
}
}
// Skaičiaus įvedimas per konsolę
int ivestiSk(const std::string& klausimas, int nuo, int iki);

// Funkcija, gražinanti loginę reikšmę taip ar ne klausimui
bool taipArNe(const std::string& klausimas);
bool iSkaiciu(const std::string& tekstas, int& rezultatas);
template <template <typename...> class Konteineris>
void ivestiRanka(bool zinomas_sk, Statistika statistika, Rezimas rezimas, std::ostream& output, Rusiuoti rusiuoti, Tvarka tvarka) {
    const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(static_cast<std::mt19937::result_type>(seed));
    std::uniform_int_distribution<int> pazymiu_dist(MIN_PAZ, MAX_PAZ);
    Konteineris<Studentas<Konteineris>> grupe;
    const int studkiekis = ivestiSk("Kiek yra studentų? ", 0, BE_RIBOS);
    for (int i = 0; i < studkiekis; i++) {
        Studentas<Konteineris> st;

        std::cout << "Įveskite vardą: ";
        std::cin >> st.vardas;

        std::cout << "Įveskite pavardę: ";
        std::cin >> st.pavarde;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (zinomas_sk) {
            const int kiekis = ivestiSk("Kiek studentas turi pažymių? ", 1, BE_RIBOS);
            if (rezimas == Rezimas::Ranka) {
                for (int j = 1; j <= kiekis; j++) {
                    st.paz.push_back(ivestiSk("Įveskite " + std::to_string(j) + "-ąjį pažymį: ", MIN_PAZ, MAX_PAZ));
                    std::cout << '\n';
                }
            } else {
                std::cout << "Suvesti atsitiktiniai pažymiai: ";
                for (int j = 0; j < kiekis; j++) {
                    const int sk = pazymiu_dist(gen);
                    st.paz.push_back(sk);
                    std::cout << sk << " ";
                }
                std::cout << '\n';
            }
        } else {
            std::string eilute;
            while (true) {
                std::cout << "Įveskite " << st.paz.size() + 1 << "-ąjį pažymį (Enter, kad užbaigti): ";
                if (!std::getline(std::cin, eilute) || eilute.empty()) break;
                int pazymys;
                if (!iSkaiciu(eilute, pazymys)) {
                    std::cout << "Įvesta netinkama reikšmė (ne skaičius arba per didelis skaičius)!\n";
                } else if (pazymys < MIN_PAZ || pazymys > MAX_PAZ) {
                    std::cout << "Pažymys turi būti nuo " << MIN_PAZ << " iki " << MAX_PAZ << "!\n";
                } else {
                    st.paz.push_back(pazymys);
                }
            }
        }
        if (rezimas == Rezimas::Generavimas) {
            st.exam = pazymiu_dist(gen);
            std::cout << "Atsitiktinis egzamino rezultatas: " << st.exam << '\n';
        } else {
            st.exam = ivestiSk("Įveskite egzamino rezultatą: ", MIN_PAZ, MAX_PAZ);
        }

        skaiciuotiGalutini(st);
        grupe.push_back(st);
        std::cout << "Įvesto studento adresas atmintyje: " << &grupe.back() << "\n";
    }
    rusiuotiStudentus(grupe,rusiuoti,tvarka);
    pagalba::rasytiGrupe(output, grupe, statistika);
}
template <template <typename...> class Konteineris>
void nuskaitytiIsFailo(const std::string& filename, Statistika statistika, std::ostream& output, Rusiuoti rusiuoti, Tvarka tvarka) {
    Konteineris<Studentas<Konteineris>> grupe;
    nuskaitytiStudentus(grupe, filename);
    for (auto& st : grupe) {
        skaiciuotiGalutini(st);
    }
    rusiuotiStudentus(grupe,rusiuoti,tvarka);
    pagalba::rasytiGrupe(output,grupe,statistika);
}

int nustatymai(const std::string& klausimas, const std::string& pasirinkimai);

#endif  // OOP_PROJECT_MANUAL_H
