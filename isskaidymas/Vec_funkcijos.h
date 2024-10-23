#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "Vec_Biblioteka.h"

struct Studentas {
    string vardas, pavarde;
    vector<int> pazymiai;
    int egzaminoPazymys;
    float vidurkis = 0;
    float mediana = 0;
    float galutinisVidurkis = 0;
    float galutineMediana = 0;
};

void Vec_programa();
void ivestiStudentoDuomenis(Studentas& studentas);
void inicializuotiAtsitiktinius();
Studentas generuotiAtsitiktiniStudenta();
int gautiPazymi(const string& klausimas);
float skaiciuotiMediana(vector<int>& pazymiai);
float skaiciuotiVidurki(vector<int>& pazymiai);
void rusiuotiStudentus(vector<Studentas>& studentai);
int generuotiSkaiciu(int min, int max);
string generuotiVardaPavarde();
void generuotiFaila();
void generuotiAtsitiktiniusFailus();
void generuotiStudentuFaila(int studentuKiekis, const string& failoPavadinimas);
void vykdytiVisusZingsnius();

#endif
