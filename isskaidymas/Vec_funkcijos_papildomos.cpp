#include "Vec_funkcijos.h"
#include "Vec_funkcijos_papildomos.h"
#include "Vec_failo_apdorojimas.h"

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
                cout << "Klaida: pazymys turi buti tarp 0 ir 10.\n";
            }
        } catch (const invalid_argument&) {
            cout << "Klaida: iveskite teisinga skaiciu.\n";
        }
    }
}

// Rūšiuoja studentus pagal pavardę, o jei pavardės vienodos - pagal vardą
void rusiuotiStudentusPagalPavarde(std::vector<Studentas>& studentai) {
    std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
        if (a.pavarde == b.pavarde) {
            return a.vardas < b.vardas; // Sort by first name if last names are the same
        }
        return a.pavarde < b.pavarde; // Sort by last name
    });
}

// Rūšiuoja studentus pagal vardą, o jei vardai vienodos - pagal pavardę
void rusiuotiStudentusPagalVarda(std::vector<Studentas>& studentai) {
    std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
        if (a.vardas == b.vardas) {
            return a.pavarde < b.pavarde; // Sort by last name if first names are the same
        }
        return a.vardas < b.vardas; // Sort by first name
    });
}

// Įveda studento duomenis
void ivestiStudentoDuomenis(Studentas& studentas) {
    cout << "Vardas: ";
    cin >> studentas.vardas;

    cout << "Pavarde: ";
    cin >> studentas.pavarde;

    cout << "Iveskite pazymius (iveskite -1, kad baigtumete):\n";
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

    const double egzaminoBalas = 0.6 * studentas.egzaminoPazymys;
    const double vidurkioBalas = 0.4 * studentas.vidurkis;
    const double medianosBalas = 0.4 * studentas.mediana;

    studentas.galutinisVidurkis = vidurkioBalas + egzaminoBalas;
    studentas.galutineMediana = medianosBalas + egzaminoBalas;
}

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

// Skaičiuoja pažymių vidurkį
float skaiciuotiVidurki(vector<int>& pazymiai) {
    if (pazymiai.empty()) {
        return 0.0f;
    }
    return std::accumulate(pazymiai.begin(), pazymiai.end(), 0.0f) / pazymiai.size();
}

int generuotiSkaiciu(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(gen);
}

// Generuoja atsitiktinį vardą arba pavardę
string generuotiVardaPavarde() {
    static const char raides[] = "abcdefghijklmnopqrstuvwxyz";
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> raideDistrib(0, 25);
    
    string vardasPavarde(4, ' '); 

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
    const double egzaminoBalas = 0.6 * studentas.egzaminoPazymys;
    const double vidurkioBalas = 0.4 * studentas.vidurkis;
    const double medianosBalas = 0.4 * studentas.mediana;

    studentas.galutinisVidurkis = vidurkioBalas + egzaminoBalas;
    studentas.galutineMediana = medianosBalas + egzaminoBalas;

    return studentas;
}

void generuotiAtsitiktiniusFailus() {
    for (int i = 1; i <= 5; ++i) {
        int studentuKiekis = generuotiSkaiciu(1, 1000000);
        string failoPavadinimas = "txt_failai/studentai_random_" + to_string(i) + ".txt";
        generuotiStudentuFaila(studentuKiekis, failoPavadinimas);
        cout << "Sugeneruotas failas " << failoPavadinimas << " su " << studentuKiekis << " studentu.\n";
    }
}


