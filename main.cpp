#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

#include "failai.h"
#include "studentas.h"
#include "timer.h"
#include "utils.h"
#include "results.h"


int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    constexpr int MINFAILAS = 1000;
    constexpr int MAXFAILAS = 10000000;
    constexpr int KARTAI = 5;

    std::cout << std::fixed << std::setprecision(3);

    std::cout << "Pagal ką rūšiuoti išvesties failus?\n"
     << "[0] - Vardą\n"
     << "[1] - Pavardę\n"
     << "[2] - Galutinį balą\n";
    auto rusiuoti = static_cast<Rusiuoti>(ivestiSk("Pasirinkite programos režimą: ", 0, 2));


    if (!arFailaiEgzistuoja(MINFAILAS,MAXFAILAS) or taipArNe("Ar generuoti naujus failus? [y/n]")) {
        Timer visasGeneravimas;
        for (int i = MINFAILAS; i <= MAXFAILAS; i *= 10) {
            Timer t;
            generuotiFaila(i);
            std::cout << "  Generavimas užtruko: " << t.elapsed() << " s\n";
        }
        std::cout << "Visų failų generavimas užtruko: " << visasGeneravimas.elapsed() << " s\n\n";
    }
    std::vector<Rezultatai> visi;
    for (int i = MINFAILAS; i <= MAXFAILAS; i *= 10) {
        Rezultatai rezultatai;
        rezultatai.dydis = i;
        const std::string pavadinimas = failoPavadinimas("kursiokai", i);
        std::cout << "Apdorojamas failas " << pavadinimas << "\n";
        for (int j = 0; j < KARTAI; j++){
            std::cout << j+1 << "-oji iteracija\n";

            Timer apdorojimas;
            Timer t;

            std::vector<Studentas> grupe;
            nuskaitytiStudentus(grupe, pavadinimas);
            rezultatai.nuskaitymai.push_back(t.elapsed());
            std::cout << "  Nuskaitymas: " << rezultatai.nuskaitymai[j] << " s\n";

            t.reset();
            for (Studentas& st : grupe) {
                skaiciuotiGalutini(st);
            }
            rezultatai.galutiniai.push_back(t.elapsed());
            std::cout << "  Galutinių skaičiavimas: " << rezultatai.galutiniai[j] << " s\n";

            t.reset();
            rusiuotiStudentus(grupe, rusiuoti);
            rezultatai.rusiavimai.push_back(t.elapsed());
            std::cout << "  Rūšiavimas: " << rezultatai.rusiavimai[j] << " s\n";

            t.reset();
            std::vector<Studentas> nuskriaustukai, kietukai;
            for (Studentas& st : grupe) {
                (st.galutinis < ISLAIKYMO_RIBA ? nuskriaustukai : kietukai).push_back(std::move(st));
            }
            grupe.clear();
            rezultatai.dalijimai.push_back(t.elapsed());
            std::cout << "  Dalijimas į dvi grupes: " << rezultatai.dalijimai[j] << " s\n";

            t.reset();
            isvestiStudentus(nuskriaustukai, failoPavadinimas("nuskriaustukai", i));
            rezultatai.isvedimaiNuskriaustuku.push_back(t.elapsed());
            std::cout << "  Nuskriaustukų išvedimas: " << rezultatai.isvedimaiNuskriaustuku[j] << " s\n";

            t.reset();
            isvestiStudentus(kietukai, failoPavadinimas("kietukai", i));
            rezultatai.isvedimaiKietuku.push_back(t.elapsed());
            std::cout << "  Kietukų išvedimas: " << rezultatai.isvedimaiKietuku[j] << " s\n";
            rezultatai.bendri.push_back(apdorojimas.elapsed());
            std::cout << "  Viso apdorojimas: " << rezultatai.bendri[j] << " s\n\n";
        }
        visi.push_back(rezultatai);
    }
    std::string lentele = "lentele.txt";
    spausdintiLentele(lentele,visi);
}
