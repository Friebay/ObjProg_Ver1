#ifndef LIST_FAILO_APDOROJIMAS_H
#define LIST_FAILO_APDOROJIMAS_H

#include "List_Biblioteka.h"
#include "List_funkcijos.h"

void List_skaitytiDuomenisIsFailo(const string& failoPavadinimas, list<List_Studentas>& studentai, long long& trukmeSkaitymo, long long& trukmeVidurkio);
void skaiciuotiIsFailo(List_Studentas& studentas, bool tinkamiPazymiai, list<List_Studentas>& studentai);
void skaitytiIrIsvestiDuomenis(const string& ivestiesFailoPavadinimas, const string& outputFileName, long long& trukmeSkaitymo, long long& trukmeVidurkio, long long& trukmeIrasymo);
void List_padalintiRezultatuFaila(const string& ivestiesFailoPavadinimas, const string& islaikiusiuFailoPavadinimas, const string& neislaikiusiuFailoPavadinimas, long long& laikasSkaitymo, long long& rusiavimoLaikas, long long& laikasRasymo);
void List_skaitytiIrIsvestiDuomenis(const string& ivestiesFailoPavadinimas, const string& irasymoFailoPavadinimas, long long& trukmeSkaitymo, long long& trukmeVidurkio, long long& trukmeIrasymo);


#endif
