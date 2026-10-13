//
// Created by Darc on 10/13/2026.
//

#ifndef OOP_PROJECT_MANUAL_H
#define OOP_PROJECT_MANUAL_H
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include "studentas.h"
#include "utils.h"
enum class Statistika {Mediana, Vidurkis, Abu};
namespace pagalba {
    void rasytiAntraste(std::ostream& out, Statistika statistika);
    void rasytiStudenta(std::ostream& out, const Studentas& st, Statistika statistika);
}
// Skaičiaus įvedimas per konsolę
int ivestiSk(const std::string& klausimas, int nuo, int iki);

// Funkcija, gražinanti loginę reikšmę taip ar ne klausimui
bool taipArNe(const std::string& klausimas);
bool iSkaiciu(const std::string& tekstas, int& rezultatas);
template <typename Konteineris>
void ivestiRanka(bool zinomas_sk, Statistika statistika, std::ostream& output) {
    Konteineris grupe;
    const int studkiekis = ivestiSk("Kiek yra studentų? ", 0, BE_RIBOS);
    for (int i = 0; i < studkiekis; i++) {
        Studentas st;

        std::cout << "Įveskite vardą: ";
        std::cin >> st.vardas;

        std::cout << "Įveskite pavardę: ";
        std::cin >> st.pavarde;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (zinomas_sk) {
            const int kiekis = ivestiSk("Kiek studentas turi pažymių? ", 1, BE_RIBOS);
            for (int j = 1; j <= kiekis; j++) {
                st.paz.push_back(
                    ivestiSk("Įveskite " + std::to_string(j) + "-ąjį pažymį: ", MIN_PAZ, MAX_PAZ));
                std::cout << '\n';
            }
        }
        else {
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
        st.exam = ivestiSk("Įveskite egzamino rezultatą: ", MIN_PAZ, MAX_PAZ);
        grupe.push_back(st);
    }
    pagalba::rasytiAntraste(output, statistika);
    for (Studentas& st : grupe) {
        pagalba::rasytiStudenta(output, st, statistika);
    }
    }


int nustatymai(const std::string& klausimas, const std::string& pasirinkimai);


#endif //OOP_PROJECT_MANUAL_H
