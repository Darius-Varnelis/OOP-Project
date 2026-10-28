#include "utils.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <numeric>
#include <vector>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <psapi.h>
#else
#include <fstream>
#endif
using std::string;

size_t utf8Ilgis(const std::string& tekstas) {
    size_t ilgis = 0;
    for (unsigned char c : tekstas) {
        if ((c & 0xC0) != 0x80) ilgis++;
    }
    return ilgis;
}

int utf8Plotis(const std::string& tekstas) {
    return static_cast<int>(PLOTIS + tekstas.size() - utf8Ilgis(tekstas));
}
#ifdef _WIN32
size_t pikineAtmintis() {
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    return pmc.PeakWorkingSetSize;
}

size_t dabartineAtmintis() {
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    return pmc.WorkingSetSize;
}
#else
static size_t procStatusReiksme(const string& raktas) {
    std::ifstream in("/proc/self/status");
    string eilute;
    while (std::getline(in, eilute)) {
        if (eilute.compare(0, raktas.size(), raktas) == 0)
            return std::stoull(eilute.substr(raktas.size())) * 1024;
    }
    return 0;
}

size_t pikineAtmintis() {
    return procStatusReiksme("VmHWM:");
}

size_t dabartineAtmintis() {
    return procStatusReiksme("VmRSS:");
}
#endif
