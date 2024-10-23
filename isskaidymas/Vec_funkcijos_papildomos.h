#ifndef VEC_FUNKCIJOS_PAPILDOMOS_H
#define VEC_FUNKCIJOS_PAPILDOMOS_H

#include "Vec_Biblioteka.h"
#include "Vec_funkcijos.h"

void rusiuotiStudentusPagalPavarde(std::vector<Studentas>& studentai);
void rusiuotiStudentusPagalVarda(std::vector<Studentas>& studentai);
void ivestiStudentoDuomenis(Studentas& studentas);
float skaiciuotiMediana(vector<int>& pazymiai);
float skaiciuotiVidurki(vector<int>& pazymiai);
int generuotiSkaiciu(int min, int max);
string generuotiVardaPavarde();
Studentas generuotiAtsitiktiniStudenta();
void generuotiAtsitiktiniusFailus();
void vykdytiVisusZingsnius();


#endif