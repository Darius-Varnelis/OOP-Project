#include "testai.h"
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
