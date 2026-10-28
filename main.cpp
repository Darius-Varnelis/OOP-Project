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
#include "nustatymai.h"
#include "studentas.h"
#include "timer.h"
#include "manual.h"
#include "results.h"
#include "testai.h"

int main(int argc, char* argv[]) {

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    if (argc == 4 && std::string(argv[1]) == "--testas")
        return vienasTestas(argv[2], argv[3]);

    std::cout << std::fixed << std::setprecision(3);
    auto rezimas = static_cast<Rezimas>(nustatymai(
        "Koks programos rėžimas?",
        "Studentų įvedimas ranka;Studentų nuskaitymas iš failo;Automatinis generavimas;Programos greitumo testavimas;Atminties naudojimo testas;"));
    if (rezimas == Rezimas::Atmintis) {
        paleistiAtmintiesTestus(argv[0]);
        return 0;
    }
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
        std::vector<Rezultatai> visiVector;
        std::vector<Rezultatai> visiList;
        for (int i = MINFAILAS; i <= MAXFAILAS; i *= 10) {
            std::cout << "Atliekamas testas su Vector.\n";
            Rezultatai rezultatai = testuPaleistuvas(i, Struktura::Vector, rusiuoti, tvarka);
            visiVector.push_back(rezultatai);
            std::cout << "Atliekamas testas su List.\n";
            rezultatai = testuPaleistuvas(i, Struktura::List, rusiuoti, tvarka);
            visiList.push_back(rezultatai);
        }
        std::string lentele = "lenteleVector.txt";
        spausdintiLentele(lentele, visiVector);
        lentele = "lenteleList.txt";
        spausdintiLentele(lentele, visiList);
        if (taipArNe("Ar trinti nuskriaustukų ir kietukų failus? ")) {
            for (int i = MINFAILAS; i <= MAXFAILAS; i *= 10) {
                trintiFaila(failoPavadinimas("nuskriaustukai",i));
                trintiFaila(failoPavadinimas("kietukai",i));
            }
        }
        if (taipArNe("Ar trinti kursiokų failus? ")) {
            if (taipArNe("Ar tikrai???!!!")) {
                for (int i = MINFAILAS; i <= MAXFAILAS; i *= 10) {
                    trintiFaila(failoPavadinimas("kursiokai",i));
                }
            }
        }

        return 0;
    }


    auto struktura = static_cast<Struktura>(nustatymai("Į kokią C++ struktūrą vesti studentus?", "Vector;List"));
    auto isvedimas = static_cast<Isvedimas>(nustatymai("Kur išvesti studentų duomenis?", "Į konsolę;Į failą"));
    auto statistika =
    static_cast<Statistika>(nustatymai("Kokios statistikos pageidaujate?", "Vidurkio;Medianos;Abiejų"));
    bool arZinomasSk;
    if (rezimas == Rezimas::Ranka) {
        arZinomasSk = taipArNe("Ar žinomas namų darbų skaičius?");
    } else {
        arZinomasSk = true;
    }
    if (rezimas == Rezimas::Ranka or rezimas == Rezimas::Generavimas) {

        if (isvedimas == Isvedimas::Konsole) {
            if (struktura == Struktura::List) {
                ivestiRanka<std::list>(arZinomasSk, statistika, rezimas, std::cout, rusiuoti, tvarka);
            } else {
                ivestiRanka<std::vector>(arZinomasSk, statistika, rezimas, std::cout, rusiuoti, tvarka);
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
                ivestiRanka<std::list>(arZinomasSk, statistika, rezimas, failas, rusiuoti, tvarka);
            } else {
                ivestiRanka<std::vector>(arZinomasSk, statistika, rezimas, failas, rusiuoti, tvarka);
            }
        }

    }
    if (rezimas == Rezimas::Failas) {
        std::string failoPavadinimas;
        std::cout << "Įveskite failo pavadinimą nuskaitymui: ";
        std::cin >> failoPavadinimas;
        if (isvedimas == Isvedimas::Konsole) {
            try {
                if (struktura == Struktura::Vector) {
                    nuskaitytiIsFailo<std::vector>(failoPavadinimas + ".txt",statistika,std::cout, rusiuoti, tvarka);
                } else {
                    nuskaitytiIsFailo<std::list>(failoPavadinimas + ".txt",statistika,std::cout, rusiuoti, tvarka);
                }
            }
            catch (std::exception& e) {
                std::cout << "Failo nepavyko atdaryti: "<<e.what() << '\n';
            }
        }
        else {
            std::string outputPavadinimas;
            std::cout << "Įveskite išvesties failo pavadinimą: ";
            std::cin >> outputPavadinimas;
            std::ofstream failas(outputPavadinimas + ".txt");
            if (!failas) {
                std::cout << "Nepavyko atidaryti failo!\n";
                return 0;
            }
            try {
                if (struktura == Struktura::Vector) {
                    nuskaitytiIsFailo<std::vector>(failoPavadinimas + ".txt",statistika,failas, rusiuoti, tvarka);
                } else {
                    nuskaitytiIsFailo<std::list>(failoPavadinimas + ".txt",statistika,failas, rusiuoti, tvarka);
                }
            }
            catch (std::exception& e) {
                std::cout << "Failo nepavyko atdaryti: "<<e.what() << '\n';
            }
        }
    }

}


