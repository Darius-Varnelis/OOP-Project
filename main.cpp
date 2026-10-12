#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

#include "failai.h"
#include "studentas.h"
#include "timer.h"
#include "manual.h"
#include "results.h"
template <typename Konteineris>
void testas (const std::string& i, int j, const std::string& pavadinimas, Rezultatai& rezultatai, Rusiuoti rusiuoti);
Rezultatai testuPaleistuvas(const std::string& i, const std::string& fileName, const Struktura& struktura, const Rusiuoti& rusiuoti);
constexpr int KARTAI = 5;
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    constexpr int MINFAILAS = 1000;
    constexpr int MAXFAILAS = 10000000;


    std::cout << std::fixed << std::setprecision(3);
    auto struktura = static_cast<Struktura>(nustatymai("Į kokią C++ struktūrą vesti studentus?","Vector;List"));
    auto rusiuoti = static_cast<Rusiuoti>(nustatymai("Pagal ką rūšiuoti išvesties failus?","Vardą;Pavardę;Galutinį balą"));
    auto rezimas = static_cast<Rezimas>(nustatymai("Koks programos rėžimas?","Studentų įvedimas ranka;Studentų nuskaitymas iš failo;Programos greitumo testavimas"));
    if (rezimas == Rezimas::Benchmark) {
        if (!arFailaiEgzistuoja(MINFAILAS,MAXFAILAS) or taipArNe("Ar generuoti naujus failus? [y/n]")) {
            Timer visasGeneravimas;
            for (int i = MINFAILAS; i <= MAXFAILAS; i *= 10) {
                Timer t;
                generuotiFaila(std::to_string(i));
                std::cout << "  Generavimas užtruko: " << t.elapsed() << " s\n";
            }
            std::cout << "Visų failų generavimas užtruko: " << visasGeneravimas.elapsed() << " s\n\n";
        }
        std::vector<Rezultatai> visi;
        for (int i = MINFAILAS; i <= MAXFAILAS; i *= 10) {
            Rezultatai rezultatai = testuPaleistuvas(std::to_string(i), failoPavadinimas("kursiokai", std::to_string(i)), struktura, rusiuoti);
            visi.push_back(rezultatai);
            }

        std::string lentele = "lentele.txt";
        spausdintiLentele(lentele,visi);
    }

}
template <typename Konteineris>
void testas (const std::string& i, const int j, const std::string& pavadinimas, Rezultatai& rezultatai, Rusiuoti rusiuoti){
    Konteineris grupe;
    Timer apdorojimas;
    Timer t;
    std::cout << "  Grupės adresas atmintyje: " << &grupe <<"\n";
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

Rezultatai testuPaleistuvas(const std::string& i, const std::string& fileName, const Struktura& struktura, const Rusiuoti& rusiuoti) {
    Rezultatai rezultatai;
    rezultatai.dydis = i;
    std::cout << "Apdorojamas failas " << fileName << "\n";
    for (int j = 0; j < KARTAI; j++) {
        std::cout << j+1 << "-oji iteracija\n";
        if (struktura == Struktura::Vector){
            testas<std::vector<Studentas>>(i, j, fileName, rezultatai, rusiuoti);
        }
        else {
            testas<std::list<Studentas>>(i,j,fileName,rezultatai,rusiuoti);
        }
    }
    return rezultatai;
}