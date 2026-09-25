#ifndef OOP_PROJECT_FAILAI_H
#define OOP_PROJECT_FAILAI_H

#include <string>
#include <vector>

#include "studentas.h"

std::string failoPavadinimas(const std::string& pradzia, int n);

void generuotiFaila(int n);
void nuskaitytiStudentus(std::vector<studentas>& grupe, const std::string& filename);
void isvestiStudentus(const std::vector<studentas>& grupe, int n);

#endif  // OOP_PROJECT_FAILAI_H
