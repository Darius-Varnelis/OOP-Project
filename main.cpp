#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

using std::cin;
using std::cout;
using std::string;
using std::vector;

constexpr int MIN_PAZ = 0;
constexpr int MAX_PAZ = 10;
constexpr int BE_RIBOS = std::numeric_limits<int>::max();
constexpr int PLOTIS = 20;

enum class Rezimas { Ivesti, Nuskaityti, Generuoti };
enum class Statistika { Vidurkis, Mediana, Abu };

struct studentas {
    string vardas, pavarde;
    vector<int> paz;
    int exam = 0;
};

double mediana(vector<int> paz) {
    if (paz.empty()) return 0.0;
    std::sort(paz.begin(), paz.end());
    if (paz.size() % 2 == 1) {
        return paz[paz.size() / 2];
    }
    return (paz[(paz.size() - 1) / 2] + paz[paz.size() / 2]) / 2.0;
}

double vidurkis(const vector<int>& paz) {
    if (paz.empty()) return 0.0;
    return static_cast<double>(std::accumulate(paz.begin(), paz.end(), 0)) / paz.size();
}

bool i_skaiciu(const string& tekstas, int& rezultatas) {
    try {
        size_t pabaiga;
        int sk = std::stoi(tekstas, &pabaiga);
        if (tekstas.find_first_not_of(" \t\r", pabaiga) != string::npos) return false;
        rezultatas = sk;
        return true;
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}



int nuskaityti_pazymi(std::istream& stream, size_t eilutes_nr, const string& pavadinimas) {
    string reiksme;
    int pazymys = 0;
    if (!(stream >> reiksme)) {
        cout << "Eilutėje " << eilutes_nr << " (" << pavadinimas << "): trūksta reikšmės! Įrašomas 0.\n";
    } else if (!i_skaiciu(reiksme, pazymys)) {
        cout << "Eilutėje " << eilutes_nr << " (" << pavadinimas << "): „" << reiksme
             << "“ nėra tinkamas skaičius! Įrašomas 0.\n";
        pazymys = 0;
    } else if (pazymys < MIN_PAZ || pazymys > MAX_PAZ) {
        cout << "Eilutėje " << eilutes_nr << " (" << pavadinimas << "): " << pazymys << " nepatenka į intervalą ["
             << MIN_PAZ << "; " << MAX_PAZ << "]! Įrašomas 0.\n";
        pazymys = 0;
    }
    return pazymys;
}

size_t utf8_ilgis(const string& tekstas) {
    size_t ilgis = 0;
    for (unsigned char c : tekstas) {
        if ((c & 0xC0) != 0x80) ilgis++;
    }
    return ilgis;
}

int utf8_plotis(const string& tekstas) {
    return static_cast<int>(PLOTIS + tekstas.size() - utf8_ilgis(tekstas));
}

void spausdinti(const studentas& st, Statistika statistika, std::ofstream& output) {
    output << std::left << std::setw(utf8_plotis(st.vardas)) << st.vardas << "|";
    output << std::left << std::setw(utf8_plotis(st.pavarde)) << st.pavarde << "|";
    double vid = 0.4 * vidurkis(st.paz) + 0.6 * st.exam;
    double med = 0.4 * mediana(st.paz) + 0.6 * st.exam;
    if (statistika == Statistika::Vidurkis) {
        output << std::right << std::setw(PLOTIS) << std::fixed << std::setprecision(2) << vid << "|\n";
    } else if (statistika == Statistika::Mediana) {
        output << std::right << std::setw(PLOTIS) << std::fixed << std::setprecision(2) << med << "|\n";
    } else if (statistika == Statistika::Abu) {
        output << std::right << std::setw(PLOTIS) << std::fixed << std::setprecision(2) << vid << "|" << std::setw(PLOTIS)
             << med << "|\n";
    }
}

void generuotiFaila(const int n) {
    const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(static_cast<std::mt19937::result_type>(seed));
    std::uniform_int_distribution<int> pazymiu_dist(MIN_PAZ, MAX_PAZ);
    std::uniform_int_distribution<int> nd(1,20);
    int nd_kiekis = nd(gen);
    cout << "Generuojamas failas kursiokai" + std::to_string(n) + ".txt\n";
    std::ofstream output;
    output.open("kursiokai" + std::to_string(n) + ".txt");

    output << std::left << std::setw(PLOTIS) << "Vardas" << "|";
    output << std::left << std::setw(utf8_plotis("Pavardė")) << "Pavardė" << "|";
    for (int i=0; i<nd_kiekis; i++) {
        output << std::left << std::setw(PLOTIS) << "ND" + std::to_string(i+1) << "|";
    }
    output << std::left << std::setw(PLOTIS) << "Egzaminas" << "|\n";

    for (int i = 0; i < n; i++) {
        output << std::left <<std::setw(PLOTIS) << "Vardenis" + std::to_string(i+1) <<"|";
        output << std::left << std::setw(PLOTIS) << "Pavardenis" + std::to_string(i+1)<< "|";
        for (int j=0; j<nd_kiekis; j++) {
            output << std::right << std::setw(PLOTIS) << pazymiu_dist(gen) <<"|" ;
            }
        output << std::right << std::setw(PLOTIS) <<pazymiu_dist(gen) <<"|\n" ;
        }


}

int main() {



#ifdef _WIN32
     SetConsoleOutputCP(CP_UTF8);
     SetConsoleCP(CP_UTF8);
#endif
    const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(static_cast<std::mt19937::result_type>(seed));
    std::uniform_int_distribution<int> pazymiu_dist(MIN_PAZ, MAX_PAZ);
    double kiekiai[5];
    for (int i =1000; i<=10000000; i=i*10) {
        generuotiFaila(i);
    }




//
//     vector<studentas> grupe;
//     bool zinomas_sk = false;
//     string eilute;
//
//     cout << "Ar namų darbų ir egzaminų rezultatus įvesti ranka, nuskaityti nuo failo ar generuoti atsitiktinai?\n"
//          << "[0] - įvesti ranka\n"
//          << "[1] - nuskaityti iš failo\n"
//          << "[2] - generuoti atsitiktinai\n";
//     const auto rezimas = static_cast<Rezimas>(ivesti_sk("Pasirinkite programos režimą: ", 0, 2));
//
//     if (rezimas == Rezimas::Ivesti) {
//         cout << "Ar žinomas namų darbų skaičius? [y/n] ";
//         while (std::getline(cin, eilute)) {
//             if (eilute == "y") {
//                 zinomas_sk = true;
//                 break;
//             }
//             if (eilute == "n") {
//                 zinomas_sk = false;
//                 break;
//             }
//             cout << "Įveskite \"n\" arba \"y\"\n";
//             cout << "Ar žinomas namų darbų skaičius? [y/n] ";
//         }
//     } else {
//         zinomas_sk = true;
//     }
//
//     if (rezimas != Rezimas::Nuskaityti) {
//         const int studkiekis = ivesti_sk("Kiek yra studentų? ", 0, BE_RIBOS);
//         for (int i = 0; i < studkiekis; i++) {
//             studentas st;
//
//             cout << "Įveskite vardą: ";
//             cin >> st.vardas;
//
//             cout << "Įveskite pavardę: ";
//             cin >> st.pavarde;
//             cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//             if (zinomas_sk) {
//                 const int kiekis = ivesti_sk("Kiek studentas turi pažymių? ", 1, BE_RIBOS);
//
//                 if (rezimas == Rezimas::Ivesti) {
//                     for (int j = 1; j <= kiekis; j++) {
//                         st.paz.push_back(
//                             ivesti_sk("Įveskite " + std::to_string(j) + "-ąjį pažymį: ", MIN_PAZ, MAX_PAZ));
//                     }
//                 } else {
//                     cout << "Suvesti atsitiktiniai pažymiai: ";
//                     for (int j = 0; j < kiekis; j++) {
//                         const int sk = pazymiu_dist(gen);
//                         st.paz.push_back(sk);
//                         cout << sk << " ";
//                     }
//                     cout << '\n';
//                 }
//             } else {
//                 while (true) {
//                     cout << "Įveskite " << st.paz.size() + 1 << "-ąjį pažymį (Enter, kad užbaigti): ";
//                     if (!std::getline(cin, eilute) || eilute.empty()) break;
//
//                     int pazymys;
//                     if (!i_skaiciu(eilute, pazymys)) {
//                         cout << "Įvesta netinkama reikšmė (ne skaičius arba per didelis skaičius)!\n";
//                     } else if (pazymys < MIN_PAZ || pazymys > MAX_PAZ) {
//                         cout << "Pažymys turi būti nuo " << MIN_PAZ << " iki " << MAX_PAZ << "!\n";
//                     } else {
//                         st.paz.push_back(pazymys);
//                     }
//                 }
//             }
//
//             if (rezimas == Rezimas::Generuoti) {
//                 st.exam = pazymiu_dist(gen);
//                 cout << "Atsitiktinis egzamino rezultatas: " << st.exam << '\n';
//             } else {
//                 st.exam = ivesti_sk("Įveskite egzamino rezultatą: ", MIN_PAZ, MAX_PAZ);
//             }
//             grupe.push_back(st);
//         }
//     }
//
//     if (rezimas == Rezimas::Nuskaityti) {
//         string failo_pavadinimas;
//         std::ifstream failas;
//         while (true) {
//             cout << "Įveskite failo pavadinimą nuskaitymui. (pvz.: „studentai.txt“): ";
//             if (!(cin >> failo_pavadinimas)) break;
//             failas.open(failo_pavadinimas);
//             if (failas) break;
//             cout << "Failas nerastas.\n";
//             failas.clear();
//         }
//         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//         vector<string> turinys;
//         while (std::getline(failas, eilute)) {
//             turinys.push_back(eilute);
//         }
//
//         if (!failas.is_open()) {
//             cout << "Failas neatidarytas.\n";
//         } else if (turinys.empty()) {
//             cout << "Failas tuščias!\n";
//         } else {
//             std::istringstream antraste(turinys[0]);
//             string zodis;
//             int paz_kiekis = 0;
//             while (antraste >> zodis) {
//                 paz_kiekis++;
//             }
//             paz_kiekis = std::max(paz_kiekis - 3, 0);
//
//             for (size_t i = 1; i < turinys.size(); i++) {
//                 if (turinys[i].empty()) continue;
//                 std::istringstream ss(turinys[i]);
//                 studentas st;
//                 ss >> st.vardas >> st.pavarde;
//                 for (int j = 0; j < paz_kiekis; j++) {
//                     st.paz.push_back(nuskaityti_pazymi(ss, i + 1, "namų darbų pažymys"));
//                 }
//                 st.exam = nuskaityti_pazymi(ss, i + 1, "egzamino rezultatas");
//                 grupe.push_back(st);
//             }
//         }
//         failas.close();
//     }
//
//     cout << "Kokių norite duomenų:\n"
//          << "[0] - vidurkio\n"
//          << "[1] - medianos\n"
//          << "[2] - abiejų\n";
//     const auto statistika = static_cast<Statistika>(ivesti_sk("Pasirinkite: ", 0, 2));
//
//     string outputfile = "output.txt";
//     std::ofstream output;
//     output.open(outputfile);
//
//     output << std::left << std::setw(PLOTIS) << "Vardas" << "|";
//     output << std::left << std::setw(utf8_plotis("Pavardė")) << "Pavardė" << "|";
//     if (statistika == Statistika::Vidurkis) {
//         output << std::left << std::setw(PLOTIS) << "Galutinis (vid.)" << "|\n";
//     } else if (statistika == Statistika::Mediana) {
//         output << std::left << std::setw(PLOTIS) << "Galutinis (med.)" << "|\n";
//     } else if (statistika == Statistika::Abu) {
//         output << std::left << std::setw(PLOTIS) << "Galutinis (vid.)" << "|" << std::setw(PLOTIS) << "Galutinis (med.)"
//              << "|\n";
//     }
//
//     if (statistika != Statistika::Abu) {
//         output << std::string(PLOTIS*3+3, '-') << "\n";
//     } else {
//         output << std::string(PLOTIS*4+4, '-') << "\n";
//     }
//     cout << "Ar norite rūšiuoti rezultatus pagal pavardę? [y/n] ";
//     while (std::getline(cin, eilute)) {
//         if (eilute == "y") {
//             std::sort(grupe.begin(), grupe.end(), [](const studentas& a, const studentas& b) {
//                 if (a.pavarde != b.pavarde) return a.pavarde < b.pavarde;
//                 return a.vardas < b.vardas;
//             });
//             break;
//         }
//         if (eilute == "n") {
//             break;
//         }
//         cout << "Įveskite \"n\" arba \"y\"\n";
//         cout << "Ar norite rūšiuoti rezultatus pagal pavardę? [y/n] ";
//     }
//         for (const studentas& stud : grupe) {
//             spausdinti(stud, statistika, output);
//         }
//         output.close();
//         cout << "Išvesta į " << outputfile << "\n";
    }

