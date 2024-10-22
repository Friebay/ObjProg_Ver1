#ifndef FAILO_APDOROJIMAS_H
#define FAILO_APDOROJIMAS_H

#include "Biblioteka.h"
#include "funkcijos.h"
#include <list>

void skaitytiDuomenisIsFailo(const string& failoPavadinimas, list<Studentas>& studentai, long long& trukmeSkaitymo, long long& trukmeVidurkio);
void skaiciuotiIsFailo(Studentas& studentas, bool tinkamiPazymiai, list<Studentas>& studentai);
void skaitytiIrIsvestiDuomenis(const string& ivestiesFailoPavadinimas, const string& outputFileName, long long& trukmeSkaitymo, long long& trukmeVidurkio, long long& trukmeIrasymo);
void padalintiRezultatuFaila(const string& ivestiesFailoPavadinimas, const string& islaikiusiuFailoPavadinimas, const string& neislaikiusiuFailoPavadinimas, long long& laikasSkaitymo, long long& rusiavimoLaikas, long long& laikasRasymo);

#endif
