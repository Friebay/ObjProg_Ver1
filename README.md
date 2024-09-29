# Studentų pažymių skaičiuoklė

## Aprašymas

Ši programa skirta studentų galutinio įvertinimo (vidurkio ir medianos pagrindu) apskaičiavimui ir duomenų apdorojimui. Programa leidžia:

1. Rankiniu būdu įvesti studentų duomenis.
2. Automatiškai generuoti studentų duomenis.
3. Nuskaityti duomenis iš failo ir juos apdoroti.
4. Generuoti didelius studentų sąrašų failus.
5. Rūšiuoti studentus į dvi kategorijas pagal galutinį balą.
6. Atlikti programos veikimo spartos analizę.

## Funkcionalumas

- Skaičiuoja galutinį studento įvertinimą pagal pažymių vidurkį arba medianą ir egzamino pažymį.
- Leidžia pasirinkti duomenų įvedimo būdą: rankinis įvedimas, automatinė duomenų generacija arba duomenų nuskaitymas iš failo.
- Duomenų rūšiavimas pagal studentų pavardes ir vardus.
- Generuoja penkis atsitiktinius studentų sąrašų failus (1 000, 10 000, 100 000, 1 000 000, 10 000 000 įrašų).
- Rūšiuoja studentus į dvi kategorijas: "neišlaikiusius" (galutinis balas < 5.0) ir "išlaikiusius" (galutinis balas >= 5.0).
- Išveda surūšiuotus studentus į du atskirus failus.
- Matuoja programos veikimo spartą, įskaitant failų kūrimą, duomenų nuskaitymą, rūšiavimą ir išvedimą.

## Reikalavimai

- C++11 arba naujesnė versija.
- Standartinė šablonų biblioteka (STL).

## Naudojimas

1. Susikompiliuokite programą arba atsisiųskite sukompiliuotą versiją iš Releases.
2. Paleiskite programą ir sekite ekrane pateikiamus nurodymus.
3. Pasirinkite norimą veiksmą iš meniu:
   - Įvesti duomenis ranka
   - Automatiškai generuoti duomenis
   - Nuskaityti duomenis iš failo
   - Sukurti atsitiktinių studentų failus
   - Nuskaityti sugeneruotus failus ir išvesti į naują failą
   - Padalinti rezultatų failą į išlaikiusius ir neišlaikiusius
   - Sugeneruoti 5 atsitiktinius failus
   - Vykdyti visus žingsnius visiems studentų kiekiams
4. Programa atliks pasirinktą veiksmą ir pateiks rezultatus arba spartos analizę.

## Spartos analizė

Programa matuoja šių veiksmų spartą:

- Failų kūrimas
- Duomenų nuskaitymas iš failų
- Studentų rūšiavimas į dvi kategorijas
- Surūšiuotų studentų išvedimas į du naujus failus

Spartos analizės rezultatai pateikiami konsolėje po kiekvieno veiksmo.