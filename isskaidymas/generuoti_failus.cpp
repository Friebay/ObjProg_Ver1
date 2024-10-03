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

void generuotiStudentuFaila(int studentuKiekis, const string& failoPavadinimas) {
    ofstream isvedimoFailas(failoPavadinimas);
    if (!isvedimoFailas.is_open()) {
        throw runtime_error("Nepavyko atidaryti failo " + failoPavadinimas);
    }

    // Generuojamas antraštės eilutė
    ostringstream headerStream;
    headerStream << left << setw(16) << "Vardas" << setw(16) << "Pavarde" << setw(20) << " ";
    for (int i = 1; i <= 8; ++i) {
        headerStream << setw(10) << ("ND" + to_string(i));
    }

    headerStream << setw(9) << ("ND9");

    for (int i = 10; i <= 15; ++i) {
        headerStream << setw(10) << ("ND" + to_string(i));
    }
    headerStream << setw(9) << "Egz." << "\n";
    isvedimoFailas << headerStream.str();

    // Naudojamas stringstream, kad kauptų studentų duomenis prieš įrašymą
    ostringstream outputStream;
    for (int i = 0; i < studentuKiekis; ++i) {
        string vardas = generuotiVardaPavarde();  // Generuojami vardai ir pavardės
        string pavarde = generuotiVardaPavarde();

        outputStream << left << setw(16) << vardas << setw(16) << pavarde << setw(13) << " ";

        // Generuojami 15 pažymių
        for (int j = 0; j < 15; ++j) {
            outputStream << right << setw(10) << generuotiSkaiciu(1, 10);
        }

        // Generuojamas egzamino pažymys
        outputStream << right << setw(10) << generuotiSkaiciu(1, 10) << "\n";
    }

    // Galutinis rašymas iš stream į failą
    isvedimoFailas << outputStream.str();

    isvedimoFailas.close();
    cout << "Failas '" << failoPavadinimas << "' su " << studentuKiekis << " studentais buvo sugeneruotas." << '\n';
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
    string failoPavadinimas = "studentai_" + to_string(studentuKiekis) + ".txt";

    try {
        generuotiStudentuFaila(studentuKiekis, failoPavadinimas);
    } catch (const exception& e) {
        cout << "Klaida: " << e.what() << '\n';
    }
}