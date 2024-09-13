#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

struct Duomenys {
    string Vardas, Pavarde;
    vector<int> paz;
    int egz;
    float vidurkis = 0;
    float mediana = 0;
    float galutinis_vid = 0;
    float galutinis_med = 0;
};

void rikiavimas(vector<int>& pazymiu_sarasas) {
    for (int i = 0; i < pazymiu_sarasas.size() - 1; i++) {
        for (int j = i + 1; j < pazymiu_sarasas.size(); j++) {
            if (pazymiu_sarasas[i] > pazymiu_sarasas[j]) {
                int temp = pazymiu_sarasas[i];
                pazymiu_sarasas[i] = pazymiu_sarasas[j];
                pazymiu_sarasas[j] = temp;
            }
        }
    }
}

float medianosRadimas(vector<int>& pazymiu_sarasas) {
    rikiavimas(pazymiu_sarasas);
    int kiekis = pazymiu_sarasas.size();
    if (kiekis % 2 != 0) {
        return pazymiu_sarasas[kiekis / 2];
    }
    else {
        return (pazymiu_sarasas[kiekis / 2 - 1] + pazymiu_sarasas[kiekis / 2]) / 2.0;
    }
}

float vidurkioRadimas(vector<int>& pazymiu_sarasas) {
    int suma = 0;
    
    for (int paz : pazymiu_sarasas) {
        suma += paz;
    }

    if (pazymiu_sarasas.size() == 0) {
        return 0;
    } else {
        return float(suma) / pazymiu_sarasas.size();
    }
}

int gautiPazymi(const string& tekstas) {
    while (true) {
        string pazymys;
        cout << tekstas;
        cin >> pazymys;

        if (pazymys == "-1") return -1;

        bool arSkaicius = true;
        for (char simbolis : pazymys) {
            if (simbolis < '0' || simbolis > '9') {
                arSkaicius = false;
                break;
            }
        }

        if (arSkaicius) {
            int grade = 0;
            for (char simbolis : pazymys) {
                grade = grade * 10 + (simbolis - '0');
            }

            if (grade >= 0 && grade <= 10) {
                return grade;
            } else {
                cout << "Klaida: pazymys turi buti nuo 0 iki 10." << endl;
            }
        } else {
            cout << "Klaida: iveskite tik skaicius." << endl;
        }
    }
}



int main() {
    Duomenys stud1, stud2;
    
    cout << "Vardas: ";
    cin >> stud1.Vardas;

    cout << "Pavarde: ";
    cin >> stud1.Pavarde;

    cout << "Iveskite pazymius (iveskite -1, kad baigtumete):" << endl;

    while (true) {
        int pazymys = gautiPazymi("Pazymys (arba -1 baigti): ");
        if (pazymys == -1) break;
        stud1.paz.push_back(pazymys);
    }

    stud1.egz = gautiPazymi("Egzamino pazymys: ");

    if (!stud1.paz.empty()) {
        stud1.vidurkis = vidurkioRadimas(stud1.paz);
        stud1.mediana = medianosRadimas(stud1.paz);
    }

    stud1.galutinis_vid = 0.4 * stud1.vidurkis + 0.6 * stud1.egz;
    stud1.galutinis_med = 0.4 * stud1.mediana + 0.6 * stud1.egz;

    cout << "Vardas: ";
    cin >> stud2.Vardas;

    cout << "Pavarde: ";
    cin >> stud2.Pavarde;

    while (true) {
        int pazymys = gautiPazymi("Pazymys (arba -1 baigti): ");
        if (pazymys == -1) break;
        stud2.paz.push_back(pazymys);
    }

    stud2.egz = gautiPazymi("Egzamino pazymys: ");

    if (!stud2.paz.empty()) {
        stud2.vidurkis = vidurkioRadimas(stud2.paz);
        stud2.mediana = medianosRadimas(stud2.paz);
    }

    stud2.galutinis_vid = 0.4 * stud2.vidurkis + 0.6 * stud2.egz;
    stud2.galutinis_med = 0.4 * stud2.mediana + 0.6 * stud2.egz;


    cout << left << setw(12) << "Pavarde" << setw(15) << "Vardas" << setw(25) << "Galutinis (Vidurkis)" << " / " << "Galutinis (Mediana)" << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    cout << left << setw(12) << stud1.Pavarde << setw(15) << stud1.Vardas << setw(25) << fixed << setprecision(2) << stud1.galutinis_vid << "   " << fixed << setprecision(2) << stud1.galutinis_med << endl;

    cout << left << setw(12) << stud2.Pavarde << setw(15) << stud2.Vardas << setw(25) << fixed << setprecision(2) << stud2.galutinis_vid << "   " << fixed << setprecision(2) << stud2.galutinis_med << endl;

    return 0;
}