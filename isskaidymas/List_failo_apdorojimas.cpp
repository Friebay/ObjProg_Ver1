#include "List_failo_apdorojimas.h"
#include "List_funkcijos.h"
#include "Vec_funkcijos_papildomos.h"

void List_skaiciuotiIsFailo(List_Studentas& studentas, bool tinkamiPazymiai, list<List_Studentas>& studentai) {
    if (tinkamiPazymiai && !studentas.pazymiai.empty()) {
        studentas.egzaminoPazymys = studentas.pazymiai.back();
        studentas.pazymiai.pop_back();

        studentas.vidurkis = List_skaiciuotiVidurki(studentas.pazymiai);
        studentas.mediana = List_skaiciuotiMediana(studentas.pazymiai);

        const double egzaminoBalas = 0.6 * studentas.egzaminoPazymys;
        const double vidurkioBalas = 0.4 * studentas.vidurkis;
        const double medianosBalas = 0.4 * studentas.mediana;

        studentas.galutinisVidurkis = vidurkioBalas + egzaminoBalas;
        studentas.galutineMediana = medianosBalas + egzaminoBalas;

        studentai.push_back(move(studentas));
    } else {
        cout << "Klaida: truksta pazymiu studentui " << studentas.vardas << " " << studentas.pavarde << "\n";
    }
}

void List_skaitytiDuomenisIsFailo(const string& failoPavadinimas, list<List_Studentas>& studentai, long long& trukmeSkaitymo, long long& trukmeVidurkio) {
    auto pradziaSkaitymo = std::chrono::high_resolution_clock::now();

    ifstream failas(failoPavadinimas, std::ios::in | std::ios::binary);
    if (!failas) {
        throw runtime_error("Failo " + failoPavadinimas + " nera.");
    }

    string buffer;
    buffer.reserve(1048576); // Buferio dydis baitais

    // Praleidžia antraštę
    getline(failas, buffer);

    while (getline(failas, buffer)) {
        if (buffer.length() < 52) { // Minimalaus ilgio patikrinimas
            throw runtime_error("Netinkamas eilutes ilgis");
        }

        List_Studentas studentas;
        
        // Skaito vardą ir pavardę
        studentas.vardas = buffer.substr(0, 16);
        studentas.pavarde = buffer.substr(16, 32);

        // Funkcija ištrinti whitespace iš string
        auto trim = [](std::string &str) {
            // Ištrinti pradžioję esantį whitespace
            str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
            // Ištrinti pabaigoje esantį whitespace
            str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }).base(), str.end());
        };

        trim(studentas.pavarde);

        // Pažymiai prasideda nuo 52 simbolio
        size_t pozicija = 52;
        bool tinkamiPazymiai = true;
        
        while (pozicija < buffer.length()) {
            // Praleidžia whitespace
            while (pozicija < buffer.length() && isspace(buffer[pozicija])) pozicija++;
            if (pozicija >= buffer.length()) break;

            int grade = 0;
            bool tinkamas = true;
            
            // Patikrina ar skaičius
            if (isdigit(buffer[pozicija])) {
                while (pozicija < buffer.length() && isdigit(buffer[pozicija])) {
                    grade = grade * 10 + (buffer[pozicija] - '0');
                    pozicija++;
                }

                // Patikrina ar tarp 0 ir 10
                if (grade < 0 || grade > 10) {
                    tinkamas = false;
                }
            } else {
                // Jeigu ne skaičius:
                tinkamas = false; // Netinkamas
                pozicija++; // Eina į kitą poziciją
            }

            if (tinkamas) {
                studentas.pazymiai.push_back(grade);
            } else {
                tinkamiPazymiai = false;
                break;
            }
            
            // Praleidžia whitespace
            while (pozicija < buffer.length() && isspace(buffer[pozicija])) pozicija++;
        }

        // Paskaičiuoja rezultatus
        List_skaiciuotiIsFailo(studentas, tinkamiPazymiai, studentai);
    }

    auto pabaigaSkaitymo = std::chrono::high_resolution_clock::now();
    trukmeSkaitymo = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaSkaitymo - pradziaSkaitymo).count();
    trukmeVidurkio = 0;
}


