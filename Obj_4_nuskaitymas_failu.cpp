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
    for (int i = 0; i < pazymiai.size(); i++) {
        for (int j = i + 1; j < pazymiai.size(); j++) {
            if (pazymiai[i] > pazymiai[j]) {
                int pazymys = pazymiai[i];
                pazymiai[i] = pazymiai[j];
                pazymiai[j] = pazymys;
            }
        }
    }
}

void rusiuotiStudentus(vector<Studentas>& studentai) {
    for (int i = 0; i < studentai.size() - 1; i++) {
        for (int j = i + 1; j < studentai.size(); j++) {
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
    if (pazymiai.empty()) return 0;
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


// 1. Įvedimo ranka kodas
int gautiPazymi(const string& klausimas) {
    while (true) {
        string skaicius;
        cout << klausimas;
        cin >> skaicius;

        if (skaicius == "-1") return -1;

        try {
            int pazymys = stoi(skaicius);

            if (pazymys >= 0 && pazymys <= 10) {
                return pazymys;
            } else {
                cout << "Klaida: pazymys turi buti tarp 0 ir 10." << endl;
            }
        } catch (const invalid_argument&) {
            cout << "Klaida: iveskite teisinga skaiciu." << endl;
        }
    }
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

// 2. Studentų generavimo kodas
void inicializuotiAtsitiktinius() {
    int random = int(time(0));
    srand(random);
}

int generuotiSkaiciu(int min, int max) {
    return min + (rand() % (max - min + 1));
}

string generuotiVardaPavarde() {
    string raidziuRinkinys;
    char raides[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < 5; i++) {
        char x = raides[rand() % 26];
        raidziuRinkinys += x;
    }
    return raidziuRinkinys;
}

Studentas generuotiAtsitiktiniStudenta() {
    Studentas studentas;
    
    studentas.vardas = generuotiVardaPavarde();
    studentas.pavarde = generuotiVardaPavarde();

    int pazymiuKiekis = generuotiSkaiciu(1, 20);
    for (int i = 0; i < pazymiuKiekis; i++) {
        studentas.pazymiai.push_back(generuotiSkaiciu(0, 10));
    }

    studentas.egzaminoPazymys = generuotiSkaiciu(0, 10);
    studentas.vidurkis = skaiciuotiVidurki(studentas.pazymiai);
    studentas.mediana = skaiciuotiMediana(studentas.pazymiai);
    studentas.galutinisVidurkis = 0.4 * studentas.vidurkis + 0.6 * studentas.egzaminoPazymys;
    studentas.galutineMediana = 0.4 * studentas.mediana + 0.6 * studentas.egzaminoPazymys;

    return studentas;
}

// 3. Failo skaitymo, skaičiavimo kodas
void skaiciuotiIsFailo(Studentas& studentas, bool tinkamiPazymiai, vector<Studentas>& studentai) {
    if (tinkamiPazymiai) {
        if (!studentas.pazymiai.empty()) {
            studentas.egzaminoPazymys = studentas.pazymiai.back();
            studentas.pazymiai.pop_back();

            studentas.vidurkis = skaiciuotiVidurki(studentas.pazymiai);
            studentas.mediana = skaiciuotiMediana(studentas.pazymiai);
            studentas.galutinisVidurkis = 0.4 * studentas.vidurkis + 0.6 * studentas.egzaminoPazymys;
            studentas.galutineMediana = 0.4 * studentas.mediana + 0.6 * studentas.egzaminoPazymys;

            studentai.push_back(studentas);
        } else {
            cout << "Klaida: truksta pazymiu studentui " << studentas.vardas << " " << studentas.pavarde << endl;
        }
    } else {
        cout << "Studentas " << studentas.vardas << " " << studentas.pavarde << " neturi galutiniu pazymiu del neteisingu duomenu." << endl;
    }
}

void skaitytiDuomenisIsFailo(const string& failoPavadinimas, vector<Studentas>& studentai) {
    ifstream failas(failoPavadinimas);
    if (!failas) {
        throw runtime_error("Failo " + failoPavadinimas + " nera.");
    }

    string eilute;
    getline(failas, eilute);

    while (getline(failas, eilute)) {
        istringstream iss(eilute);
        Studentas studentas;
        if (!(iss >> studentas.vardas >> studentas.pavarde)) {
            throw runtime_error("Klaida nuskaitant varda ir pavarde.");
        }

        string pazymysStr;
        bool tinkamiPazymiai = true;

        while (iss >> pazymysStr) {
            try {
                if (pazymysStr.find_first_not_of("0123456789") != string::npos) {
                    throw invalid_argument("Klaida: pazymys turi buti skaicius.");
                }

                int pazymys = stoi(pazymysStr);
                if (pazymys < 0 || pazymys > 10) {
                    throw out_of_range("Klaida: pazymys turi buti tarp 0 ir 10.");
                }

                studentas.pazymiai.push_back(pazymys);
            } catch (const invalid_argument& e) {
                cout << "Klaida: neteisingas pazymys: " << pazymysStr << " - " << e.what() << endl;
                tinkamiPazymiai = false;
                break;
            } catch (const out_of_range& e) {
                cout << e.what() << endl;
                tinkamiPazymiai = false;
                break;
            }
        }

        if (tinkamiPazymiai) {
            skaiciuotiIsFailo(studentas, tinkamiPazymiai, studentai);
        } else {
            cout << "Studentas " << studentas.vardas << " " << studentas.pavarde << " neturi galutiniu pazymiu del neteisingu duomenu." << endl;
        }
    }
}

void programa() {
    vector<Studentas> studentai;
    int pasirinkimas;
    long long studentuKiekis;
    int failoPasirinkimas;

    cout << "1. Ivesti duomenis ranka" << endl;
    cout << "2. Automatiskai generuoti duomenis" << endl;
    cout << "3. Nuskaityti duomenis is failo" << endl;
    cout << "Jusu pasirinkimas: ";
    
    while (!(cin >> pasirinkimas) || (pasirinkimas < 1 || pasirinkimas > 3)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Neteisingas pasirinkimas. Prasome ivesti 1, 2, arba 3: ";
    }

    try {
        switch (pasirinkimas) {
            case 1: {
                cout << "Kiek studentu norite irasyti? ";
                bool validInput = false;

                while (!validInput) {
                    cin >> studentuKiekis;
                    if (cin.fail() || studentuKiekis < 1) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Klaida: Ivestas neteisingas studentu skaicius. Prasome ivesti skaiciu didesni uz 0: ";
                    } else {
                        validInput = true;
                    }
                }

                studentai.resize(studentuKiekis);
                for (Studentas& studentas : studentai) {
                    ivestiStudentoDuomenis(studentas);
                }
                break;
            }

            case 2: {
                cout << "Kiek studentu norite sugeneruoti? ";
                bool validInput = false;

                while (!validInput) {
                    cin >> studentuKiekis;
                    if (cin.fail() || studentuKiekis < 1) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Klaida: Ivestas neteisingas studentu skaicius. Prasome ivesti skaiciu didesni uz 0: ";
                    } else {
                        validInput = true;
                    }
                }

                for (int i = 0; i < studentuKiekis; i++) {
                    studentai.push_back(generuotiAtsitiktiniStudenta());
                }
                break;
            }

            case 3: {
                cout << "Pasirinkite faila (1. studentai10.txt, 2. studentai100.txt, 3. studentai10000.txt, 4. studentai100000.txt, 5. studentai1000000.txt, 6. studentai10_blog.txt, 7. tuscias.txt): ";
                bool validInput = false;

                while (!validInput) {
                    cin >> failoPasirinkimas;
                    if (cin.fail() || failoPasirinkimas < 1 || failoPasirinkimas > 7) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Neteisingas pasirinkimas. Prasome ivesti skaiciu nuo 1 iki 7: ";
                    } else {
                        validInput = true;
                    }
                }

                string failoPavadinimas;
                switch (failoPasirinkimas) {
                    case 1: failoPavadinimas = "studentai10.txt"; break;
                    case 2: failoPavadinimas = "studentai100.txt"; break;
                    case 3: failoPavadinimas = "studentai10000.txt"; break;
                    case 4: failoPavadinimas = "studentai100000.txt"; break;
                    case 5: failoPavadinimas = "studentai1000000.txt"; break;
                    case 6: failoPavadinimas = "studentai10_blog.txt"; break;
                    case 7: failoPavadinimas = "tuscias.txt"; break;
                }

                skaitytiDuomenisIsFailo(failoPavadinimas, studentai);
                break;
            }
        }

        if (studentai.empty()) {
            throw runtime_error("Nera studentu duomenu.");
        }

        rusiuotiStudentus(studentai);

        cout << left << setw(16) << "Pavarde" << setw(16) << "Vardas" << setw(25) << "Galutinis Vidurkis" << " / " << "Galutine Mediana" << endl;
        cout << "-------------------------------------------------------------------------" << endl;

        for (const Studentas& studentas : studentai) {
            cout << left << setw(12) << studentas.pavarde << setw(15) << studentas.vardas 
                 << setw(25) << fixed << setprecision(2) << studentas.galutinisVidurkis 
                 << "   " << fixed << setprecision(2) << studentas.galutineMediana << endl;
        }
    } catch (const exception& e) {
        cout << "Ivyko klaida: " << e.what() << endl;
    }
}

int main() {
    inicializuotiAtsitiktinius();
    
    char pabaiga = 'N';

    while (toupper(pabaiga) != 'T') { 
        programa();

        cout << "Ar norite uzdaryti programa? Jeigu taip - rasykite T, jeigu ne - rasykite N: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> pabaiga; 

        while (toupper(pabaiga) != 'T' && toupper(pabaiga) != 'N') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neteisingas pasirinkimas. Prasome ivesti T arba N: ";
            cin >> pabaiga;
        }
    }
    return 0;
}