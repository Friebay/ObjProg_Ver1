#include "funkcijos.h"
#include "failo_apdorojimas.h"

#include <fstream>
#include <iomanip>
#include <ctime>

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
/* 
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
*/

// Skaičiuoja pažymių medianą
float skaiciuotiMediana(vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0;
    
    size_t n = pazymiai.size();
    size_t middle = n / 2;
    
    if (n % 2 == 0) {
        nth_element(pazymiai.begin(), pazymiai.begin() + middle - 1, pazymiai.end());
        nth_element(pazymiai.begin() + middle - 1, pazymiai.begin() + middle, pazymiai.end());
        return (pazymiai[middle-1] + pazymiai[middle]) / 2.0f;
    } else {
        nth_element(pazymiai.begin(), pazymiai.begin() + middle, pazymiai.end());
        return pazymiai[middle];
    }
}

/* 
float skaiciuotiVidurki(vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0; 

    int suma = 0;
    for (int pazymys : pazymiai) {
        suma += pazymys;
    }
    return float(suma) / pazymiai.size();
}
*/

// Skaičiuoja pažymių vidurkį
float skaiciuotiVidurki(vector<int>& pazymiai) {
    if (pazymiai.empty()) {
        return 0.0f;
    }
    return std::accumulate(pazymiai.begin(), pazymiai.end(), 0.0f) / pazymiai.size();
}

// Generuoja atsitiktinį skaičių nurodytame intervale
/* int generuotiSkaiciu(int min, int max) {
    return min + (rand() % (max - min + 1));
} */

int generuotiSkaiciu(int min, int max) {
    static std::random_device rd;  // Non-deterministic random seed
    static std::mt19937 gen(rd()); // Mersenne Twister RNG
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(gen);
}

// Generuoja atsitiktinį vardą arba pavardę
/*string generuotiVardaPavarde() {
    string raidziuRinkinys;
    char raides[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < 5; i++) {
        char x = raides[rand() % 26];
        raidziuRinkinys += x;
    }
    return raidziuRinkinys;
}*/

string generuotiVardaPavarde() {
    static const char raides[] = "abcdefghijklmnopqrstuvwxyz";
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> raideDistrib(0, 25);
    
    string vardasPavarde(4, ' ');  // Fixed length of 5 characters

    for (int i = 0; i < 4; ++i) {
        vardasPavarde[i] = raides[raideDistrib(gen)];
    }

    return vardasPavarde;
}

