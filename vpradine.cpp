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
    bool teisinga = false;
    std::string eilute;
    std::cout << "Kiek yra studentų? ";
    while (!teisinga) {
        try {
            std::getline(std::cin, eilute);
            studkiekis = std::stoi(eilute);
            teisinga = true;
        } catch (const std::invalid_argument&) {
            std::cout << "Įvestas ne skaičius, bandykite vėl: ";
        }
    }
    teisinga = false;
    for(int i = 0; i < studkiekis; i++) {
        std::cout << "Įveskite vardą: ";
        std::cin >> st.vardas;

        std::cout <<"Įveskite pavardę: ";
        std::cin >> st.pavarde;
        std::cin.ignore();
        int j = 1;
        std::cout << "Įveskite " << j <<"-ąjį pažymį (Enter, kad užbaigti; \"r\", kad sugeneruoti atsitiktinai): ";
        j++;
        while (!teisinga) {
            try {
                while (std::getline(std::cin, eilute) && !eilute.empty()) {
                    if (eilute == "r") {
                        st.paz.push_back(std::rand()%11);
                        std::cout << "Įvestas sk. "<<st.paz.back()<<std::endl;
                    } else {
                        int paz = std::stoi(eilute);
                        st.paz.push_back(paz);
                    }
                    std::cout << "Įveskite " << j <<"-ąjį pažymį (Enter, kad užbaigti; \"r\", kad sugeneruoti atsitiktinai): ";
                    j++;

                }
                teisinga = true;

            } catch(const std::invalid_argument&) {
                    std::cout << "Įvestas ne skaičius!" << std::endl;
                    std::cout << "Įveskite " << j <<"-ąjį pažymį (Enter, kad užbaigti; \"r\", kad sugeneruoti atsitiktinai): ";
            }
        }
        teisinga = false;

        std::cout << "Įveskite egzamino rezultatą (\"r\", kad generuoti atsitikinai): ";


        while (!teisinga) {
            try {
                std::getline(std::cin, eilute);
                if (eilute == "r") {
                    st.exam = std::rand()%11;
                    std::cout << "Įvestas sk. "<<st.exam<<std::endl;
                }
                else {
                    st.exam = std::stoi(eilute);
                }
                teisinga = true;
            } catch (const std::invalid_argument&) {
                std::cout << "Įvestas ne skaičius, bandykite vėl: ";
            }
        }
        teisinga = false;
        grupe.push_back(st);
        st.pavarde.clear();
        st.vardas.clear();
        st.paz.clear();
        st.exam = 0;
    }
    std::cout << "Kokių norite duomenų:" << std::endl<< "[0] - vidurkio" << std::endl << "[1] - medianos" << std::endl << "[2] - abiejų"<<std::endl;
    while (!teisinga and (stats != 0 or stats != 1 or stats != 2)) {
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
