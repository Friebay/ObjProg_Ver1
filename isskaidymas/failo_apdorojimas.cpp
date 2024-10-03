#include "failo_apdorojimas.h"



using namespace std;

void skaiciuotiIsFailo(Studentas& studentas, bool tinkamiPazymiai, vector<Studentas>& studentai) {
    if (tinkamiPazymiai && !studentas.pazymiai.empty()) {
        studentas.egzaminoPazymys = studentas.pazymiai.back();
        studentas.pazymiai.pop_back();

        studentas.vidurkis = skaiciuotiVidurki(studentas.pazymiai);
        studentas.mediana = skaiciuotiMediana(studentas.pazymiai);
        
        studentas.galutinisVidurkis = 0.4 * studentas.vidurkis + 0.6 * studentas.egzaminoPazymys;
        studentas.galutineMediana = 0.4 * studentas.mediana + 0.6 * studentas.egzaminoPazymys;

        studentai.push_back(std::move(studentas));
    } else {
        cout << "Klaida: truksta pazymiu studentui " << studentas.vardas << " " << studentas.pavarde << '\n';
    }
}
/*
void skaitytiDuomenisIsFailo(const std::string& failoPavadinimas, std::vector<Studentas>& studentai, long long& trukmeSkaitymo, long long& trukmeVidurkio) {
    auto pradziaSkaitymo = chrono::high_resolution_clock::now();

    // Open the file and read it into memory at once
    ifstream failas(failoPavadinimas, ios::in | ios::binary | ios::ate);
    if (!failas) {
        throw runtime_error("Failo " + failoPavadinimas + " nera.");
    }

    // Get file size
    size_t dydis = failas.tellg();
    failas.seekg(0, ios::beg);

    // Allocate buffer and read the whole file
    vector<char> buffer(dydis);
    failas.read(buffer.data(), dydis);
    failas.close();

    stringstream iss(string(buffer.data(), dydis));  // Convert the buffer into a stringstream for parsing

    string eilute;
    getline(iss, eilute);  // Skip the header

    // Process each student
    while (getline(iss, eilute)) {
        istringstream eilutesStream(eilute);
        Studentas studentas;
        
        if (!(eilutesStream >> studentas.vardas >> studentas.pavarde)) {
            throw runtime_error("Klaida nuskaitant varda ir pavarde.");
        }

        string pazymysStr;
        bool tinkamiPazymiai = true;

        // Skaitomi pažymiai
        while (eilutesStream >> pazymysStr) {
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
                cout << "Klaida: neteisingas pazymys: " << pazymysStr << " - " << e.what() << '\n';
                tinkamiPazymiai = false;
                break;
            } catch (const out_of_range& e) {
                cout << e.what() << '\n';
                tinkamiPazymiai = false;
                break;
            }
        }

        // If valid, calculate and store the results
        skaiciuotiIsFailo(studentas, tinkamiPazymiai, studentai);
    }

    auto pabaigaSkaitymo = chrono::high_resolution_clock::now();
    trukmeSkaitymo = chrono::duration_cast<chrono::milliseconds>(pabaigaSkaitymo - pradziaSkaitymo).count();
    trukmeVidurkio = 0;
}
*/



void skaitytiDuomenisIsFailo(const std::string& failoPavadinimas, std::vector<Studentas>& studentai, long long& trukmeSkaitymo, long long& trukmeVidurkio) {
    auto pradziaSkaitymo = std::chrono::high_resolution_clock::now();

    std::ifstream failas(failoPavadinimas, std::ios::in | std::ios::binary);
    if (!failas) {
        throw std::runtime_error("Failo " + failoPavadinimas + " nera.");
    }

    std::string buffer;
    buffer.reserve(1048576); // Use a buffer to reduce reallocations

    // Skip the header
    std::getline(failas, buffer);

    while (std::getline(failas, buffer)) {
        if (buffer.length() < 52) { // Minimum length check
            throw std::runtime_error("Invalid line length: " + buffer);
        }

        Studentas studentas;
        
        // Parse vardas and pavarde directly by indices
        studentas.vardas = buffer.substr(0, 16);
        studentas.pavarde = buffer.substr(0, 16);

        // Preallocate space for grades (assuming max ~25 grades)
        studentas.pazymiai.reserve(25);

        // Parse grades starting from position 52
        size_t pos = 52;
        bool tinkamiPazymiai = true;
        
        while (pos < buffer.length()) {
            // Skip whitespace
            while (pos < buffer.length() && std::isspace(buffer[pos])) pos++;
            if (pos >= buffer.length()) break;

            int grade = 0;
            bool valid = true;
            
            // Check if the current character is a digit
            if (std::isdigit(buffer[pos])) {
                // Manually parse the integer
                while (pos < buffer.length() && std::isdigit(buffer[pos])) {
                    grade = grade * 10 + (buffer[pos] - '0');
                    pos++;
                }

                // Check if the grade is valid (0-10)
                if (grade < 0 || grade > 10) {
                    valid = false;
                }
            } else {
                // If not a digit, skip to the next non-space character
                valid = false; // Mark the grade as invalid
                pos++; // Move past the invalid character
            }

            // Check if the grade is valid (0-10)
            if (grade < 0 || grade > 10) {
                valid = false;
            }

            if (valid) {
                studentas.pazymiai.push_back(grade);
            } else {
                tinkamiPazymiai = false;
                break;
            }
            
            // Skip the space after the grade
            while (pos < buffer.length() && std::isspace(buffer[pos])) pos++;
        }

        // Process student
        skaiciuotiIsFailo(studentas, tinkamiPazymiai, studentai);
    }

    auto pabaigaSkaitymo = std::chrono::high_resolution_clock::now();
    trukmeSkaitymo = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaSkaitymo - pradziaSkaitymo).count();
    trukmeVidurkio = 0; // Assuming average time is computed later
}

