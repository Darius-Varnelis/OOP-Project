#include "utils.h"

size_t utf8_ilgis(const std::string& tekstas) {
    size_t ilgis = 0;
    for (unsigned char c : tekstas) {
        if ((c & 0xC0) != 0x80) ilgis++;
    }
    return ilgis;
}

int utf8_plotis(const std::string& tekstas) {
    return static_cast<int>(PLOTIS + tekstas.size() - utf8_ilgis(tekstas));
}