void vykdytiVisusZingsnius() {
    vector<int> studentuKiekiai = {1000, 10000, 100000, 1000000, 10000000};
    
    // Atidaryti CSV failą rašymui
    ofstream csvFile("performance_data.csv", std::ios::app);
    if (!csvFile.is_open()) {
        throw runtime_error("Nepavyko atidaryti CSV failo");
    }
    
    // Įrašo CSV antraštę, jei failas tuščias
    csvFile.seekp(0, std::ios::end);
    if (csvFile.tellp() == 0) {
        csvFile << "Testavimo Laikas;Studentu Kiekis;Studentu generavimo laikas;Sugeneruotu duomenu skaitymo laikas;Rezultatu irasymo laikas;Rezultatu skaitymo laikas;Rezultatu skaidymo laikas;Skaidymo irasymas;Bendras Laikas\n";
    }

    for (int kiekis : studentuKiekiai) {
        cout << "Vykdomi zingsniai su " << kiekis << " studentu:\n";
        auto pradziaVisko = std::chrono::high_resolution_clock::now();
        
        // Gauti dabartinį laiką
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
        cout << "Failo su " << kiekis << "studentais generavimas uztruko " << trukmeGeneravimo.count() << " ms.\n";

        // Skaitomas sugeneruotas failas, apskaičiuoja galutinius rezultatus ir išvedamas į rezultatų failą
        string rezultatuFailas = "rezultatai_" + to_string(kiekis) + ".txt";
        cout << "Skaitomi duomenys ir isvedami i " << rezultatuFailas << "...\n";
        long long trukmeSkaitymo, trukmeVidurkio, trukmeIrasymo;
        auto pradziaSkaitymo = std::chrono::high_resolution_clock::now();
        skaitytiIrIsvestiDuomenis(studentuFailas, rezultatuFailas, trukmeSkaitymo, trukmeVidurkio, trukmeIrasymo);
        auto pabaigaSkaitymo = std::chrono::high_resolution_clock::now();
        auto trukmeSkaitymoLaikas = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaSkaitymo - pradziaSkaitymo);
        
        cout << "Skaitymo laikas: " << trukmeSkaitymo << " ms.\n";
        cout << "Duomenu isvedimas i " << rezultatuFailas << " uztruko " << trukmeIrasymo << " ms.\n";

        // Rezultatų failo padalijimas į išlaikiusius ir neišlaikiusius
        string islaikeFailas = "rezultatai_" + to_string(kiekis) + "_islaike.txt";
        string neislaikeFailas = "rezultatai_" + to_string(kiekis) + "_neislaike.txt";
        cout << "Dalinamas rezultatu failas i islaikiusius ir neislaikiusius...\n";
        long long trukmeRezultatuSkaitymo, trukmeRezultatuSkaidymas, trukmeSkaidymoIrasymas;
        padalintiRezultatuFaila(rezultatuFailas, islaikeFailas, neislaikeFailas, trukmeRezultatuSkaitymo, trukmeRezultatuSkaidymas, trukmeSkaidymoIrasymas);
        cout << "Rezultatu failo dalinimas uztruko " << trukmeRezultatuSkaitymo + trukmeRezultatuSkaidymas + trukmeSkaidymoIrasymas << " ms.\n";

        // Skaičuoti bendrą laiką
        long long bendrasLaikas = trukmeGeneravimo.count() + trukmeSkaitymo + trukmeIrasymo + trukmeRezultatuSkaitymo + trukmeRezultatuSkaidymas + trukmeSkaidymoIrasymas;
        cout << "Visi zingsniai su " << kiekis << " studentu baigti. Trukme: " << bendrasLaikas << " ms.\n\n";

        auto pabaigaVisko = std::chrono::high_resolution_clock::now();
        auto trukmeVisko = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaVisko - pradziaVisko);
        cout << "Visi zingsniai su " << kiekis << " studentu baigti. Trukme: " << trukmeVisko.count() << " ms.\n\n";


        // Surašyti laikus į CSV failą
        csvFile << timestamp << ";"
                << kiekis << ";"
                << trukmeGeneravimo.count() << ";"
                << trukmeSkaitymo << ";"
                << trukmeIrasymo << ";"
                << trukmeRezultatuSkaitymo << ";"
                << trukmeRezultatuSkaidymas << ";"
                << trukmeSkaidymoIrasymas << ";"
                << bendrasLaikas << "\n";
    }

    csvFile.close();
    cout << "Visi zingsniai visiems studentu kiekiams baigti.\n";
    cout << "Duomenys issaugoti faile 'performance_data.csv'\n";
}
