#include "studentas.h"

#include <algorithm>

#include "utils.h"

void skaiciuotiGalutini(Studentas& st) {
    st.galutinis = 0.4 * vidurkis(st.paz) + 0.6 * st.exam;
}

void rusiuotiStudentus(std::vector<Studentas>& grupe, Rusiuoti r) {
    if (r == Rusiuoti::Varda) {
        std::sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            if (a.vardas != b.vardas)return a.vardas < b.vardas;
            if (a.pavarde != b.pavarde) return a.pavarde < b.pavarde;
            return a.galutinis < b.galutinis;            });
    }
    else if (r == Rusiuoti::Pavarde) {
        std::sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            if (a.pavarde != b.pavarde) return a.pavarde < b.pavarde;
            if (a.vardas != b.vardas)return a.vardas < b.vardas;
            return a.galutinis < b.galutinis;            });
    }
    else {
        std::sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            if (a.galutinis != b.galutinis) return a.galutinis < b.galutinis;
            if (a.pavarde != b.pavarde) return a.pavarde < b.pavarde;
            return a.vardas < b.vardas;
            });
    }
}
