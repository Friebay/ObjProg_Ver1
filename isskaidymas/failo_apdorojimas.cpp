#include "failo_apdorojimas.h"
#include <iomanip>

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
    // Atidaromas failas
    ifstream failas(failoPavadinimas);
    if (!failas) {
        throw runtime_error("Failo " + failoPavadinimas + " nera.");
    }

    string eilute;
    // Praleidžiama antraštės eilutė
    getline(failas, eilute);

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

        // Jei pažymiai tinkami, skaičiuojami galutiniai įvertinimai
        if (tinkamiPazymiai) {
            skaiciuotiIsFailo(studentas, tinkamiPazymiai, studentai);
        } else {
            cout << "Studentas " << studentas.vardas << " " << studentas.pavarde << " neturi galutiniu pazymiu del neteisingu duomenu." << endl;
        }
    }
}

void skaitytiIrIsvestiDuomenis(const string& inputFileName, const string& outputFileName) {
    vector<Studentas> studentai;
    skaitytiDuomenisIsFailo(inputFileName, studentai);

    ofstream outputFile(outputFileName);
    if (!outputFile) {
        throw runtime_error("Nepavyko atidaryti isvesties failo " + outputFileName);
    }

    outputFile << left << setw(16) << "Pavarde" << setw(16) << "Vardas" 
               << setw(25) << "Galutinis Vidurkis" << "Galutine Mediana" << endl;
    outputFile << string(70, '-') << endl;

    for (const auto& studentas : studentai) {
        outputFile << left << setw(16) << studentas.pavarde << setw(16) << studentas.vardas 
                   << setw(25) << fixed << setprecision(2) << studentas.galutinisVidurkis 
                   << fixed << setprecision(2) << studentas.galutineMediana << endl;
    }

    outputFile.close();
}