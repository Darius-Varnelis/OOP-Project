#include "utils.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <numeric>
#include <vector>
#include <windows.h>
#include <psapi.h>
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