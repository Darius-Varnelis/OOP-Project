
#ifndef OOP_PROJECT_TESTAI_H
#define OOP_PROJECT_TESTAI_H
#include <iostream>
#include <string>

#include "failai.h"
#include "nustatymai.h"
#include "results.h"
#include "studentas.h"
#include "timer.h"

template <typename Konteineris>
void testas(int i, int j, const std::string& pavadinimas, Rezultatai& rezultatai, Rusiuoti rusiuoti, Tvarka tvarka) {
    Konteineris grupe;
    Timer apdorojimas;
    Timer t;
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

    rusiuotiStudentus(grupe, rusiuoti, tvarka);
    rezultatai.rusiavimai.push_back(t.elapsed());
    std::cout << "  Rūšiavimas: " << rezultatai.rusiavimai[j] << " s\n";

    t.reset();
    Konteineris nuskriaustukai, kietukai;
    skirstytiStudentus(grupe, nuskriaustukai, kietukai);
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
Rezultatai testuPaleistuvas(int i, const Struktura& struktura, const Rusiuoti& rusiuoti, const Tvarka& tvarka);
#endif //OOP_PROJECT_TESTAI_H
