#include "testai.h"
#include <cstdlib>
#include "utils.h"
#include "studentas.h"
constexpr int KARTAI = 5;
Rezultatai testuPaleistuvas(int i, const Struktura& struktura, const Rusiuoti& rusiuoti, const Tvarka& tvarka) {
    Rezultatai rezultatai;
    rezultatai.dydis = i;
    std::string fileName = failoPavadinimas("kursiokai", i);
    std::cout << "Apdorojamas failas " << fileName << "\n";
    for (int j = 0; j < KARTAI; j++) {
        std::cout << j + 1 << "-oji iteracija\n";
        if (struktura == Struktura::Vector) {
            testas<std::vector>(i, j, fileName, rezultatai, rusiuoti, tvarka);
        } else {
            testas<std::list>(i, j, fileName, rezultatai, rusiuoti, tvarka);
        }
    }
    return rezultatai;
}

int vienasTestas(const std::string& strategija, const std::string& failas) {


    std::vector<Studentas<std::vector>> grupe;
    nuskaitytiStudentus(grupe, failas);
    std::vector<Studentas<std::vector>> kietukai;
    std::vector<Studentas<std::vector>> nuskriaustukai;
    std::size_t pries = dabartineAtmintis();
    std::size_t pikasPries = pikineAtmintis();

    if (strategija == "copy") {
       skirstytiStudentusCopyIf(grupe, nuskriaustukai);
    }
    else if (strategija == "move") {
        skirstytiStudentusMano(grupe, nuskriaustukai, kietukai);
    }
    else if (strategija == "partition") {
        skirstytiStudentusPartition(grupe, nuskriaustukai, kietukai);
    }
    else if (strategija == "1") {
        skirstytiStudentus1(grupe,nuskriaustukai, kietukai);
    }
    else if (strategija == "2") {
        skirstytiStudentus2(grupe,nuskriaustukai);
    }

    std::size_t pikasPo = pikineAtmintis();
    std::cout << strategija << ',' << failas << ','
          << pries / (1024 * 1024) << ','
          << pikasPries / (1024 * 1024) << ','
          << pikasPo / (1024 * 1024) << '\n';
    return 0;
}


void paleistiAtmintiesTestus(const std::string& exe) {
    std::vector<std::string> strategijos = {"move", "1", "2", "copy", "partition"};
    std::vector<std::string> failai = {"kursiokai10000000.txt"};

    for (const auto& f : failai)
        for (const auto& s : strategijos)
            for (int i = 0; i < KARTAI; ++i) {
#ifdef _WIN32
                // cmd.exe reikalauja papildomų kabučių aplink visą komandą
                std::string cmd = "\"\"" + exe + "\" --testas " + s + " " + f
                                + " >> rezultatai.txt\"";
#else
                std::string cmd = "\"" + exe + "\" --testas " + s + " " + f
                                + " >> rezultatai.txt";
#endif
                std::system(cmd.c_str());
            }
    std::cout << "Baigta, žr. rezultatai.txt\n";
}