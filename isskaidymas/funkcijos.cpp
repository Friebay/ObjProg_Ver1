#include "funkcijos.h"
#include "failo_apdorojimas.h"

// Inicializuoja atsitiktinių skaičių generatorių
void inicializuotiAtsitiktinius() {
    int random = int(time(0));
    srand(random);
}

// Gauna pažymį iš vartotojo įvesties
int gautiPazymi(const string& klausimas) {
    while (true) {
        string skaicius;
        cout << klausimas;
        cin >> skaicius;

        if (skaicius == "-1") return -1; // Grąžina -1, jei vartotojas nori baigti įvestį

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

// Įveda studento duomenis
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

    // Skaičiuoja vidurkį ir medianą, jei yra pažymių
    if (!studentas.pazymiai.empty()) {
        studentas.vidurkis = skaiciuotiVidurki(studentas.pazymiai);
        studentas.mediana = skaiciuotiMediana(studentas.pazymiai);
    }

    // Skaičiuoja galutinius įvertinimus
    studentas.galutinisVidurkis = 0.4 * studentas.vidurkis + 0.6 * studentas.egzaminoPazymys;
    studentas.galutineMediana = 0.4 * studentas.mediana + 0.6 * studentas.egzaminoPazymys;
}

// Rūšiuoja pažymius didėjimo tvarka
void rusiuotiPazymius(vector<int>& pazymiai) {
    sort(pazymiai.begin(), pazymiai.end());
}

// Rūšiuoja studentus pagal pavardę, o jei pavardės vienodos - pagal vardą
void rusiuotiStudentus(vector<Studentas>& studentai) {
    sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
        if (a.pavarde == b.pavarde) {
            return a.vardas < b.vardas;
        }
        return a.pavarde < b.pavarde;
    });
}

// Skaičiuoja pažymių medianą
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

// Skaičiuoja pažymių vidurkį
float skaiciuotiVidurki(vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0; 

    int suma = 0;
    for (int pazymys : pazymiai) {
        suma += pazymys;
    }
    return float(suma) / pazymiai.size();
}

// Generuoja atsitiktinį skaičių nurodytame intervale
int generuotiSkaiciu(int min, int max) {
    return min + (rand() % (max - min + 1));
}

// Generuoja atsitiktinį vardą arba pavardę
string generuotiVardaPavarde() {
    string raidziuRinkinys;
    char raides[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < 5; i++) {
        char x = raides[rand() % 26];
        raidziuRinkinys += x;
    }
    return raidziuRinkinys;
}

// Generuoja atsitiktinį studentą su atsitiktiniais duomenimis
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

