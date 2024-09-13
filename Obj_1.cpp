#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

struct Duomenys {
    string Vardas, Pavarde;
    int paz[5];
    int egz;
    int paz_suma = 0;
    float vidurkis = 0;
    float mediana = 0;
    float galutinis_vid = 0;
    float galutinis_med = 0;
};

void rikiavimas(int pazymiu_sarasas[], int pazymiu_kiekis) {
    for (int i = 0; i < pazymiu_kiekis - 1; i++) {
        for (int j = i + 1; j < pazymiu_kiekis; j++) {
            if (pazymiu_sarasas[i] > pazymiu_sarasas[j]) {
                int temp = pazymiu_sarasas[i];
                pazymiu_sarasas[i] = pazymiu_sarasas[j];
                pazymiu_sarasas[j] = temp;
            }
        }
    }
}

float medianosRadimas(int pazymiu_sarasas[], int pazymiu_kiekis) {
    rikiavimas(pazymiu_sarasas, pazymiu_kiekis);
    if (pazymiu_kiekis % 2 != 0) {
        return pazymiu_sarasas[pazymiu_kiekis / 2];
    }
    else {
        return (pazymiu_sarasas[pazymiu_kiekis / 2 - 1] + pazymiu_sarasas[pazymiu_kiekis / 2]) / 2.0;
    }
}

int main() {
    Duomenys stud1, stud2;

    cout << "Vardas: ";
    cin >> stud1.Vardas;

    cout << "Pavarde: ";
    cin >> stud1.Pavarde;

    for (int i = 0; i < 5; i++) {
        cout << "Pazymys: ";
        cin >> stud1.paz[i];
        stud1.paz_suma += stud1.paz[i];
    }

    cout << "Egzamino pazymys: ";
    cin >> stud1.egz;

    stud1.vidurkis = float(stud1.paz_suma) / 5;
    stud1.mediana = medianosRadimas(stud1.paz, 5);

    stud1.galutinis_vid = 0.4 * stud1.vidurkis + 0.6 * stud1.egz;
    stud1.galutinis_med = 0.4 * stud1.mediana + 0.6 * stud1.egz;

    cout << "Vardas: ";
    cin >> stud2.Vardas;

    cout << "Pavarde: ";
    cin >> stud2.Pavarde;

    for (int i = 0; i < 5; i++) {
        cout << "Pazymys: ";
        cin >> stud2.paz[i];
        stud2.paz_suma += stud2.paz[i];
    }

    cout << "Egzamino pazymys: ";
    cin >> stud2.egz;

    stud2.vidurkis = float(stud2.paz_suma) / 5;
    stud2.mediana = medianosRadimas(stud2.paz, 5);

    stud2.galutinis_vid = 0.4 * stud2.vidurkis + 0.6 * stud2.egz;
    stud2.galutinis_med = 0.4 * stud2.mediana + 0.6 * stud2.egz;

    cout << left << setw(12) << "Pavarde" << setw(15) << "Vardas" << setw(25) << "Galutinis (Vidurkis)" << " / " << "Galutinis (Mediana)" << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    cout << left << setw(12) << stud1.Pavarde << setw(15) << stud1.Vardas << setw(25) << fixed << setprecision(2) << stud1.galutinis_vid << " / " << fixed << setprecision(2) << stud1.galutinis_med << endl;

    cout << left << setw(12) << stud2.Pavarde << setw(15) << stud2.Vardas << setw(25) << fixed << setprecision(2) << stud2.galutinis_vid << " / " << fixed << setprecision(2) << stud2.galutinis_med << endl;

    return 0;
}
