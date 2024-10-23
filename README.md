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

### Sistemos parametrai
```
CPU: i7-9750H 6C/12T
RAM: 32GB 2400MHz
HDD/SSD: Kingston SA2000M8500G, NVMe PCI, skaitymo greitis iki 2200 MB/s, įrašymo greitis iki 2000 MB/s.
```

### Testavimo rezultatai

#### Vector prieš List palyginimas
- 4 bandymų rezultatai
##### Studentų generavimo laikas (ms)
| Įrašų kiekis | std::vector | std::list | Skirtumas |
|--------------|-------------|------------|-----------|
| 1,000        |3.5|8|4.5|
| 10,000       |26.75|31.5|4.75|
| 100,000      |184.75|169.25|-15.5|
| 1,000,000    |1803.75|1604.25|-199.5|
| 10,000,000   |17392.75|17572.25|179.5|

##### Sugeneruotu duomenu skaitymo laikas (ms)
| Įrašų kiekis | std::vector | std::list | Skirtumas |
|--------------|-------------|------------|-----------|
| 1,000        |11.25|25|13.75|
| 10,000       |31.5|44.25|12.75|
| 100,000      |211.75|306.75|95|
| 1,000,000    |2005.25|3212|1206.75|
| 10,000,000   |21035|35745.25|14710.25|

##### Rezultatu irasymo laikas (ms)
| Įrašų kiekis | std::vector | std::list | Skirtumas |
|--------------|-------------|------------|-----------|
| 1,000        |2.75|4.25|1.5|
| 10,000       |22|24.75|2.75|
| 100,000      |197.5|204.5|7|
| 1,000,000    |1975.25|2090.25|115|
| 10,000,000   |20092|21063.5|971.5|

##### Rezultatu skaitymo laikas (ms)
| Įrašų kiekis | std::vector | std::list | Skirtumas |
|--------------|-------------|------------|-----------|
| 1,000        |             |            |           |
| 10,000       |             |            |           |
| 100,000      |             |            |           |
| 1,000,000    |             |            |           |
| 10,000,000   |             |            |           |

##### Rezultatu skaidymo laikas (ms)
| Įrašų kiekis | std::vector | std::list | Skirtumas |
|--------------|-------------|------------|-----------|
| 1,000        |             |            |           |
| 10,000       |             |            |           |
| 100,000      |             |            |           |
| 1,000,000    |             |            |           |
| 10,000,000   |             |            |           |

##### Skaidymo irasymas (ms)
| Įrašų kiekis | std::vector | std::list | Skirtumas |
|--------------|-------------|------------|-----------|
| 1,000        |             |            |           |
| 10,000       |             |            |           |
| 100,000      |             |            |           |
| 1,000,000    |             |            |           |
| 10,000,000   |             |            |           |

### Išvados

