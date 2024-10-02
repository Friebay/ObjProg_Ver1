#include "failo_apdorojimas.h"
#include <iomanip>
#include <sstream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <cstring>
#include <chrono>
#include <stdexcept>
#include <cstdlib>


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
            //studentai.push_back(studentas);
            studentai.push_back(std::move(studentas));
        } else {
            cout << "Klaida: truksta pazymiu studentui " << studentas.vardas << " " << studentas.pavarde << endl;
        }
    } else {
        cout << "Studentas " << studentas.vardas << " " << studentas.pavarde << " neturi galutiniu pazymiu del neteisingu duomenu." << endl;
    }
}

// Funkcija skaito duomenis iš failo ir apdoroja kiekvieną studentą
/*
void skaitytiDuomenisIsFailo(const string& failoPavadinimas, vector<Studentas>& studentai, long long& trukmeSkaitymo, long long& trukmeVidurkio) {
    auto pradziaSkaitymo = std::chrono::high_resolution_clock::now();

    // Atidaromas failas
    ifstream failas(failoPavadinimas);
    if (!failas) {
        throw runtime_error("Failo " + failoPavadinimas + " nera.");
    }
    string eilute;
    getline(failas, eilute);  // Praleidžiama antraštės eilutė

    vector<Studentas> nuskaitytStudentai;

    // Skaitoma kiekviena eilutė
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
            nuskaitytStudentai.push_back(studentas);
        } else {
            cout << "Studentas " << studentas.vardas << " " << studentas.pavarde << " neturi galutiniu pazymiu del neteisingu duomenu." << endl;
        }
    }

    auto pabaigaSkaitymo = std::chrono::high_resolution_clock::now();
    trukmeSkaitymo = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaSkaitymo - pradziaSkaitymo).count();

    auto pradziaVidurkio = std::chrono::high_resolution_clock::now();

    for (auto& studentas : nuskaitytStudentai) {
        skaiciuotiIsFailo(studentas, true, studentai);
    }

    auto pabaigaVidurkio = std::chrono::high_resolution_clock::now();
    trukmeVidurkio = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaVidurkio - pradziaVidurkio).count();
}
*/



// // Funkcija skaito duomenis iš failo ir apdoroja kiekvieną studentą
// void skaitytiDuomenisIsFailo(const std::string& failoPavadinimas, std::vector<Studentas>& studentai, long long& trukmeSkaitymo, long long& trukmeVidurkio) {
//     auto pradziaSkaitymo = std::chrono::high_resolution_clock::now();

//     // Atidaromas failas binariniu režimu ir skaitomas turinys į buferį
//     std::ifstream failas(failoPavadinimas, std::ios::in | std::ios::binary);
//     if (!failas) {
//         throw std::runtime_error("Failo " + failoPavadinimas + " nera.");
//     }

//     // Gauti failo dydį ir perskaityti jį į buferį
//     failas.seekg(0, std::ios::end);
//     std::size_t failoDydis = failas.tellg();
//     failas.seekg(0, std::ios::beg);

//     std::vector<char> buferis(failoDydis);
//     failas.read(buferis.data(), failoDydis);
//     failas.close();

//     // Naudoti stringstream skaitant iš buferio
//     std::istringstream failoTurinys(std::string(buferis.begin(), buferis.end()));
//     std::string eilute;
    
//     // Praleisti antraštės eilutę
//     std::getline(failoTurinys, eilute);

//     // Inicializuoti studento objektą iš anksto, kad nereikėtų sukurti kiekviename ciklo žingsnyje
//     Studentas studentas;
//     std::istringstream iss;
//     std::string pazymysStr;
//     bool tinkamiPazymiai;

//     // Skaitomos kiekvienos eilutės studentų duomenys
//     while (std::getline(failoTurinys, eilute)) {
//         iss.clear();  // Išvalyti stream būseną
//         iss.str(eilute);  // Panaudoti tą patį stream objektą naujai eilutei

//         if (!(iss >> studentas.vardas >> studentas.pavarde)) {
//             throw std::runtime_error("Klaida nuskaitant varda ir pavarde.");
//         }

