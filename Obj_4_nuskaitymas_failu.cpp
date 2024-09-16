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

void rusiuotiPazymius(vector<int>& pazymiai) {
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

void rusiuotiStudentus(vector<Studentas>& studentai) {
    for (int i = 0; i < studentai.size() - 1; ++i) {
        for (int j = i + 1; j < studentai.size(); ++j) {
            if (studentai[i].pavarde > studentai[j].pavarde || 
               (studentai[i].pavarde == studentai[j].pavarde && studentai[i].vardas > studentai[j].vardas)) {
                Studentas temp = studentai[i];
                studentai[i] = studentai[j];
                studentai[j] = temp;
            }
        }
    }
}

float skaiciuotiMediana(vector<int>& pazymiai) {
    rusiuotiPazymius(pazymiai); 
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

void skaitytiDuomenisIsFailo(const string& failoVardas, vector<Studentas>& studentai) {
    ifstream failas(failoVardas);
    if (!failas) {
        cout << "Failo " << failoVardas << " nera." << endl;
        system("pause");
    }

    string eilute;
    getline(failas, eilute);

    while (getline(failas, eilute)) {
        istringstream iss(eilute);
        Studentas studentas;
        iss >> studentas.vardas >> studentas.pavarde;

        int pazymys;
        while (iss >> pazymys) {
            studentas.pazymiai.push_back(pazymys);
        }

        studentas.egzaminoPazymys = studentas.pazymiai.back();
        studentas.pazymiai.pop_back();

        studentas.vidurkis = skaiciuotiVidurki(studentas.pazymiai);
        studentas.mediana = skaiciuotiMediana(studentas.pazymiai);
        studentas.galutinisVidurkis = 0.4 * studentas.vidurkis + 0.6 * studentas.egzaminoPazymys;
        studentas.galutineMediana = 0.4 * studentas.mediana + 0.6 * studentas.egzaminoPazymys;

        studentai.push_back(studentas);
    }
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

string generuotiVardaPavarde() {
    string vardasPavarde;
    char raides[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < 5; ++i) {
        char x = raides[rand() % 26];
        vardasPavarde += x;
    }
    return vardasPavarde;
}

Studentas generuotiAtsitiktiniStudenta() {
    Studentas studentas;
    
    studentas.vardas = generuotiVardaPavarde();
    studentas.pavarde = generuotiVardaPavarde();

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
    if (studentas.egzaminoPazymys == -1){
        studentas.egzaminoPazymys = 0;
    }

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
    long long studentuKiekis;

    cout << "1. Ivesti duomenis ranka" << endl;
    cout << "2. Automatiskai generuoti duomenis" << endl;
    cout << "3. Nuskaityti duomenis is failo" << endl;
    cout << "Jusu pasirinkimas: ";
    cin >> pasirinkimas;

    if (pasirinkimas == '1') {
        cout << "Kiek studentu norite irasyti? ";
        cin >> studentuKiekis;
        if (studentuKiekis < 1 || studentuKiekis > 2147483647) {
            cout << "Klaida: Studentu skaicius turi buti daugiau nei 0 ir maziau nei 2147483647." << endl << "Programa uzdaroma." << endl;;
            system("pause");
            return 0;
        }
        studentai.resize(studentuKiekis);
        for (Studentas& studentas : studentai) {
            ivestiStudentoDuomenis(studentas);
        }
    } else if (pasirinkimas == '2') {
        cout << "Kiek studentu norite sugeneruoti? ";
        cin >> studentuKiekis;
        if (studentuKiekis < 1 || studentuKiekis > 2147483647) {
            cout << "Klaida: Studentu skaicius turi buti daugiau nei 0 ir maziau nei 2147483647." << endl << "Programa uzdaroma." << endl;;
            system("pause");
            return 0;
        }
        for (int i = 0; i < studentuKiekis; i++) {
            studentai.push_back(generuotiAtsitiktiniStudenta());
        }
    } else if (pasirinkimas == '3') {
        cout << "Pasirinkite faila (1. studentai10.txt, 2. studentai100.txt, 3. studentai10000.txt, 4. studentai100000.txt, 5. studentai1000000.txt): ";
        int failoPasirinkimas;
        cin >> failoPasirinkimas;
        
        string failoVardas;
        if (failoPasirinkimas == 1) {
            failoVardas = "C:/Users/zabit/Documents/GitHub/ObjProg_Ver1/stud_duomenys/studentai10.txt";
        } else if (failoPasirinkimas == 2) {
            failoVardas = "C:/Users/zabit/Documents/GitHub/ObjProg_Ver1/stud_duomenys/studentai100.txt";
        } else if (failoPasirinkimas == 3) {
            failoVardas = "C:/Users/zabit/Documents/GitHub/ObjProg_Ver1/stud_duomenys/studentai10000.txt";
        } else if (failoPasirinkimas == 4) {
            failoVardas = "C:/Users/zabit/Documents/GitHub/ObjProg_Ver1/stud_duomenys/studentai100000.txt";
        } else if (failoPasirinkimas == 5) {
            failoVardas = "C:/Users/zabit/Documents/GitHub/ObjProg_Ver1/stud_duomenys/studentai1000000.txt";
        } else {
            cout << "Neteisingas pasirinkimas." << endl << "Programa uzdaroma." << endl;;
            system("pause");
            return 0;
        }
        skaitytiDuomenisIsFailo(failoVardas, studentai);
    } else {
        cout << "Neteisingas pasirinkimas." << endl << "Programa uzdaroma." << endl;
        system("pause");
        return 0;
    }

    rusiuotiStudentus(studentai);

    cout << left << setw(16) << "Pavarde" << setw(16) << "Vardas" 
         << setw(25) << "Galutinis Vidurkis" << " / " << "Galutine Mediana" << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    for (const Studentas& studentas : studentai) {
        cout << left << setw(12) << studentas.pavarde << setw(15) << studentas.vardas << setw(25) << fixed << setprecision(2) << studentas.galutinisVidurkis << "   " << fixed << setprecision(2) << studentas.galutineMediana << endl;
    }
    system("pause");

    return 0;
}
