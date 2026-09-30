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

    Timer visasGeneravimas;
    for (int i = minfailas; i <= maxfailas; i *= 10) {
        Timer t;
        generuotiFaila(i);
        std::cout << "  Generavimas užtruko: " << t.elapsed() << " s\n";
    }
    std::cout << "Visų failų generavimas užtruko: " << visasGeneravimas.elapsed() << " s\n\n";

    for (int i = minfailas; i <= maxfailas; i *= 10) {
        const std::string pavadinimas = failoPavadinimas("kursiokai", i);
        std::cout << "Apdorojamas failas " << pavadinimas << "\n";
        Timer apdorojimas;
        Timer t;

        std::vector<studentas> grupe;
        nuskaitytiStudentus(grupe, pavadinimas);
        std::cout << "  Nuskaitymas: " << t.elapsed() << " s\n";

        t.reset();
        for (studentas& st : grupe) {
            skaiciuotiGalutini(st);
        }
        std::cout << "  Galutinių skaičiavimas: " << t.elapsed() << " s\n";

        t.reset();
        rusiuotiStudentus(grupe, rusiuoti);
        std::cout << "  Rūšiavimas: " << t.elapsed() << " s\n";
        isvestiStudentus(grupe, i);
        std::cout << "  Išvedimas į failus: " << t.elapsed() << " s\n";

        std::cout << "  Viso apdorojimas: " << apdorojimas.elapsed() << " s\n\n";
    }
}
