#ifndef FAILO_APDOROJIMAS_H
#define FAILO_APDOROJIMAS_H

#include "Biblioteka.h"
#include "funkcijos.h"

void skaitytiDuomenisIsFailo(const string& failoPavadinimas, vector<Studentas>& studentai);
void skaiciuotiIsFailo(Studentas& studentas, bool tinkamiPazymiai, vector<Studentas>& studentai);

#endif
