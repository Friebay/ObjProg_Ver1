#ifndef FILE_IO_H
#define FILE_IO_H

#include "Biblioteka.h"
#include "student_functions.h"

void skaitytiDuomenisIsFailo(const string& failoPavadinimas, vector<Studentas>& studentai);
void skaiciuotiIsFailo(Studentas& studentas, bool tinkamiPazymiai, vector<Studentas>& studentai);

#endif
