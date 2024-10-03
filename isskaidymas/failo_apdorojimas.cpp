#include "failo_apdorojimas.h"

void skaiciuotiIsFailo(Studentas& studentas, bool tinkamiPazymiai, vector<Studentas>& studentai) {
    if (tinkamiPazymiai && !studentas.pazymiai.empty()) {
        studentas.egzaminoPazymys = studentas.pazymiai.back();
        studentas.pazymiai.pop_back();

        studentas.vidurkis = skaiciuotiVidurki(studentas.pazymiai);
        studentas.mediana = skaiciuotiMediana(studentas.pazymiai);
        
        studentas.galutinisVidurkis = 0.4 * studentas.vidurkis + 0.6 * studentas.egzaminoPazymys;
        studentas.galutineMediana = 0.4 * studentas.mediana + 0.6 * studentas.egzaminoPazymys;

        studentai.push_back(move(studentas));
    } else {
        cout << "Klaida: truksta pazymiu studentui " << studentas.vardas << " " << studentas.pavarde << '\n';
    }
}

void skaitytiDuomenisIsFailo(const string& failoPavadinimas, vector<Studentas>& studentai, long long& trukmeSkaitymo, long long& trukmeVidurkio) {
    auto pradziaSkaitymo = std::chrono::high_resolution_clock::now();

    ifstream failas(failoPavadinimas, std::ios::in | std::ios::binary);
    if (!failas) {
        throw runtime_error("Failo " + failoPavadinimas + " nera.");
    }

    string buffer;
    buffer.reserve(1048576); // Use a buffer to reduce reallocations

    // Skip the header
    getline(failas, buffer);

    while (getline(failas, buffer)) {
        if (buffer.length() < 52) { // Minimum length check
            throw runtime_error("Invalid line length: " + buffer);
        }

        Studentas studentas;
        
        // Parse vardas and pavarde directly by indices
        studentas.vardas = buffer.substr(0, 16);
        studentas.pavarde = buffer.substr(16, 32);

        // Lambda function to trim leading and trailing whitespaces
        auto trim = [](std::string &str) {
            // Remove leading whitespaces
            str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
            // Remove trailing whitespaces
            str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }).base(), str.end());
        };

        trim(studentas.pavarde);
        
        // Preallocate space for grades (assuming max ~25 grades)
        studentas.pazymiai.reserve(25);

        // Parse grades starting from position 52
        size_t pos = 52;
        bool tinkamiPazymiai = true;
        
        while (pos < buffer.length()) {
            // Skip whitespace
            while (pos < buffer.length() && isspace(buffer[pos])) pos++;
            if (pos >= buffer.length()) break;

            int grade = 0;
            bool valid = true;
            
            // Check if the current character is a digit
            if (isdigit(buffer[pos])) {
                // Manually parse the integer
                while (pos < buffer.length() && isdigit(buffer[pos])) {
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
            while (pos < buffer.length() && isspace(buffer[pos])) pos++;
        }

        // Process student
        skaiciuotiIsFailo(studentas, tinkamiPazymiai, studentai);
    }

    auto pabaigaSkaitymo = std::chrono::high_resolution_clock::now();
    trukmeSkaitymo = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaSkaitymo - pradziaSkaitymo).count();
    trukmeVidurkio = 0; // Assuming average time is computed later
}

void skaitytiIrIsvestiDuomenis(const string& ivestiesFailoPavadinimas, const string& outputFileName, long long& trukmeSkaitymo, long long& trukmeVidurkio, long long& trukmeIrasymo) {
    vector<Studentas> studentai;
    skaitytiDuomenisIsFailo(ivestiesFailoPavadinimas, studentai, trukmeSkaitymo, trukmeVidurkio);

    auto pradziaIrasimo = std::chrono::high_resolution_clock::now();
    
    // Use stringstream for buffered output
    ostringstream buffer;

    // Write header
    buffer << left << setw(16) << "Pavarde" 
           << setw(16) << "Vardas" 
           << setw(25) << "Galutinis Vidurkis" 
           << "Galutine Mediana" << '\n';
    buffer << string(70, '-') << '\n';

    // Pre-format the student data into the buffer
    for (const auto& studentas : studentai) {
        buffer << left << setw(16) << studentas.pavarde
               << setw(16) << studentas.vardas
               << setw(25) << fixed << setprecision(2) << studentas.galutinisVidurkis
               << fixed << setprecision(2) << studentas.galutineMediana
               << '\n';
    }

    // Open file for output
    ofstream outputFile(outputFileName, std::ios::out | std::ios::binary);
    if (!outputFile) {
        throw runtime_error("Nepavyko atidaryti isvesties failo " + outputFileName);
    }

    // Write the entire buffer to the file at once
    outputFile << buffer.str();
    outputFile.close();

    auto pabaigaIrasimo = std::chrono::high_resolution_clock::now();
    trukmeIrasymo = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaIrasimo - pradziaIrasimo).count();
}

void padalintiRezultatuFaila(const string& ivestiesFailoPavadinimas, const string& islaikiusiuFailoPavadinimas, const string& neislaikiusiuFailoPavadinimas) {
    // Atidaromas įvesties failas binariniu režimu
    ifstream ivestiesFailas(ivestiesFailoPavadinimas, std::ios::in | std::ios::binary);
    if (!ivestiesFailas) {
        throw runtime_error("Nepavyko atidaryti ivesties failo " + ivestiesFailoPavadinimas);
    }

    // Skaitomas įvesties failas į buferį
    ivestiesFailas.seekg(0, std::ios::end);
    size_t failoDydis = ivestiesFailas.tellg();
    ivestiesFailas.seekg(0, std::ios::beg);
    vector<char> buferis(failoDydis);
    ivestiesFailas.read(buferis.data(), failoDydis);
    ivestiesFailas.close();

    // Atidaromi išvesties failai vieną kartą
    ofstream islaikiusiuFailas(islaikiusiuFailoPavadinimas, std::ios::out | std::ios::binary);
    ofstream neislaikiusiuFailas(neislaikiusiuFailoPavadinimas, std::ios::out | std::ios::binary);
    if (!islaikiusiuFailas || !neislaikiusiuFailas) {
        throw runtime_error("Nepavyko atidaryti išvesties failų");
    }

    // Sukuriama eilutes string
    string failoTurinys(buferis.begin(), buferis.end());
    istringstream iss(failoTurinys);
    string eilute;

    // Pirmoji ir antroji antraštės eilutės - kopijuojamos į abu išvesties failus
    getline(iss, eilute);
    islaikiusiuFailas << eilute << '\n';
    neislaikiusiuFailas << eilute << '\n';

    getline(iss, eilute);
    islaikiusiuFailas << eilute << '\n';
    neislaikiusiuFailas << eilute << '\n';

    // Eilinė turinio peržiūra ir skirstymas
    while (getline(iss, eilute)) {
        // Naudojame rfind, kad rastume paskutinį tarpo simbolį
        size_t paskutinisTarpas = eilute.rfind(' ');
        if (paskutinisTarpas != string::npos) {
            // Gauti galutinį vidurkį kaip float
            float galutinisVidurkis = stof(eilute.substr(paskutinisTarpas + 1));

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
