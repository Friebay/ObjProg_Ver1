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

### Pirmos sistemos parametrai
```
CPU: Intel i7-9750H 6C/12T 3.2 GHz
RAM: 1x32GB 2400MHz
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
| 1,000        |17.75|22|4.25|
| 10,000       |106|91.5|-14.5|
| 100,000      |857.25|850|-7.25|
| 1,000,000    |8315.25|8491.5|176.25|
| 10,000,000   |83565.75|87570.25|4004.5|

##### Rezultatu skaidymo laikas (ms)
| Įrašų kiekis | std::vector | std::list | Skirtumas |
|--------------|-------------|------------|-----------|
| 1,000        |0|0|0|
| 10,000       |2.75|1.5|-1.25|
| 100,000      |31.75|38.25|6.5|
| 1,000,000    |359.25|657|297.75|
| 10,000,000   |4385|10963.25|6578.25|

##### Skaidymo irasymas (ms)
| Įrašų kiekis | std::vector | std::list | Skirtumas |
|--------------|-------------|------------|-----------|
| 1,000        |2.5|4.5|2|
| 10,000       |24.75|25.75|1|
| 100,000      |216.5|236.25|19.75|
| 1,000,000    |2182|2330|148|
| 10,000,000   |21501.25|23156|1654.75|

![i7_9750_greitis.png](https://github.com/Friebay/ObjProg_Ver1/blob/v0.3/greicio_duomenys/i7_9750h_greiciai.png?raw=true)

### Antros sistemos parametrai
```
CPU: AMD Ryzen 9 3900X, 8C/12T, 3.9 GHz
RAM: 2x8 GB 3200 MHz
HDD/SSD: Patriot PCIe M.2 P300 512 GB, skaitymo greitis iki 1700 MB/s, įrašymo greitis iki 1100 MB/s
```

### Testavimo rezultatai

#### Vector prieš List palyginimas
- 3 bandymų rezultatai
##### Studentų generavimo laikas (ms)
| Įrašų kiekis | std::vector | std::list | Skirtumas |
|--------------|-------------|------------|-----------|
| 1,000        |1.66666666666667|1.66666666666667|0|
| 10,000       |13.3333333333333|15.3333333333333|2|
| 100,000      |131|135.666666666667|4.66666666666666|
| 1,000,000    |1282|1301.33333333333|19.3333333333333|
| 10,000,000   |13312|13408|96|

##### Sugeneruotu duomenu skaitymo laikas (ms)
| Įrašų kiekis | std::vector | std::list | Skirtumas |
|--------------|-------------|------------|-----------|
| 1,000        |1|1.66666666666667|0.666666666666667|
| 10,000       |13|19.3333333333333|6.33333333333333s|
| 100,000      |138.666666666667|192|53.3333333333333|
| 1,000,000    |1349.33333333333|2162|812.666666666667|
| 10,000,000   |14011.3333333333|20688.3333333333|6677|

##### Rezultatu irasymo laikas (ms)
| Įrašų kiekis | std::vector | std::list | Skirtumas |
|--------------|-------------|------------|-----------|
| 1,000        |1|1.33333333333333|0.333333333333333|
| 10,000       |14.3333333333333|15.3333333333333|1|
| 100,000      |142.666666666667|151|8.33333333333334|
| 1,000,000    |1457|1523.66666666667|66.6666666666667|
| 10,000,000   |14534.3333333333|15345.3333333333|811|

##### Rezultatu skaitymo laikas (ms)
| Įrašų kiekis | std::vector | std::list | Skirtumas |
|--------------|-------------|------------|-----------|
| 1,000        |6.66666666666667|6.66666666666667|0|
| 10,000       |63|68.6666666666667|5.66666666666667|
| 100,000      |629|626|-3|
| 1,000,000    |6270|6296|26|
| 10,000,000   |62649.6666666667|63260.6666666667|611|

##### Rezultatu skaidymo laikas (ms)
| Įrašų kiekis | std::vector | std::list | Skirtumas |
|--------------|-------------|------------|-----------|
| 1,000        |0|0|0|
| 10,000       |1|1|0|
| 100,000      |17.6666666666667|19.3333333333333|1.66666666666666|
| 1,000,000    |219.333333333333|462.666666666667|243.333333333333|
| 10,000,000   |2723.33333333333|7969.66666666667|5246.33333333333|

##### Skaidymo irasymas (ms)
| Įrašų kiekis | std::vector | std::list | Skirtumas |
|--------------|-------------|------------|-----------|
| 1,000        |1|1.33333333333333|0.333333333333333|
| 10,000       |16|16|0|
| 100,000      |161|170|9|
| 1,000,000    |1616.66666666667|1727.33333333333|110.666666666667|
| 10,000,000   |16331|17653.6666666667|1322.66666666667|

![3900x_greiciai.png.png](https://github.com/Friebay/ObjProg_Ver1/blob/v0.3/greicio_duomenys/3900x_greiciai.png?raw=true)


### Išvados

