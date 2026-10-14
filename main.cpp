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
void testas(int i, int j, const std::string& pavadinimas, Rezultatai& rezultatai, Rusiuoti rusiuoti, Tvarka tvarka);
Rezultatai testuPaleistuvas(int i, const Struktura& struktura, const Rusiuoti& rusiuoti, const Tvarka& tvarka);
constexpr int KARTAI = 5;
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << std::fixed << std::setprecision(3);
    auto rezimas = static_cast<Rezimas>(nustatymai(
        "Koks programos rėžimas?",
        "Studentų įvedimas ranka;Studentų nuskaitymas iš failo;Automatinis generavimas;Programos greitumo testavimas"));
    auto rusiuoti =
        static_cast<Rusiuoti>(nustatymai("Pagal ką rūšiuoti išvesties failus?", "Vardą;Pavardę;Galutinį balą"));
    auto tvarka =
        static_cast<Tvarka>(nustatymai("Kokia tvarka rūšiuoti išvesties failus?", "Didėjimo;Mažėjimo"));

    if (rezimas == Rezimas::Benchmark) {
        constexpr int MAXFAILAS = 10000000;
        constexpr int MINFAILAS = 1000;
        if (!arFailaiEgzistuoja(MINFAILAS, MAXFAILAS) or taipArNe("Ar generuoti naujus failus?")) {
            Timer visasGeneravimas;
            for (int i = MINFAILAS; i <= MAXFAILAS; i *= 10) {
                Timer t;
                generuotiFaila(i);
                std::cout << "  Generavimas užtruko: " << t.elapsed() << " s\n";
            }
            std::cout << "Visų failų generavimas užtruko: " << visasGeneravimas.elapsed() << " s\n\n";
        }
        std::vector<Rezultatai> visi;
        std::cout << "Atliekami testai su Vector struktūra.\n";
        for (int i = MINFAILAS; i <= MAXFAILAS; i *= 10) {

            Rezultatai rezultatai = testuPaleistuvas(i, Struktura::Vector, rusiuoti, tvarka);
            visi.push_back(rezultatai);
        }
        std::string lentele = "lenteleVector.txt";
        spausdintiLentele(lentele, visi);
        visi.clear();
        std::cout << "Atliekami testai su List struktūra.\n";
        for (int i = MINFAILAS; i <= MAXFAILAS; i *= 10) {

            Rezultatai rezultatai = testuPaleistuvas(i, Struktura::List, rusiuoti, tvarka);
            visi.push_back(rezultatai);
        }
        lentele = "lenteleList.txt";
        spausdintiLentele(lentele, visi);

        return 0;
    }


    auto struktura = static_cast<Struktura>(nustatymai("Į kokią C++ struktūrą vesti studentus?", "Vector;List"));
    auto isvedimas = static_cast<Isvedimas>(nustatymai("Kur išvesti studentų duomenis?", "Į konsolę;Į failą"));
    bool arZinomasSk;
    if (rezimas == Rezimas::Benchmark) {
        arZinomasSk = taipArNe("Ar žinomas namų darbų skaičius?");
    } else {
        arZinomasSk = true;
    }
    if ((rezimas == Rezimas::Ranka or rezimas == Rezimas::Generavimas) and rezimas != Rezimas::Benchmark) {
        auto statistika =
            static_cast<Statistika>(nustatymai("Kokios statistikos pageidaujate?", "Vidurkio;Medianos;Abiejų"));
        if (isvedimas == Isvedimas::Konsole) {
            if (struktura == Struktura::List) {
                ivestiRanka<std::list<Studentas>>(arZinomasSk, statistika, rezimas, std::cout, rusiuoti, tvarka);
            } else {
                ivestiRanka<std::vector<Studentas>>(arZinomasSk, statistika, rezimas, std::cout, rusiuoti, tvarka);
            }
        } else {
            std::string failoPavadinimas;
            std::cout << "Įveskite failo pavadinimą: ";
            std::cin >> failoPavadinimas;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::ofstream failas(failoPavadinimas + ".txt");
            if (!failas) {
                std::cout << "Nepavyko atidaryti failo!\n";
                return 0;
            }
            if (struktura == Struktura::List) {
                ivestiRanka<std::list<Studentas>>(arZinomasSk, statistika, rezimas, failas, rusiuoti, tvarka);
            } else {
                ivestiRanka<std::vector<Studentas>>(arZinomasSk, statistika, rezimas, failas, rusiuoti, tvarka);
            }
        }
    }
}
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

Rezultatai testuPaleistuvas(int i, const Struktura& struktura, const Rusiuoti& rusiuoti, const Tvarka& tvarka) {
    Rezultatai rezultatai;
    rezultatai.dydis = i;
    std::string fileName = failoPavadinimas("kursiokai", i);
    std::cout << "Apdorojamas failas " << fileName << "\n";
    for (int j = 0; j < KARTAI; j++) {
        std::cout << j + 1 << "-oji iteracija\n";
        if (struktura == Struktura::Vector) {
            testas<std::vector<Studentas>>(i, j, fileName, rezultatai, rusiuoti, tvarka);
        } else {
            testas<std::list<Studentas>>(i, j, fileName, rezultatai, rusiuoti, tvarka);
        }
    }
    return rezultatai;
}