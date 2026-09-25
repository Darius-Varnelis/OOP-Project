#include <vector>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

#include "failai.h"
#include "studentas.h"

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    const int minfailas = 1000;
    const int maxfailas = 10000000;

    for (int i = minfailas; i <= maxfailas; i *= 10) {
        generuotiFaila(i);
    }
    for (int i = minfailas; i <= maxfailas; i *= 10) {
        std::vector<studentas> grupe;
        nuskaitytiStudentus(grupe, failoPavadinimas("kursiokai", i));
        for (studentas& st : grupe) {
            skaiciuotiGalutini(st);
        }
        isvestiStudentus(grupe, i);
    }
}
