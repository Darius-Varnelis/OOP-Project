#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using std::string;
using std::vector;
struct studentas {
    string vardas, pavarde;
    vector<int> paz;
    int exam;
};
void print(studentas& st) {
    std::cout << std::left << std::setw(10) <<  st.vardas << "|";
    std::cout << std::left << std::setw(10) << st.pavarde << "|";
    for (int i : st.paz) {
        std::cout << std::right << std::setw(10) << i << "|";
    }
    std::cout << std::right << std::setw(10) << st.exam << "|"<<std::endl;
}

int main(){
    vector<studentas> grupe;
    studentas st;
    int kiekis;
    int studkiekis;
    std::cout << "Kiek yra studentų? ";
    std::cin >> studkiekis;
    for(int i = 0; i < studkiekis; i++) {
        std::cout << "Įveskite vardą: ";
        std::cin >> st.vardas;

        std::cout <<"Įveskite pavardę: ";
        std::cin >> st.pavarde;

        std::cout << "Kiek studentas turi pažymių? ";
        std::cin >> kiekis;

        for(int i = 0; i < kiekis; i++) {
            std::cout << "Įveskite " << i+1 <<"-ąjį pažymį: ";
            //cin >> st.paz[i];
            int a;
            std::cin >> a;
            st.paz.push_back(a);
        }

        std::cout << "Įveskite egzamino rezultatą: ";
        std::cin >> st.exam;
        grupe.push_back(st);
        st.pavarde.clear();
        st.vardas.clear();
        st.paz.clear();
        st.exam = 0;
    }


    for (studentas& stud : grupe) {
        print(stud);

    }
}
