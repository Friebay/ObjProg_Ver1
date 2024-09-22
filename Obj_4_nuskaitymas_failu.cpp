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
        cout << "Failo " << failoPavadinimas << " nera." << endl;
        return;
    }

    string eilute;
    getline(failas, eilute);

    while (getline(failas, eilute)) {
        istringstream iss(eilute);
        Studentas studentas;
        iss >> studentas.vardas >> studentas.pavarde;

        string pazymysStr;
        bool tinkamiPazymiai = true;

        while (iss >> pazymysStr) {
            try {
                if (pazymysStr.find_first_not_of("0123456789") != string::npos) {
                    throw invalid_argument("Klaida: pazymys turi buti skaicius.");
                }

                int pazymys = stoi(pazymysStr);
                if (pazymys < 0 || pazymys > 10) {
                    cout << "Klaida: pazymys turi buti tarp 0 ir 10." << endl;
                    tinkamiPazymiai = false;
                    break;
                }

                studentas.pazymiai.push_back(pazymys);
            } catch (const invalid_argument&) {
                cout << "Klaida: neteisingas pazymys: " << pazymysStr << endl;
                tinkamiPazymiai = false;
                break;
            }
        }

        skaiciuotiIsFailo(studentas, tinkamiPazymiai, studentai);
    }
}

void programa(){
    vector<Studentas> studentai;
    char pasirinkimas;
    long long studentuKiekis;

    cout << "1. Ivesti duomenis ranka" << endl;
    cout << "2. Automatiskai generuoti duomenis" << endl;
    cout << "3. Nuskaityti duomenis is failo" << endl;
    cout << "Jusu pasirinkimas: ";
    cin >> pasirinkimas;

    switch (pasirinkimas) {
        case '1':
            cout << "Kiek studentu norite irasyti? ";
            cin >> studentuKiekis;
            if (studentuKiekis < 1 || studentuKiekis > 2147483647) {
                cout << "Klaida: Studentu skaicius turi buti daugiau nei 0 ir maziau nei 2147483647." << endl;
                return;
            }
            studentai.resize(studentuKiekis);
            for (Studentas& studentas : studentai) {
                ivestiStudentoDuomenis(studentas);
            }
            break;
        
        case '2':
            cout << "Kiek studentu norite sugeneruoti? ";
            cin >> studentuKiekis;
            if (studentuKiekis < 1 || studentuKiekis > 2147483647) {
                cout << "Klaida: Studentu skaicius turi buti daugiau nei 0 ir maziau nei 2147483647." << endl;
                return;
            }
            for (int i = 0; i < studentuKiekis; i++) {
                studentai.push_back(generuotiAtsitiktiniStudenta());
            }
            break;

        case '3': {
            cout << "Pasirinkite faila (1. studentai10.txt, 2. studentai100.txt, 3. studentai10000.txt, 4. studentai100000.txt, 5. studentai1000000.txt, 6. studentai10_blog.txt): ";
            int failoPasirinkimas;
            cin >> failoPasirinkimas;
            
            string failoPavadinimas;
            switch (failoPasirinkimas) {
                case 1: failoPavadinimas = "studentai10.txt"; break;
                case 2: failoPavadinimas = "studentai100.txt"; break;
                case 3: failoPavadinimas = "studentai10000.txt"; break;
                case 4: failoPavadinimas = "studentai100000.txt"; break;
                case 5: failoPavadinimas = "studentai1000000.txt"; break;
                case 6: failoPavadinimas = "studentai10_blog.txt"; break;
                default: 
                    cout << "Neteisingas pasirinkimas." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return;
            }
            skaitytiDuomenisIsFailo(failoPavadinimas, studentai);
            break;
        }

        default:
            cout << "Neteisingas pasirinkimas." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
    }

    if (studentai.empty()) {
        return;
    }

    rusiuotiStudentus(studentai);

    cout << left << setw(16) << "Pavarde" << setw(16) << "Vardas" << setw(25) << "Galutinis Vidurkis" << " / " << "Galutine Mediana" << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    for (const Studentas& studentas : studentai) {
        cout << left << setw(12) << studentas.pavarde << setw(15) << studentas.vardas << setw(25) << fixed << setprecision(2) << studentas.galutinisVidurkis << "   " << fixed << setprecision(2) << studentas.galutineMediana << endl;
    }
}


int main() {
    inicializuotiAtsitiktinius();
    
    int pabaiga;
    
    do {
        programa();
        
        cout << "Ar norite uzdaryti programa? Jeigu taip - rasykite 1, jeigu ne - rasykite 0: ";
        cin >> pabaiga;
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (pabaiga != 1);
    
    return 0;
}