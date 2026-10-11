#include "studentas.h"

#include <algorithm>
#include <list>

#include "utils.h"

void skaiciuotiGalutini(Studentas& st) {
    st.galutinis = 0.4 * vidurkis(st.paz) + 0.6 * st.exam;
}