/*
void skaitytiIrIsvestiDuomenis(const string& ivestiesFailoPavadinimas, const string& outputFileName, long long& trukmeSkaitymo, long long& trukmeVidurkio, long long& trukmeIrasymo) {
    vector<Studentas> studentai;
    skaitytiDuomenisIsFailo(ivestiesFailoPavadinimas, studentai, trukmeSkaitymo, trukmeVidurkio);

    auto pradziaIrasimo = std::chrono::high_resolution_clock::now();
    ofstream outputFile(outputFileName);
    if (!outputFile) {
        throw runtime_error("Nepavyko atidaryti isvesties failo " + outputFileName);
    }

    outputFile << left << setw(16) << "Pavarde" << setw(16) << "Vardas" << setw(25) << "Galutinis Vidurkis" << "Galutine Mediana" << '\n';
    outputFile << string(70, '-') << '\n';

    for (const auto& studentas : studentai) {
        outputFile << left << setw(16) << studentas.pavarde << setw(16) << studentas.vardas << setw(25) << fixed << setprecision(2) << studentas.galutinisVidurkis << fixed << setprecision(2) << studentas.galutineMediana << '\n';
    }
    outputFile.close();

    auto pabaigaIrasimo = std::chrono::high_resolution_clock::now();
    trukmeIrasymo = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaIrasimo - pradziaIrasimo).count();
    
}
*/



void skaitytiIrIsvestiDuomenis(const std::string& ivestiesFailoPavadinimas, const std::string& outputFileName, long long& trukmeSkaitymo, long long& trukmeVidurkio, long long& trukmeIrasymo) {
    std::vector<Studentas> studentai;
    skaitytiDuomenisIsFailo(ivestiesFailoPavadinimas, studentai, trukmeSkaitymo, trukmeVidurkio);

    auto pradziaIrasimo = std::chrono::high_resolution_clock::now();
    
    // Use stringstream for buffered output
    std::ostringstream buffer;

    // Write header
    buffer << std::left << std::setw(16) << "Pavarde" 
           << std::setw(16) << "Vardas" 
           << std::setw(25) << "Galutinis Vidurkis" 
           << "Galutine Mediana" << '\n';
    buffer << std::string(70, '-') << '\n';

    // Pre-format the student data into the buffer
    for (const auto& studentas : studentai) {
        buffer << std::left << std::setw(16) << studentas.pavarde
               << std::setw(16) << studentas.vardas
               << std::setw(25) << std::fixed << std::setprecision(2) << studentas.galutinisVidurkis
               << std::fixed << std::setprecision(2) << studentas.galutineMediana
               << '\n';
    }

    // Open file for output
    std::ofstream outputFile(outputFileName, std::ios::out | std::ios::binary);
    if (!outputFile) {
        throw std::runtime_error("Nepavyko atidaryti isvesties failo " + outputFileName);
    }

    // Write the entire buffer to the file at once
    outputFile << buffer.str();
    outputFile.close();

    auto pabaigaIrasimo = std::chrono::high_resolution_clock::now();
    trukmeIrasymo = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaIrasimo - pradziaIrasimo).count();
}

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
    std::ofstream islaikiusiuFailas(islaikiusiuFailoPavadinimas, std::ios::out | std::ios::binary);
    std::ofstream neislaikiusiuFailas(neislaikiusiuFailoPavadinimas, std::ios::out | std::ios::binary);
    if (!islaikiusiuFailas || !neislaikiusiuFailas) {
        throw std::runtime_error("Nepavyko atidaryti išvesties failų");
    }

    // Sukuriama eilutes string
    std::string failoTurinys(buferis.begin(), buferis.end());
    std::istringstream iss(failoTurinys);
    std::string eilute;

    // Pirmoji ir antroji antraštės eilutės - kopijuojamos į abu išvesties failus
    std::getline(iss, eilute);
    islaikiusiuFailas << eilute << '\n';
    neislaikiusiuFailas << eilute << '\n';

    std::getline(iss, eilute);
    islaikiusiuFailas << eilute << '\n';
    neislaikiusiuFailas << eilute << '\n';

    // Eilinė turinio peržiūra ir skirstymas
    while (std::getline(iss, eilute)) {
        // Naudojame rfind, kad rastume paskutinį tarpo simbolį
        std::size_t paskutinisTarpas = eilute.rfind(' ');
        if (paskutinisTarpas != std::string::npos) {
            // Gauti galutinį vidurkį kaip float
            float galutinisVidurkis = std::stof(eilute.substr(paskutinisTarpas + 1));

            // Patikrinimas pagal galutinį vidurkį ir rašymas į atitinkamą failą
            if (galutinisVidurkis >= 5.0f) {
                islaikiusiuFailas << eilute << '\n'; // Buffer successful students
            } else {
                neislaikiusiuFailas << eilute << '\n'; // Buffer failed students
            }
        }
    }

    // Uždaryti išvesties failus
    islaikiusiuFailas.close();
    neislaikiusiuFailas.close();
}
