#include "failo_apdorojimas.h"
#include <iomanip>
#include <sstream>

// Funkcija skaičiuoja studento galutinius įvertinimus ir prideda studentą į vektorių
void skaiciuotiIsFailo(Studentas& studentas, bool tinkamiPazymiai, vector<Studentas>& studentai) {
    if (tinkamiPazymiai) {
        if (!studentas.pazymiai.empty()) {
            // Paskutinis pažymys laikomas egzamino pažymiu
            studentas.egzaminoPazymys = studentas.pazymiai.back();
            studentas.pazymiai.pop_back();

            // Skaičiuojami vidurkis ir mediana
            studentas.vidurkis = skaiciuotiVidurki(studentas.pazymiai);
            studentas.mediana = skaiciuotiMediana(studentas.pazymiai);
            
            // Skaičiuojami galutiniai įvertinimai
            studentas.galutinisVidurkis = 0.4 * studentas.vidurkis + 0.6 * studentas.egzaminoPazymys;
            studentas.galutineMediana = 0.4 * studentas.mediana + 0.6 * studentas.egzaminoPazymys;

            // Studentas pridedamas į vektorių
            studentai.push_back(studentas);
        } else {
            cout << "Klaida: truksta pazymiu studentui " << studentas.vardas << " " << studentas.pavarde << endl;
        }
    } else {
        cout << "Studentas " << studentas.vardas << " " << studentas.pavarde << " neturi galutiniu pazymiu del neteisingu duomenu." << endl;
    }
}

// Funkcija skaito duomenis iš failo ir apdoroja kiekvieną studentą
void skaitytiDuomenisIsFailo(const string& failoPavadinimas, vector<Studentas>& studentai) {
    auto pradziaViso = std::chrono::high_resolution_clock::now();
    auto pradziaSkaitymo = pradziaViso;

    // Atidaromas failas
    ifstream failas(failoPavadinimas);
    if (!failas) {
        throw runtime_error("Failo " + failoPavadinimas + " nera.");
    }
    string eilute;
    // Praleidžiama antraštės eilutė
    getline(failas, eilute);

    vector<Studentas> nuskaitytStudentai;

    // Skaitoma kiekviena eilutė
    while (getline(failas, eilute)) {
        istringstream iss(eilute);
        Studentas studentas;
        // Nuskaitomas vardas ir pavardė
        if (!(iss >> studentas.vardas >> studentas.pavarde)) {
            throw runtime_error("Klaida nuskaitant varda ir pavarde.");
        }
        string pazymysStr;
        bool tinkamiPazymiai = true;
        // Skaitomi pažymiai
        while (iss >> pazymysStr) {
            try {
                // Tikrinama, ar pažymys yra skaičius
                if (pazymysStr.find_first_not_of("0123456789") != string::npos) {
                    throw invalid_argument("Klaida: pazymys turi buti skaicius.");
                }
                int pazymys = stoi(pazymysStr);
                // Tikrinama, ar pažymys yra tinkamame intervale
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
            nuskaitytStudentai.push_back(studentas);
        } else {
            cout << "Studentas " << studentas.vardas << " " << studentas.pavarde << " neturi galutiniu pazymiu del neteisingu duomenu." << endl;
        }
    }

    auto pabaigaSkaitymo = std::chrono::high_resolution_clock::now();
    auto trukmeSkaitymo = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaSkaitymo - pradziaSkaitymo);

    auto pradziaVidurkio = std::chrono::high_resolution_clock::now();

    // Skaičiuojami galutiniai įvertinimai
    for (auto& studentas : nuskaitytStudentai) {
        skaiciuotiIsFailo(studentas, true, studentai);
    }

    auto pabaigaVidurkio = std::chrono::high_resolution_clock::now();
    auto trukmeVidurkio = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaVidurkio - pradziaVidurkio);

    auto pabaigaViso = std::chrono::high_resolution_clock::now();
    auto trukmėViso = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaViso - pradziaViso);

    cout << "Duomenu skaitymas is "<< failoPavadinimas <<" uztruko " << trukmeSkaitymo.count() << " ms." << endl;
    cout << "Vidurkiu skaiciavimas uztruko " << trukmeVidurkio.count() << " ms." << endl;
}

void skaitytiIrIsvestiDuomenis(const string& ivestiesFailoPavadinimas, const string& outputFileName) {
    vector<Studentas> studentai;
    skaitytiDuomenisIsFailo(ivestiesFailoPavadinimas, studentai);

    auto pradziaIrasimo = std::chrono::high_resolution_clock::now();
    ofstream outputFile(outputFileName);
    if (!outputFile) {
        throw runtime_error("Nepavyko atidaryti isvesties failo " + outputFileName);
    }

    outputFile << left << setw(16) << "Pavarde" << setw(16) << "Vardas" << setw(25) << "Galutinis Vidurkis" << "Galutine Mediana" << endl;
    outputFile << string(70, '-') << endl;

    for (const auto& studentas : studentai) {
        outputFile << left << setw(16) << studentas.pavarde << setw(16) << studentas.vardas << setw(25) << fixed << setprecision(2) << studentas.galutinisVidurkis << fixed << setprecision(2) << studentas.galutineMediana << endl;
    }
    outputFile.close();

    auto pabaigaIrasimo = std::chrono::high_resolution_clock::now();
    auto trukmeIrasymo = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaIrasimo - pradziaIrasimo);
    cout << "Duomenu isvedimas i "<< outputFileName << " uztruko " << trukmeIrasymo.count() << " ms." << endl;

}

void padalintiRezultatuFaila(const string& ivestiesFailoPavadinimas, const string& islaikiusiuFailoPavadinimas, const string& neislaikiusiuFailoPavadinimas) {
    ifstream ivestiesFailas(ivestiesFailoPavadinimas);

    if (!ivestiesFailas) {
        throw runtime_error("Nepavyko atidaryti ivesties failo " + ivestiesFailoPavadinimas);
    }

    ofstream islaikiusiuFailas(islaikiusiuFailoPavadinimas);
    ofstream neislaikiusiuFailas(neislaikiusiuFailoPavadinimas);
    if (!islaikiusiuFailas || !neislaikiusiuFailas) {
        throw runtime_error("Nepavyko atidaryti isvesties failu");
    }

    string eilute;
    getline(ivestiesFailas, eilute);
    islaikiusiuFailas << eilute << endl;
    neislaikiusiuFailas << eilute << endl;

    getline(ivestiesFailas, eilute);
    islaikiusiuFailas << eilute << endl;
    neislaikiusiuFailas << eilute << endl;

    while (getline(ivestiesFailas, eilute)) {
        istringstream iss(eilute);
        string pavarde, vardas;
        float galutinisVidurkis, galutineMediana;

        iss >> pavarde >> vardas >> galutinisVidurkis >> galutineMediana;

        if (galutinisVidurkis >= 5.0) {
            islaikiusiuFailas << eilute << endl;
        } else {
            neislaikiusiuFailas << eilute << endl;
        }
    }

    ivestiesFailas.close();
    islaikiusiuFailas.close();
    neislaikiusiuFailas.close();
}