// Pagrindinė programos funkcija
void programa() {
    vector<Studentas> studentai;
    int pasirinkimas;
    int failoPasirinkimas;
    int studentuKiekis;
    bool gerasPasirinkimas = false;
    
    // Meniu
    cout << "1. Ivesti duomenis ranka" << endl;
    cout << "2. Automatiskai generuoti duomenis" << endl;
    cout << "3. Nuskaityti duomenis is failo" << endl;
    cout << "4. Sukurti atsitiktiniu studentu failus" << endl;
    cout << "5. Nuskaityti sugeneruotus failus ir isvesti i nauja faila" << endl;
    cout << "6. Padalinti rezultatu faila i islaikius ir neislaikius" << endl;
    cout << "7. Sugeneruoti 5 atsitiktinius failus" << endl;
    cout << "Jusu pasirinkimas: ";
    
    // Vartotojo pasirinkimo tikrinimas
    while (!gerasPasirinkimas) {
        cout << "Iveskite pasirinkima (1, 2, 3, 4, 5, 6 arba 7): ";
        cin >> pasirinkimas;

        if (cin.fail() || pasirinkimas < 1 || pasirinkimas > 7) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neteisingas pasirinkimas. Prasome ivesti 1, 2, 3, 4, 5, 6 arba 7." << endl;
        } else {
            gerasPasirinkimas = true;
        }
    }

    try {
        switch (pasirinkimas) {
            case 1: {
                // Duomenų įvedimas ranka
                cout << "Kiek studentu norite irasyti? ";
                bool gerasPasirinkimas = false;

                while (!gerasPasirinkimas) {
                    cin >> studentuKiekis;
                    if (cin.fail() || studentuKiekis < 1) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Klaida: Ivestas neteisingas studentu skaicius. Prasome ivesti skaiciu didesni uz 0: ";
                    } else {
                        gerasPasirinkimas = true;
                    }
                }

                studentai.resize(studentuKiekis);
                for (Studentas& studentas : studentai) {
                    ivestiStudentoDuomenis(studentas);
                }
                break;
            }

            case 2: {
                // Automatinis duomenų generavimas
                cout << "Kiek studentu norite sugeneruoti? ";
                bool gerasPasirinkimas = false;

                while (!gerasPasirinkimas) {
                    cin >> studentuKiekis;
                    if (cin.fail() || studentuKiekis < 1) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Klaida: Ivestas neteisingas studentu skaicius. Prasome ivesti skaiciu didesni uz 0: ";
                    } else {
                        gerasPasirinkimas = true;
                    }
                }

                for (int i = 0; i < studentuKiekis; i++) {
                    studentai.push_back(generuotiAtsitiktiniStudenta());
                }
                break;
            }

            case 3: {
                // Duomenų nuskaitymas iš failo
                cout << "Pasirinkite faila (1. studentai10.txt, 2. studentai100.txt, 3. studentai10000.txt, 4. studentai100000.txt, 5. studentai1000000.txt, 6. studentai10_blog.txt, 7. tuscias.txt): ";
                bool gerasPasirinkimas = false;

                while (!gerasPasirinkimas) {
                    cin >> failoPasirinkimas;
                    if (cin.fail() || failoPasirinkimas < 1 || failoPasirinkimas > 7) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Neteisingas pasirinkimas. Prasome ivesti skaiciu nuo 1 iki 7: ";
                    } else {
                        gerasPasirinkimas = true;
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

            case 4: {
                // Atsitiktinių studentų failų kūrimas
                generuotiFaila();
                return; // Return after generating files to avoid further processing
            }   
            case 5: {
                // Skaityti generuotus failus
                vector<int> fileSizes = {1000, 10000, 100000, 1000000, 10000000};
                cout << "Pasirinkite faila:" << endl;
                for (int i = 0; i < fileSizes.size(); ++i) {
                    cout << i + 1 << ". studentai_" << fileSizes[i] << ".txt" << endl;
                }

                int fileChoice;
                cin >> fileChoice;
                if (fileChoice < 1 || fileChoice > 5) {
                    throw runtime_error("Neteisingas failo pasirinkimas.");
                }

                string inputFileName = "studentai_" + to_string(fileSizes[fileChoice - 1]) + ".txt";
                string outputFileName = "rezultatai_" + to_string(fileSizes[fileChoice - 1]) + ".txt";

                skaitytiIrIsvestiDuomenis(inputFileName, outputFileName);
                cout << "Duomenys nuskaityti is " << inputFileName << " ir isvesti i " << outputFileName << endl;
                return;
            }

            case 6: {
                // New option: Split results file into passed and not passed
                vector<int> fileSizes = {1000, 10000, 100000, 1000000, 10000000};
                cout << "Pasirinkite rezultatu faila:" << endl;
                for (int i = 0; i < fileSizes.size(); ++i) {
                    cout << i + 1 << ". rezultatai_" << fileSizes[i] << ".txt" << endl;
                }

                int fileChoice;
                cin >> fileChoice;
                if (fileChoice < 1 || fileChoice > 5) {
                    throw runtime_error("Neteisingas failo pasirinkimas.");
                }

                string inputFileName = "rezultatai_" + to_string(fileSizes[fileChoice - 1]) + ".txt";
                string passedFileName = "rezultatai_" + to_string(fileSizes[fileChoice - 1]) + "_passed.txt";
                string notPassedFileName = "rezultatai_" + to_string(fileSizes[fileChoice - 1]) + "_not_passed.txt";

                padalintiRezultatuFaila(inputFileName, passedFileName, notPassedFileName);
                cout << "Rezultatu failas padalintas i " << passedFileName << " ir " << notPassedFileName << endl;
                return;
            }

            case 7: {
                // Generate 5 random-length files
                generuotiAtsitiktiniusFailus();
                return;
            }

            
            
        }

        if (studentai.empty()) {
            throw runtime_error("Nera studentu duomenu.");
        }

        // Rūšiuoja studentus
        rusiuotiStudentus(studentai);

        // Spausdina rezultatus
        cout << left << setw(16) << "Pavarde" << setw(16) << "Vardas" << setw(25) << "Galutinis Vidurkis" << " / " << "Galutine Mediana" << endl;
        cout << "-------------------------------------------------------------------------" << endl;

        for (const Studentas& studentas : studentai) {
            cout << left << setw(16) << studentas.pavarde << setw(16) << studentas.vardas << setw(25) << fixed << setprecision(2) << studentas.galutinisVidurkis << "   " << fixed << setprecision(2) << studentas.galutineMediana << endl;
        }
    } catch (const exception& e) {
        cout << "Ivyko klaida: " << e.what() << endl;
    }
}

void generuotiAtsitiktiniusFailus() {
    for (int i = 1; i <= 5; ++i) {
        int studentuKiekis = generuotiSkaiciu(1, 10000000);
        string failoPavadinimas = "studentai_random_" + to_string(i) + ".txt";
        generuotiStudentuFaila(studentuKiekis, failoPavadinimas);
        cout << "Sugeneruotas failas " << failoPavadinimas << " su " << studentuKiekis << " studentu." << endl;
    }
}