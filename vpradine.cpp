#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using std::string;
using std::vector;
struct studentas {
    string vardas, pavarde;
    vector<int> paz;
    int exam;
};
int mediana(vector<int> paz) {
    sort(paz.begin(), paz.end());
    if (paz.size() % 2 == 1) {
        return paz[paz.size()/2];
    }
    return (paz[(paz.size()-1)/2]+paz[paz.size()/2])/2;
}
int vidurkis(vector<int> paz) {
    return std::accumulate(paz.begin(), paz.end(), 0)/paz.size();
}
void ivesti_sk(int& sk) {
    bool teisinga = false;
    std::string line;
    while (!teisinga) {
        try {
            std::getline(std::cin, line);
            sk = std::stoi(line);
            teisinga = true;
        } catch (const std::invalid_argument&) {
            std::cout << "Įvestas ne skaičius, bandykite vėl: ";
        }
    }
    teisinga = false;
}
void print(studentas& st, int stats) {
    std::cout << std::left << std::setw(20) <<  st.vardas << "|";
    std::cout << std::left << std::setw(20) << st.pavarde << "|";
    float vid = 0.4*vidurkis(st.paz) + 0.6*st.exam;
    float med = 0.4*mediana(st.paz)+0.6*st.exam;
    if (stats == 0) {
        std::cout << std::right << std::setw(20) << std::fixed<< std::setprecision(2)<< vid << "|"<<std::endl;
    }
    else if (stats == 1) {
        std::cout << std::right << std::setw(20) << std::fixed<< std::setprecision(2)<< med << "|"<<std::endl;
    }
    else if (stats == 2) {
        std::cout << std::right << std::setw(20) << std::fixed<< std::setprecision(2)<< vid << "|"<< std::setw(20) << med << "|"<<std::endl;
    }
}

int main(){
    vector<studentas> grupe;
    studentas st;
    int studkiekis;
    int stats = -1;
    bool zinomassk = false;
    bool ran = false;
    bool teisinga = false;
    std::string eilute;

    std::cout << "Ar namų darbų ir egzaminų rezultatus generuoti atsitiktinai? [y/n] ";
    while (std::getline(std::cin,eilute)) {
        if (eilute == "y") {
            ran = true;
            break;

        }
        if (eilute == "n") {
            ran = false;
            break;

        }
        std::cout << "Įveskite \"n\"(ne) arba \"y\"(taip)" << std::endl;
        std::cout << "Ar namų darbų ir egzaminų rezultatus generuoti atsitiktinai? [y/n] ";
    }
    if (!ran) {
        std::cout << "Ar žinomas namų darbų skaičius? [y/n] ";
        while (std::getline(std::cin,eilute) ) {
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
    }else {
        zinomassk = true;
    }
    std::cout << "Kiek yra studentų? ";
    ivesti_sk(studkiekis);
    for(int i = 0; i < studkiekis; i++) {
        std::cout << "Įveskite vardą: ";
        std::cin >> st.vardas;

        std::cout <<"Įveskite pavardę: ";
        std::cin >> st.pavarde;
        std::cin.ignore();

        int kiekis;
        if (zinomassk) {
            std::cout << "Kiek studentas turi pažymių? ";
            ivesti_sk(kiekis);
            while (kiekis == 0) {
                std::cout << "Kiekis negali būti 0! " << std::endl;
                std::cout << "Kiek studentas turi pažymių? ";
                ivesti_sk(kiekis);
            }
            int sk;
            if (!ran) {
                for (int j = 0; j < kiekis; j++) {
                    std::cout << "Įveskite " << j+1 <<"-ąjį pažymį";
                    ivesti_sk(sk);
                    st.paz.push_back(sk);
                }
            } else {
                std::cout << "Suvesti atsitiktiniai pažymiai: ";
                for (int j = 0; j < kiekis; j++) {
                    sk = std::rand()%11;
                    st.paz.push_back(sk);
                    std::cout << sk <<" ";
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
                        std::cout << "Įveskite " << j <<"-ąjį pažymį (Enter, kad užbaigti): ";


                    }
                    teisinga = true;

                } catch(const std::invalid_argument&) {
                    std::cout << "Įvestas ne skaičius!" << std::endl;
                    std::cout << "Įveskite " << j <<"-ąjį pažymį (Enter, kad užbaigti): ";
                }
            }
            teisinga = false;
        }


        if (ran) {
            st.exam = std::rand()%11;
            std::cout << "Atsitiktinis egzamino rezultatas: "<<st.exam<<std::endl;
        }
        else {
            std::cout << "Įveskite egzamino rezultatą: ";
            ivesti_sk(st.exam);
        }
        grupe.push_back(st);
        st.pavarde.clear();
        st.vardas.clear();
        st.paz.clear();
        st.exam = 0;
    }
    std::cout << "Kokių norite duomenų:" << std::endl<< "[0] - vidurkio" << std::endl << "[1] - medianos" << std::endl << "[2] - abiejų"<<std::endl;
    while (!teisinga && (stats != 0 || stats != 1 || stats != 2)) {
        try {
            std::getline(std::cin, eilute);
            stats = std::stoi(eilute);
            teisinga = true;
        } catch (const std::invalid_argument&) {
            std::cout << "Įvestas netinkama reikšmė, bandykite vėl: ";
        }
    }
    teisinga = false;
    std::cout << std::left << std::setw(20) <<  "Vardas" << "|";
    std::cout << std::left << std::setw(20) << "Pavarde" << "|";
    if (stats == 0) {
        std::cout << std::left << std::setw(20) << "Galutinis (vid.)" << "|"<<std::endl;
    }
    else if (stats == 1) {
        std::cout << std::left << std::setw(20) << "Galutinis (med.)"<< "|"<<std::endl;
    }
    else if (stats == 2) {
        std::cout << std::left << std::setw(20) <<  "Galutinis (vid.)" << "|"<< std::setw(20
            ) << "Galutinis (med.)"<< "|"<<std::endl;
    }

    for (studentas& stud : grupe) {
        print(stud, stats);
    }
}
