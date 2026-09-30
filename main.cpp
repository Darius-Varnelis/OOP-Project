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


int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    const int minfailas = 1000;
    const int maxfailas = 10000000;

    std::cout << std::fixed << std::setprecision(3);

    std::cout << "Pagal ką rūšiuoti išvesties failus?\n"
     << "[0] - Vardą\n"
     << "[1] - Pavardę\n"
     << "[2] - Galutinį balą\n";
    auto rusiuoti = static_cast<Rusiuoti>(ivesti_sk("Pasirinkite programos režimą: ", 0, 2));


    if (!ar_failai_egzistuoja(minfailas,maxfailas) or taiparne("Ar generuoti naujus failus? [y/n]")) {
        Timer visasGeneravimas;
        for (int i = minfailas; i <= maxfailas; i *= 10) {
            Timer t;
            generuotiFaila(i);
            std::cout << "  Generavimas užtruko: " << t.elapsed() << " s\n";
        }
        std::cout << "Visų failų generavimas užtruko: " << visasGeneravimas.elapsed() << " s\n\n";
    }

    for (int i = minfailas; i <= maxfailas; i *= 10) {
        const std::string pavadinimas = failoPavadinimas("kursiokai", i);
        std::cout << "Apdorojamas failas " << pavadinimas << "\n";
        std::vector<double> nuskaitymai;
        std::vector<double> galutiniai;
        std::vector<double> rusiavimai;
        std::vector<double> isvedimai;
        std::vector<double> bendri;
        for (int j = 0; j < 5; j++){
            std::cout << j+1 << "-oji iteracija";

            Timer apdorojimas;
            Timer t;

            std::vector<studentas> grupe;
            nuskaitytiStudentus(grupe, pavadinimas);
            nuskaitymai.push_back(t.elapsed());
            std::cout << "  Nuskaitymas: " << nuskaitymai[j] << " s\n";

            t.reset();
            for (studentas& st : grupe) {
                skaiciuotiGalutini(st);
            }
            galutiniai.push_back(t.elapsed());
            std::cout << "  Galutinių skaičiavimas: " << galutiniai[j] << " s\n";

            t.reset();
            rusiuotiStudentus(grupe, rusiuoti);
            rusiavimai.push_back(t.elapsed());
            std::cout << "  Rūšiavimas: " << rusiavimai[j] << " s\n";
            t.reset();
            isvestiStudentus(grupe, i);
            isvedimai.push_back(t.elapsed());
            std::cout << "  Išvedimas į failus: " << isvedimai[j] << " s\n";
            bendri.push_back(apdorojimas.elapsed());
            std::cout << "  Viso apdorojimas: " << bendri[j] << " s\n\n";
        }
        std::cout << "Nuskaitymų vidurkis: "<<vidurkis(nuskaitymai)<<" s\n";
        std::cout << "Galutinių pažymių skaičiavimo vidurkis: "<<vidurkis(galutiniai)<<" s\n";
        std::cout << "Rūšiavimo vidurkis: "<<vidurkis(rusiavimai)<<" s\n";
        std::cout << "Išvedimo vidurkis: "<<vidurkis(isvedimai)<<" s\n";
        std::cout << "Visų apdorojimų vidurkis: "<<vidurkis(bendri)<<" s\n\n";
    }
}
