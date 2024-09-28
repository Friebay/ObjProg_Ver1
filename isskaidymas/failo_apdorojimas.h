#ifndef FAILO_APDOROJIMAS_H
#define FAILO_APDOROJIMAS_H

#include "Biblioteka.h"
#include "funkcijos.h"

void skaitytiDuomenisIsFailo(const string& failoPavadinimas, vector<Studentas>& studentai);
void skaiciuotiIsFailo(Studentas& studentas, bool tinkamiPazymiai, vector<Studentas>& studentai);
void skaitytiIrIsvestiDuomenis(const string& inputFileName, const string& outputFileName);
void padalintiRezultatuFaila(const string& inputFileName, const string& passedFileName, const string& notPassedFileName);

#endif