void List_skaitytiIrIsvestiDuomenis(const string& ivestiesFailoPavadinimas, const string& irasymoFailoPavadinimas, long long& trukmeSkaitymo, long long& trukmeVidurkio, long long& trukmeIrasymo) {
    list<List_Studentas> studentai;
    List_skaitytiDuomenisIsFailo(ivestiesFailoPavadinimas, studentai, trukmeSkaitymo, trukmeVidurkio);

    auto pradziaIrasimo = std::chrono::high_resolution_clock::now();
    
    // Naudoja stringstream buferiui
    ostringstream buffer;

    // Įrašo antraštę į buferį
    buffer << left << setw(16) << "Pavarde" 
           << setw(16) << "Vardas" 
           << setw(25) << "Galutinis Vidurkis" 
           << "Galutine Mediana\n";
    buffer << string(70, '-') << "\n";

    for (const auto& studentas : studentai) {
        buffer << left << setw(16) << studentas.pavarde
               << setw(16) << studentas.vardas
               << setw(25) << fixed << setprecision(2) << studentas.galutinisVidurkis
               << fixed << setprecision(2) << studentas.galutineMediana
               << "\n";
    }

    // Atidaro failą įrašymui
    ofstream irasymoFailas(irasymoFailoPavadinimas, std::ios::out | std::ios::binary);
    if (!irasymoFailas) {
        throw runtime_error("Nepavyko atidaryti isvesties failo " + irasymoFailoPavadinimas);
    }

    // Įrašo visą buferį vienu metu
    irasymoFailas << buffer.str();
    irasymoFailas.close();

    auto pabaigaIrasimo = std::chrono::high_resolution_clock::now();
    trukmeIrasymo = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaIrasimo - pradziaIrasimo).count();
}

void List_padalintiRezultatuFaila(const string& ivestiesFailoPavadinimas, const string& islaikiusiuFailoPavadinimas, const string& neislaikiusiuFailoPavadinimas, long long& laikasSkaitymo, long long& rusiavimoLaikas, long long& laikasRasymo) {
    auto pradziaSkaitymo = std::chrono::high_resolution_clock::now();
    
    // Atidaro duomenis binariniu režimu
    ifstream ivestiesFailas(ivestiesFailoPavadinimas, std::ios::in | ios::binary);
    if (!ivestiesFailas) {
        throw runtime_error("Nepavyko atidaryti ivesties failo " + ivestiesFailoPavadinimas);
    }

    // Perskaito duomenis į buferį
    ivestiesFailas.seekg(0, ios::end);
    size_t failoDydis = ivestiesFailas.tellg();
    ivestiesFailas.seekg(0, ios::beg);
    vector<char> buferis(failoDydis);
    ivestiesFailas.read(buferis.data(), failoDydis);
    ivestiesFailas.close();

    ofstream islaikiusiuFailas(islaikiusiuFailoPavadinimas, ios::out | ios::binary);
    ofstream neislaikiusiuFailas(neislaikiusiuFailoPavadinimas, ios::out | ios::binary);
    if (!islaikiusiuFailas || !neislaikiusiuFailas) {
        throw runtime_error("Nepavyko atidaryti išvesties failų");
    }

    // Konvertuoti buferį į string
    string failoTurinys(buferis.begin(), buferis.end());
    istringstream iss(failoTurinys);
    string eilute;

    // Pirmus dvi eilutės yra antraštės
    getline(iss, eilute);
    islaikiusiuFailas << eilute << "\n";
    neislaikiusiuFailas << eilute << "\n";

    getline(iss, eilute);
    islaikiusiuFailas << eilute << "\n";
    neislaikiusiuFailas << eilute << "\n";

    // Naudojame list su List_Studentas struktūra
    list<List_Studentas> studentai;

    while (getline(iss, eilute)) {
        istringstream studentLine(eilute);
        List_Studentas student;
        studentLine >> student.pavarde >> student.vardas >> student.galutinisVidurkis >> student.galutineMediana;
        studentai.push_back(student);
    }

    auto pabaigaSkaitymo = std::chrono::high_resolution_clock::now();
    laikasSkaitymo = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaSkaitymo - pradziaSkaitymo).count();
    cout << "Failo skaitymas uztruko " << laikasSkaitymo << " ms." << endl;

    auto pradetiRusiavima = std::chrono::high_resolution_clock::now();
    
    // Rušiuoti studentus pagal galutinį pažymį naudojant list::sort
    studentai.sort([](const List_Studentas& a, const List_Studentas& b) {
        return a.galutinisVidurkis > b.galutinisVidurkis;
    });

    auto pabaigaRusiavimo = std::chrono::high_resolution_clock::now();
    rusiavimoLaikas = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaRusiavimo - pradetiRusiavima).count();
    cout << "Rusiavimas uztruko " << rusiavimoLaikas << " ms." << endl;

    auto pradetiRasyma = std::chrono::high_resolution_clock::now();

    // Įrašyti surūšiuotus studentus į atitinkamus failus
    for (const auto& student : studentai) {
        if (student.galutinisVidurkis >= 5.0f) {
            islaikiusiuFailas << left << setw(15) << student.pavarde << " " << setw(15) << student.vardas << " " << setw(24) << student.galutinisVidurkis << " " << student.galutineMediana << "\n";
        } else {
            neislaikiusiuFailas << left << setw(15) << student.pavarde << " " << setw(15) << student.vardas << " " << setw(24) << student.galutinisVidurkis << " " << student.galutineMediana << "\n";
        }
    }

    auto pabaigaRasymo = std::chrono::high_resolution_clock::now();
    laikasRasymo = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaRasymo - pradetiRasyma).count();
    cout << "Rasymas uztruko " << laikasRasymo << " ms." << endl;

    // Uždaryti failus
    islaikiusiuFailas.close();
    neislaikiusiuFailas.close();
}