//         studentas.pazymiai.clear();  // Išvalyti pažymius iš ankstesnio studento
//         tinkamiPazymiai = true;

//         while (iss >> pazymysStr) {
//             try {
//                 // Greitesnis skaičių validavimas
//                 int pazymys = std::stoi(pazymysStr);
//                 if (pazymys < 0 || pazymys > 10) {
//                     throw std::out_of_range("Klaida: pazymys turi buti tarp 0 ir 10.");
//                 }
//                 studentas.pazymiai.push_back(pazymys);
//             } catch (const std::exception& e) {
//                 // Netinkamas pažymys aptiktas
//                 tinkamiPazymiai = false;
//                 break;
//             }
//         }

//         if (tinkamiPazymiai && !studentas.pazymiai.empty()) {
//             studentas.egzaminoPazymys = studentas.pazymiai.back();  // Paskutinis pažymys yra egzamino pažymys
//             studentas.pazymiai.pop_back();  // Pašalinti egzamino pažymį iš sąrašo
//             studentas.vidurkis = skaiciuotiVidurki(studentas.pazymiai);
//             studentas.mediana = skaiciuotiMediana(studentas.pazymiai);
//             studentas.galutinisVidurkis = 0.4 * studentas.vidurkis + 0.6 * studentas.egzaminoPazymys;
//             studentas.galutineMediana = 0.4 * studentas.mediana + 0.6 * studentas.egzaminoPazymys;

//             studentai.push_back(std::move(studentas));  // Naudoti move, kad išvengti kopijavimo
//         }
//     }

//     auto pabaigaSkaitymo = std::chrono::high_resolution_clock::now();
//     trukmeSkaitymo = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaSkaitymo - pradziaSkaitymo).count();

//     // Apdorojimo laikas (vidurkių skaičiavimas jau įtrauktas anksčiau)
//     auto pradziaVidurkio = std::chrono::high_resolution_clock::now();
//     auto pabaigaVidurkio = std::chrono::high_resolution_clock::now();
//     trukmeVidurkio = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaVidurkio - pradziaVidurkio).count();
// }



void skaitytiDuomenisIsFailo(const std::string& failoPavadinimas, std::vector<Studentas>& studentai, long long& trukmeSkaitymo, long long& trukmeVidurkio) {
    auto pradziaSkaitymo = std::chrono::high_resolution_clock::now();

    // Open file for reading in binary mode
    std::ifstream failas(failoPavadinimas, std::ios::binary);
    if (!failas) {
        throw std::runtime_error("Failo " + failoPavadinimas + " nera.");
    }

    // Read the entire file into a buffer
    failas.seekg(0, std::ios::end);
    std::size_t failoDydis = failas.tellg();
    failas.seekg(0, std::ios::beg);

    // Allocate buffer to hold the file contents
    std::vector<char> buferis(failoDydis);
    failas.read(buferis.data(), failoDydis);
    failas.close();

    const char* ptr = buferis.data();
    const char* end = buferis.data() + failoDydis;

    // Skip header
    while (*ptr != '\n' && ptr < end) ++ptr;
    ++ptr;  // Move past the newline character

    Studentas studentas;
    studentas.pazymiai.reserve(15);  // Pre-allocate space for grades

    while (ptr < end) {
        // Extract name and surname (first 40 characters, 20 each)
        studentas.vardas = std::string(ptr, 20);
        ptr += 20;
        studentas.pavarde = std::string(ptr, 20);
        ptr += 20;

        studentas.pazymiai.clear();  // Clear previous grades

        // Extract grades (15 grades, 5 characters wide)
        for (int i = 0; i < 15; ++i) {
            studentas.pazymiai.push_back(std::atoi(ptr));
            ptr += 5;  // Move past the grade
        }

        // Extract exam grade (next 10 characters, 10 chars wide)
        studentas.egzaminoPazymys = std::atoi(ptr);
        ptr += 10;

        // Move to the next line (skip to the newline character)
        while (*ptr != '\n' && ptr < end) ++ptr;
        ++ptr;  // Move past the newline

        // Calculate student's final results
        studentas.vidurkis = skaiciuotiVidurki(studentas.pazymiai);
        studentas.mediana = skaiciuotiMediana(studentas.pazymiai);
        studentas.galutinisVidurkis = 0.4 * studentas.vidurkis + 0.6 * studentas.egzaminoPazymys;
        studentas.galutineMediana = 0.4 * studentas.mediana + 0.6 * studentas.egzaminoPazymys;

        // Add the student to the vector (move semantics to avoid copying)
        studentai.push_back(std::move(studentas));
    }

    auto pabaigaSkaitymo = std::chrono::high_resolution_clock::now();
    trukmeSkaitymo = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaSkaitymo - pradziaSkaitymo).count();

    trukmeVidurkio = 0;
}