Studentas generuotiAtsitiktiniStudenta() {
    Studentas studentas;
    
    // Generuojami atsitiktiniai vardas ir pavarde
    studentas.vardas = generuotiVardaPavarde();
    studentas.pavarde = generuotiVardaPavarde();

    // Pre-allocate space for pazymiai to avoid reallocations
    int pazymiuKiekis = generuotiSkaiciu(1, 20);
    studentas.pazymiai.reserve(pazymiuKiekis);  // Reserve space for pazymiai

    // Generuojami atsitiktiniai pažymiai
    for (int i = 0; i < pazymiuKiekis; i++) {
        studentas.pazymiai.push_back(generuotiSkaiciu(0, 10));
    }

    // Generuojamas egzamino pažymys
    studentas.egzaminoPazymys = generuotiSkaiciu(0, 10);

    // Apskaičiuojami vidurkis ir mediana
    studentas.vidurkis = skaiciuotiVidurki(studentas.pazymiai);
    studentas.mediana = skaiciuotiMediana(studentas.pazymiai);

    // Apskaičiuojami galutiniai įvertinimai, naudojami constant multipliers
    const float koefVidurkis = 0.4f;
    const float koefEgzaminas = 0.6f;

    studentas.galutinisVidurkis = koefVidurkis * studentas.vidurkis + koefEgzaminas * studentas.egzaminoPazymys;
    studentas.galutineMediana = koefVidurkis * studentas.mediana + koefEgzaminas * studentas.egzaminoPazymys;

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
    cout << "8. Vykdyti visus zingsnius visiems studentu kiekiams" << endl;
    cout << "Jusu pasirinkimas: ";
    
    // Vartotojo pasirinkimo tikrinimas
    while (!gerasPasirinkimas) {
        cout << "Iveskite pasirinkima (1-8): ";
        cin >> pasirinkimas;

        if (cin.fail() || pasirinkimas < 1 || pasirinkimas > 8) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neteisingas pasirinkimas. Prasome ivesti skaiciu nuo 1 iki 8." << endl;
        } else {
            gerasPasirinkimas = true;
        }
    }

    try {
        long long trukmeSkaitymo, trukmeVidurkio, trukmeIrasymo;
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

                skaitytiDuomenisIsFailo(failoPavadinimas, studentai, trukmeSkaitymo, trukmeVidurkio);
                break;
            }

            case 4: {
                // Atsitiktinių studentų failų kūrimas
                generuotiFaila();
                return;
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


                skaitytiIrIsvestiDuomenis(inputFileName, outputFileName, trukmeSkaitymo, trukmeVidurkio, trukmeIrasymo);
                cout << "Duomenys nuskaityti is " << inputFileName << " ir isvesti i " << outputFileName << endl;
                return;
            }

            case 6: {
                // Rūšiuoti į išlaikiusius ir neišlaikiusius
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
                // Generuoti 5 atsitiktinio dydžio studentų failus
                generuotiAtsitiktiniusFailus();
                return;
            }

            case 8: {
                int kartai;
                bool validInput = false;
                
                // Get the number of repetitions from the user
                while (!validInput) {
                    cout << "Kiek kartu norite paleisti funkcija 'vykdytiVisusZingsnius'? ";
                    cin >> kartai;
                    
                    if (cin.fail() || kartai <= 0) {
                        cin.clear();  // Clear the error flag on cin
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
                        cout << "Neteisingas skaicius. Prasome ivesti teigiama skaiciu." << endl;
                    } else {
                        validInput = true;
                    }
                }

                // Run 'vykdytiVisusZingsnius' the specified number of times
                for (int i = 0; i < kartai; i++) {
                    cout << "Vykdoma " << i + 1 << " karta:" << endl;
                    vykdytiVisusZingsnius();
                }

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

void vykdytiVisusZingsnius() {
    vector<int> studentuKiekiai = {1000, 10000, 100000, 1000000, 10000000};
    
    // Open CSV file for writing
    ofstream csvFile("performance_data.csv", std::ios::app);
    if (!csvFile.is_open()) {
        throw runtime_error("Nepavyko atidaryti CSV failo");
    }
    
    // Write CSV header if the file is empty
    csvFile.seekp(0, std::ios::end);
    if (csvFile.tellp() == 0) {
        csvFile << "Timestamp;StudentuKiekis;GeneravimoLaikas;SkaitymoLaikas;VidurkioLaikas;trukmeIrasymo;DalinimoLaikas;BendrasLaikas\n";
    }

    for (int kiekis : studentuKiekiai) {
        cout << "Vykdomi zingsniai su " << kiekis << " studentu:" << endl;
        
        // Get current timestamp
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
        string timestamp = ss.str();

        // Generuoti studentų failą
        string studentuFailas = "studentai_" + to_string(kiekis) + ".txt";
        auto pradziaGeneravimo = std::chrono::high_resolution_clock::now();
        generuotiStudentuFaila(kiekis, studentuFailas);
        auto pabaigaGeneravimo = std::chrono::high_resolution_clock::now();
        auto trukmeGeneravimo = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaGeneravimo - pradziaGeneravimo);
        cout << "Failo generavimas uztruko " << trukmeGeneravimo.count() << " ms." << endl;

        // Skaitomas sugeneruotas failas ir išvedamas į naują failą
        string rezultatuFailas = "rezultatai_" + to_string(kiekis) + ".txt";
        cout << "Skaitomi duomenys is " << studentuFailas << " ir isvedami i " << rezultatuFailas << "..." << endl;
    
        long long trukmeSkaitymo, trukmeVidurkio, trukmeIrasymo;
        auto pradziaSkaitymo = std::chrono::high_resolution_clock::now();
        skaitytiIrIsvestiDuomenis(studentuFailas, rezultatuFailas, trukmeSkaitymo, trukmeVidurkio, trukmeIrasymo);
        auto pabaigaSkaitymo = std::chrono::high_resolution_clock::now();
        auto trukmeSkaitymoLaikas = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaSkaitymo - pradziaSkaitymo);
        
        cout << studentuFailas << "Skaitymo laikas: " << trukmeSkaitymo << " ms." << endl;
        cout << "Vidurkio skaiciavimas uztruko " << trukmeVidurkio << " ms." << endl;
        cout << "Duomenu isvedimas i " << rezultatuFailas << " uztruko " << trukmeIrasymo << " ms." << endl;

        // Rezultatų failo padalijimas į išlaikiusius ir neišlaikiusius
        string islaikeFailas = "rezultatai_" + to_string(kiekis) + "_islaike.txt";
        string neislaikeFailas = "rezultatai_" + to_string(kiekis) + "_neislaike.txt";
        cout << "Dalinamas rezultatu failas i islaikiusius ir neislaikiusius..." << endl;
        auto pradziaDalinimo = std::chrono::high_resolution_clock::now();
        padalintiRezultatuFaila(rezultatuFailas, islaikeFailas, neislaikeFailas);
        auto pabaigaDalinimo = std::chrono::high_resolution_clock::now();
        auto trukmeDalinimo = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaDalinimo - pradziaDalinimo);
        cout << "Rezultatu failo dalinimas uztruko " << trukmeDalinimo.count() << " ms." << endl;

        // Skaičuoti bendrą laiką
        long long bendrasLaikas = trukmeGeneravimo.count() + trukmeSkaitymo + trukmeVidurkio + trukmeIrasymo + trukmeDalinimo.count();
        cout << "Visi zingsniai su " << kiekis << " studentu baigti. Trukme: " << bendrasLaikas << " ms." << endl << endl;

        // Surašyti laikus į CSV failą
        csvFile << timestamp << ";"
                << kiekis << ";"
                << trukmeGeneravimo.count() << ";"
                << trukmeSkaitymo << ";"
                << trukmeVidurkio << ";"
                << trukmeIrasymo << ";"
                << trukmeDalinimo.count() << ";"
                << bendrasLaikas << "\n";
    }

    csvFile.close();
    cout << "Visi zingsniai visiems studentu kiekiams baigti." << endl;
    cout << "Duomenys issaugoti faile 'performance_data.csv'" << endl;
}
