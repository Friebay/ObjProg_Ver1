#ifndef LIST_FUNKCIJOS_H
#define LIST_FUNKCIJOS_H

#include "List_Biblioteka.h"

struct List_Studentas {
    string vardas, pavarde;
    list<int> pazymiai;
    int egzaminoPazymys;
    float vidurkis = 0;
    float mediana = 0;
    float galutinisVidurkis = 0;
    float galutineMediana = 0;
};

void List_programa();
void List_ivestiStudentoDuomenis(List_Studentas& studentas);
List_Studentas List_generuotiAtsitiktiniStudenta();
void rusiuotiStudentus(list<List_Studentas>& studentai);
float List_skaiciuotiVidurki(list<int>& pazymiai);
float List_skaiciuotiMediana(list<int>& pazymiai);

#endif
