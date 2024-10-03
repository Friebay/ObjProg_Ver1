#include "funkcijos.h"
#include <fstream>
#include <iomanip>
#include <sstream>

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>

void generuotiStudentuFaila(int studentuKiekis, const std::string& failoPavadinimas) {
    std::ofstream isvedimoFailas(failoPavadinimas);
    if (!isvedimoFailas.is_open()) {
        throw std::runtime_error("Nepavyko atidaryti failo " + failoPavadinimas);
    }

    // Generuojamas antraštės eilutė
    std::ostringstream headerStream;
    headerStream << std::left << std::setw(25) << "Vardas" << std::setw(25) << "Pavarde" << std::setw(2) << " "; // Adjusted widths
    for (int i = 1; i <= 8; ++i) {
        headerStream << std::setw(10) << ("ND" + std::to_string(i));
    }

    headerStream << std::setw(9) << ("ND9");

    for (int i = 10; i <= 15; ++i) {
        headerStream << std::setw(10) << ("ND" + std::to_string(i));
    }
    headerStream << std::setw(9) << "Egz." << "\n";
    isvedimoFailas << headerStream.str();

    // Naudojamas stringstream, kad kauptų studentų duomenis prieš įrašymą
    std::ostringstream outputStream;
    for (int i = 0; i < studentuKiekis; ++i) {
        std::string vardas = generuotiVardaPavarde();  // Generuojami vardai ir pavardės
        std::string pavarde = generuotiVardaPavarde();

        outputStream << std::left << std::setw(16) << (vardas) << std::right << std::setw(16) << (pavarde) << std::setw(13) << " ";;

        // Generuojami 15 pažymių
        for (int j = 0; j < 15; ++j) {
            outputStream << std::right << std::setw(10) << generuotiSkaiciu(1, 10);
        }

        // Generuojamas egzamino pažymys
        outputStream << std::right << std::setw(10) << generuotiSkaiciu(1, 10) << "\n";
    }

    // Galutinis rašymas iš stream į failą
    isvedimoFailas << outputStream.str();

    isvedimoFailas.close();
    std::cout << "Failas '" << failoPavadinimas << "' su " << studentuKiekis << " studentais buvo sugeneruotas." << '\n';
}

void generuotiFaila() {
    vector<int> fileSizes = {1000, 10000, 100000, 1000000, 10000000};
    
    cout << "Kiek studentu norite sugeneruoti:" << '\n';
    for (int i = 0; i < fileSizes.size(); ++i) {
        cout << i + 1 << ". " << fileSizes[i] << " studentu." << '\n';
    }

    int choice;
    while (true) {
        cout << "Prasome ivesti skaiciu (1-5): ";
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neteisingas pasirinkimas. Prasome ivesti 1, 2, 3, 4 arba 5." << '\n';
        } else {
            break;
        }
    }

    int studentuKiekis = fileSizes[choice - 1];
    string failoPavadinimas = "studentai_" + std::to_string(studentuKiekis) + ".txt";

    try {
        generuotiStudentuFaila(studentuKiekis, failoPavadinimas);
    } catch (const exception& e) {
        cout << "Klaida: " << e.what() << '\n';
    }
}