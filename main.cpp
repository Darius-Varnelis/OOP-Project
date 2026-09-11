#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <numeric>
#include<cmath>
using std::string;
using std::vector;
struct studentas {
    string vardas, pavarde;
    vector<int> paz;
    int exam;
};
int median(vector<int> paz, int exam) {
    paz.push_back(exam);
    sort(paz.begin(), paz.end());
    if (paz.size() % 2 == 1) {
        return paz[paz.size()/2];
    }
    return (paz[(paz.size()-1)/2]+paz[paz.size()/2])/2;
}
void print(studentas& st, int stats) {
    std::cout << std::left << std::setw(20) <<  st.vardas << "|";
    std::cout << std::left << std::setw(20) << st.pavarde << "|";
    float suma = std::accumulate(st.paz.begin(), st.paz.end(), 0) + st.exam;
    float vidurkis = suma / (st.paz.size() + 1);
    float mediana = median(st.paz, st.exam);
    if (stats == 0) {
        std::cout << std::right << std::setw(20) << std::fixed<< std::setprecision(2)<< vidurkis << "|"<<std::endl;
    }
    else if (stats == 1) {
        std::cout << std::right << std::setw(20) << std::fixed<< std::setprecision(2)<< mediana << "|"<<std::endl;
    }
    else if (stats == 2) {
        std::cout << std::right << std::setw(20) << std::fixed<< std::setprecision(2)<< vidurkis << "|"<< std::setw(20) << mediana << "|"<<std::endl;
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
        std::cout << "Įveskite " << j <<"-ąjį pažymį (arba Enter, kad užbaigti): ";
        j++;
        while (!teisinga) {
            try {
                while (std::getline(std::cin, eilute) && !eilute.empty()) {
                    int paz = std::stoi(eilute);
                    st.paz.push_back(paz);
                    std::cout << "Įveskite " << j <<"-ąjį pažymį (arba Enter, kad užbaigti): ";
                    j++;

                }

            } catch(const std::invalid_argument&) {
                    std::cout << "Įvestas ne skaičius!" << std::endl;
                    std::cout << "Įveskite " << j-1 <<"-ąjį pažymį (arba Enter, kad užbaigti): ";
            }
        }

        std::cout << "Įveskite egzamino rezultatą: ";


        while (!teisinga) {
            try {
                std::getline(std::cin, eilute);
                st.exam = std::stoi(eilute);
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
