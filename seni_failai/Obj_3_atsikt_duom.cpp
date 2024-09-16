#include "Biblioteka.h"

struct Studentas {
    string vardas, pavarde;
    vector<int> pazymiai;
    int egzaminoPazymys;
    float vidurkis = 0;
    float mediana = 0;
    float galutinisVidurkis = 0;
    float galutineMediana = 0;
};

void rusiuoti(vector<int>& pazymiai) {
    for (int i = 0; i < pazymiai.size(); ++i) {
        for (int j = i + 1; j < pazymiai.size(); ++j) {
            if (pazymiai[i] > pazymiai[j]) {
                int pazymys = pazymiai[i];
                pazymiai[i] = pazymiai[j];
                pazymiai[j] = pazymys;
            }
        }
    }
}

float skaiciuotiMediana(vector<int>& pazymiai) {
    rusiuoti(pazymiai); 
    int pazymiuKiekis = pazymiai.size();
    if (pazymiuKiekis % 2 == 1) {
        return pazymiai[pazymiuKiekis / 2];
    } else {
        return (pazymiai[pazymiuKiekis / 2 - 1] + pazymiai[pazymiuKiekis / 2]) / 2.0;
    }
}

float skaiciuotiVidurki(vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0; 

    int suma = 0;
    for (int pazymys : pazymiai) {
        suma += pazymys;
    }
    return float(suma) / pazymiai.size();
}

int gautiPazymi(const string& klausimas) {
    while (true) {
        string skaicius;
        cout << klausimas;
        cin >> skaicius;

        if (skaicius == "-1") return -1;

        bool arSkaicius = true;
        for (char simbolis : skaicius) {
            if (simbolis < '0' || simbolis > '9') {
                arSkaicius = false;
                break;
            }
        }

        if (arSkaicius) {
            int pazymys = stoi(skaicius);
            if (pazymys >= 0 && pazymys <= 10) {
                return pazymys;
            } else {
                cout << "Klaida: pazymys turi buti tarp 0 ir 10." << endl;
            }
        } else {
            cout << "Klaida: iveskite teisinga skaiciu." << endl;
        }
    }
}

void inicializuotiAtsitiktinius() {
    int seklos = int(time(0));
    srand(seklos);
}

int generuotiSkaiciu(int min, int max) {
    return min + (rand() % (max - min + 1));
}

Studentas generuotiAtsitiktiniStudenta() {
    Studentas studentas;
    studentas.vardas = "Vardas";
    studentas.pavarde = "Pavarde";

    int pazymiuKiekis = generuotiSkaiciu(1, 20);
    for (int i = 0; i < pazymiuKiekis; ++i) {
        studentas.pazymiai.push_back(generuotiSkaiciu(0, 10));
    }

    studentas.egzaminoPazymys = generuotiSkaiciu(0, 10);
    studentas.vidurkis = skaiciuotiVidurki(studentas.pazymiai);
    studentas.mediana = skaiciuotiMediana(studentas.pazymiai);
    studentas.galutinisVidurkis = 0.4 * studentas.vidurkis + 0.6 * studentas.egzaminoPazymys;
    studentas.galutineMediana = 0.4 * studentas.mediana + 0.6 * studentas.egzaminoPazymys;

    return studentas;
}

void ivestiStudentoDuomenis(Studentas& studentas) {
    cout << "Vardas: ";
    cin >> studentas.vardas;

    cout << "Pavarde: ";
    cin >> studentas.pavarde;

    cout << "Iveskite pazymius (iveskite -1, kad baigtumete):" << endl;
    while (true) {
        int pazymys = gautiPazymi("Pazymys (arba -1, kad baigtumete): ");
        if (pazymys == -1) break;
        studentas.pazymiai.push_back(pazymys);
    }

    studentas.egzaminoPazymys = gautiPazymi("Egzamino pazymys: ");

    if (!studentas.pazymiai.empty()) {
        studentas.vidurkis = skaiciuotiVidurki(studentas.pazymiai);
        studentas.mediana = skaiciuotiMediana(studentas.pazymiai);
    }

    studentas.galutinisVidurkis = 0.4 * studentas.vidurkis + 0.6 * studentas.egzaminoPazymys;
    studentas.galutineMediana = 0.4 * studentas.mediana + 0.6 * studentas.egzaminoPazymys;
}

int main() {
    inicializuotiAtsitiktinius();
    
    vector<Studentas> studentai;
    char pasirinkimas;
    int studentuKiekis;

    cout << "1. Ivesti duomenis ranka\n";
    cout << "2. Automatiskai generuoti duomenis\n";
    cout << "Jusu pasirinkimas: ";
    cin >> pasirinkimas;

    if (pasirinkimas == '1') {
        studentai.resize(2);
        for (Studentas& studentas : studentai) {
            ivestiStudentoDuomenis(studentas);
        }
    } else if (pasirinkimas == '2') {
        cout << "Kiek studentu norite sugeneruoti? ";
        cin >> studentuKiekis;
        for (int i = 0; i < studentuKiekis; ++i) {
            studentai.push_back(generuotiAtsitiktiniStudenta());
        }
    } else {
        cout << "Neteisingas pasirinkimas.\n";
        return 0;
    }

    cout << left << setw(12) << "Pavarde" << setw(15) << "Vardas" 
         << setw(25) << "Galutinis Vidurkis" << " / " << "Galutine Mediana" << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    for (const Studentas& studentas : studentai) {
        cout << left << setw(12) << studentas.pavarde << setw(15) << studentas.vardas << setw(25) << fixed << setprecision(2) << studentas.galutinisVidurkis << "   " << fixed << setprecision(2) << studentas.galutineMediana << endl;
    }

    return 0;
}
