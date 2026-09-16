#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using std::string;
using std::vector;

struct studentas {
    string vardas, pavarde;
    vector<int> paz;
    int exam;
};

double mediana(const vector<int>& paz) {
    if (paz.empty()) return 0.0;
    vector<int> kopija = paz;
    sort(kopija.begin(), kopija.end());
    if (kopija.size() % 2 == 1) {
        return kopija[kopija.size() / 2];
    }
    return (kopija[(kopija.size() - 1) / 2] + kopija[kopija.size() / 2]) / 2.0;
}

double vidurkis(const vector<int>& paz) {
    if (paz.empty()) return 0.0;
    return static_cast<double>(std::accumulate(paz.begin(), paz.end(), 0)) / paz.size();
}

void ivesti_sk(int& sk) {
    bool teisinga = false;
    std::string line;
    while (!teisinga) {
        if (!std::getline(std::cin, line)) {
            sk = 0;
            return;
        }
        try {
            sk = std::stoi(line);
            teisinga = true;
        } catch (const std::invalid_argument&) {
            std::cout << "Įvestas ne skaičius, bandykite vėl: ";
        } catch (const std::out_of_range&) {
            std::cout << "Įvestas per didelis skaičius, bandykite vėl: ";
        }
    }
}

void print(const studentas& st, int stats) {
    std::cout << std::left << std::setw(20) << st.vardas << "|";
    std::cout << std::left << std::setw(20) << st.pavarde << "|";
    double vid = 0.4 * vidurkis(st.paz) + 0.6 * st.exam;
    double med = 0.4 * mediana(st.paz) + 0.6 * st.exam;
    if (stats == 0) {
        std::cout << std::right << std::setw(20) << std::fixed << std::setprecision(2) << vid << "|" << std::endl;
    } else if (stats == 1) {
        std::cout << std::right << std::setw(20) << std::fixed << std::setprecision(2) << med << "|" << std::endl;
    } else if (stats == 2) {
        std::cout << std::right << std::setw(20) << std::fixed << std::setprecision(2) << vid << "|"
                  << std::setw(20) << med << "|" << std::endl;
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    vector<studentas> grupe;
    studentas st;
    int studkiekis;
    int stats = -1;
    bool zinomassk = false;
    bool ivesti = false;
    bool nuskaityti = false;
    bool generuoti = false;
    bool teisinga = false;
    std::string eilute;

    std::cout << "Ar namų darbų ir egzaminų rezultatus įvesti ranka, nuskaityti nuo failo ar generuoti atsitiktinai?" << std::endl;
    std::cout << "Spauskite [0], kad įvesti ranka; [1], kad nuskaityti iš failo; [2], kad generuoti atsitiktinai. ";
    while (std::getline(std::cin, eilute)) {
        if (eilute == "0") {
            ivesti = true;
            break;
        }
        if (eilute == "1") {
            nuskaityti = true;
            break;
        }
        if (eilute == "2") {
            generuoti = true;
            break;
        }
        std::cout << "Įveskite 0, 1 arba 2." << std::endl;
        std::cout << "Spauskite [0], kad įvesti ranka; [1], kad nuskaityti iš failo; [2], kad generuoti atsitiktinai. ";
    }

    if (ivesti) {
        std::cout << "Ar žinomas namų darbų skaičius? [y/n] ";
        while (std::getline(std::cin, eilute)) {
            if (eilute == "y") {
                zinomassk = true;
                break;
            }
            if (eilute == "n") {
                zinomassk = false;
                break;
            }
            std::cout << "Įveskite \"n\" arba \"y\"" << std::endl;
            std::cout << "Ar žinomas namų darbų skaičius? [y/n] ";
        }
    } else {
        zinomassk = true;
    }

    if (!nuskaityti) {
        std::cout << "Kiek yra studentų? ";
        ivesti_sk(studkiekis);
        for (int i = 0; i < studkiekis; i++) {
            std::cout << "Įveskite vardą: ";
            std::cin >> st.vardas;

            std::cout << "Įveskite pavardę: ";
            std::cin >> st.pavarde;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            int kiekis;
            if (zinomassk) {
                std::cout << "Kiek studentas turi pažymių? ";
                ivesti_sk(kiekis);
                while (kiekis <= 0) {
                    std::cout << "Kiekis turi būti teigiamas! " << std::endl;
                    std::cout << "Kiek studentas turi pažymių? ";
                    ivesti_sk(kiekis);
                }
                int sk;
                if (!generuoti) {
                    for (int j = 0; j < kiekis; j++) {
                        std::cout << "Įveskite " << j + 1 << "-ąjį pažymį: ";
                        ivesti_sk(sk);
                        st.paz.push_back(sk);
                    }
                } else {
                    std::cout << "Suvesti atsitiktiniai pažymiai: ";
                    for (int j = 0; j < kiekis; j++) {
                        sk = std::rand() % 11;
                        st.paz.push_back(sk);
                        std::cout << sk << " ";
                    }
                    std::cout << std::endl;
                }
            }

            if (!zinomassk) {
                int j = 1;
                std::cout << "Įveskite 1-ąjį pažymį (Enter, kad užbaigti): ";

                while (!teisinga) {
                    try {
                        while (std::getline(std::cin, eilute) && !eilute.empty()) {
                            int paz = std::stoi(eilute);
                            st.paz.push_back(paz);
                            j++;
                            std::cout << "Įveskite " << j << "-ąjį pažymį (Enter, kad užbaigti): ";
                        }
                        teisinga = true;
                    } catch (const std::invalid_argument&) {
                        std::cout << "Įvestas ne skaičius!" << std::endl;
                        std::cout << "Įveskite " << j << "-ąjį pažymį (Enter, kad užbaigti): ";
                    } catch (const std::out_of_range&) {
                        std::cout << "Įvestas per didelis skaičius!" << std::endl;
                        std::cout << "Įveskite " << j << "-ąjį pažymį (Enter, kad užbaigti): ";
                    }
                }
                teisinga = false;
            }

            if (generuoti) {
                st.exam = std::rand() % 11;
                std::cout << "Atsitiktinis egzamino rezultatas: " << st.exam << std::endl;
            } else {
                std::cout << "Įveskite egzamino rezultatą: ";
                ivesti_sk(st.exam);
            }
            grupe.push_back(st);
            st.pavarde.clear();
            st.vardas.clear();
            st.paz.clear();
            st.exam = 0;
        }
    }

    if (nuskaityti) {
        string filename;
        string rez;
        string skip;
        vector<string> turinys;
        std::ifstream File;
        int pazcount = 0;
        while (true) {
            std::cout << "Įveskite failo pavadinimą nuskaitymui. (pvz.: „studentai.txt“): ";
            std::cin >> filename;
            File.open(filename);
            if (!File) {
                std::cout << "Failas nerastas. " << std::endl;
                File.clear();
            } else {
                break;
            }
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (std::getline(File, rez)) {
            turinys.push_back(rez);
        }
        File.close();

        if (turinys.empty()) {
            std::cout << "Failas tuščias!" << std::endl;
        } else {
            string header = turinys[0];
            std::istringstream shead(header);
            while (shead >> skip) {
                pazcount++;
            }
            pazcount = pazcount - 3;
            if (pazcount < 0) pazcount = 0;
            for (size_t i = 1; i < turinys.size(); i++) {
                if (turinys[i].empty()) continue;
                std::istringstream ss(turinys[i]);
                ss >> st.vardas >> st.pavarde;
                string a;
                for (int j = 0; j < pazcount; j++) {
                    try {
                        ss >> a;
                        st.paz.push_back(stoi(a));
                    } catch (const std::invalid_argument&) {
                        std::cout << "Eilutėje " << i + 1 << " tarp namų darbų pažymių įvestas ne skaičius! Įrašomas 0." << std::endl;
                        st.paz.push_back(0);
                    } catch (const std::out_of_range&) {
                        std::cout << "Eilutėje " << i + 1 << " reikšmė per didelė! Įrašomas 0." << std::endl;
                        st.paz.push_back(0);
                    }
                }
                try {
                    ss >> a;
                    st.exam = std::stoi(a);
                } catch (const std::invalid_argument&) {
                    std::cout << "Eilutėje " << i + 1 << " egzamino rezultatas ne skaičius! Įvedamas 0." << std::endl;
                    st.exam = 0;
                } catch (const std::out_of_range&) {
                    std::cout << "Eilutėje " << i + 1 << " egzamino rezultatas per didelis! Įvedamas 0." << std::endl;
                    st.exam = 0;
                }
                ss.clear();
                grupe.push_back(st);
                st.pavarde.clear();
                st.vardas.clear();
                st.paz.clear();
                st.exam = 0;
            }
        }
    }

    std::cout << "Kokių norite duomenų:" << std::endl
              << "[0] - vidurkio" << std::endl
              << "[1] - medianos" << std::endl
              << "[2] - abiejų" << std::endl;
    while (!teisinga) {
        if (!std::getline(std::cin, eilute)) break;
        try {
            stats = std::stoi(eilute);
            if (stats == 0 || stats == 1 || stats == 2) {
                teisinga = true;
            } else {
                std::cout << "Įvesta netinkama reikšmė, bandykite vėl: ";
            }
        } catch (const std::invalid_argument&) {
            std::cout << "Įvesta netinkama reikšmė, bandykite vėl: ";
        } catch (const std::out_of_range&) {
            std::cout << "Įvesta netinkama reikšmė, bandykite vėl: ";
        }
    }
    if (!teisinga) stats = 0;
    teisinga = false;

    std::cout << std::left << std::setw(20) << "Vardas" << "|";
    std::cout << std::left << std::setw(20) << "Pavarde" << "|";
    if (stats == 0) {
        std::cout << std::left << std::setw(20) << "Galutinis (vid.)" << "|" << std::endl;
    } else if (stats == 1) {
        std::cout << std::left << std::setw(20) << "Galutinis (med.)" << "|" << std::endl;
    } else if (stats == 2) {
        std::cout << std::left << std::setw(20) << "Galutinis (vid.)" << "|"
                  << std::setw(20) << "Galutinis (med.)" << "|" << std::endl;
    }

    for (const studentas& stud : grupe) {
        print(stud, stats);
    }
}
