#include "studentas.h"

#include <numeric>

double vidurkis(const std::vector<int>& paz) {
    if (paz.empty()) return 0.0;
    return std::accumulate(paz.begin(), paz.end(), 0.0) / paz.size();
}

void skaiciuotiGalutini(studentas& st) {
    st.galutinis = 0.4 * vidurkis(st.paz) + 0.6 * st.exam;
}