void skaitytiIrIsvestiDuomenis(const string& ivestiesFailoPavadinimas, const string& outputFileName, long long& trukmeSkaitymo, long long& trukmeVidurkio, long long& trukmeIrasymo) {
    vector<Studentas> studentai;
    skaitytiDuomenisIsFailo(ivestiesFailoPavadinimas, studentai, trukmeSkaitymo, trukmeVidurkio);

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
    trukmeIrasymo = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaIrasimo - pradziaIrasimo).count();
    
}

/*
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
*/

void padalintiRezultatuFaila(const std::string& ivestiesFailoPavadinimas, const std::string& islaikiusiuFailoPavadinimas, const std::string& neislaikiusiuFailoPavadinimas) {
    // Atidaromas įvesties failas binariniu režimu
    std::ifstream ivestiesFailas(ivestiesFailoPavadinimas, std::ios::in | std::ios::binary);
    if (!ivestiesFailas) {
        throw std::runtime_error("Nepavyko atidaryti ivesties failo " + ivestiesFailoPavadinimas);
    }

    // Skaitomas įvesties failas į buferį
    ivestiesFailas.seekg(0, std::ios::end);
    std::size_t failoDydis = ivestiesFailas.tellg();
    ivestiesFailas.seekg(0, std::ios::beg);
    std::vector<char> buferis(failoDydis);
    ivestiesFailas.read(buferis.data(), failoDydis);
    ivestiesFailas.close();

    // Atidaromi išvesties failai vieną kartą
    std::ofstream islaikiusiuFailas(islaikiusiuFailoPavadinimas);
    std::ofstream neislaikiusiuFailas(neislaikiusiuFailoPavadinimas);
    if (!islaikiusiuFailas || !neislaikiusiuFailas) {
        throw std::runtime_error("Nepavyko atidaryti išvesties failų");
    }

    std::string failoTurinys(buferis.begin(), buferis.end());
    std::istringstream iss(failoTurinys);
    std::string eilute;

    // Kopijuojama antraštė į abu failus
    std::getline(iss, eilute);
    islaikiusiuFailas << eilute << '\n';
    neislaikiusiuFailas << eilute << '\n';

    // Antroji eilutė (nėra būtina tikrinti)
    std::getline(iss, eilute);
    islaikiusiuFailas << eilute << '\n';
    neislaikiusiuFailas << eilute << '\n';

    // Per visą likusį turinį
    while (std::getline(iss, eilute)) {
        // Rasti paskutinį tarpo simbolį, kad būtų galima greitai išgauti galutinį vidurkį
        std::size_t paskutinisTarpas = eilute.rfind(' ');
        if (paskutinisTarpas != std::string::npos) {
            // Naudojame substring norint gauti galutinį vidurkį kaip float
            float galutinisVidurkis = std::stof(eilute.substr(paskutinisTarpas + 1));

            // Patikriname vidurkį ir rašome į atitinkamą failą
            if (galutinisVidurkis >= 5.0f) {
                islaikiusiuFailas << eilute << '\n';
            } else {
                neislaikiusiuFailas << eilute << '\n';
            }
        }
    }

    // Uždaryti išvesties failus
    islaikiusiuFailas.close();
    neislaikiusiuFailas.close();
}
