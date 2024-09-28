#include "funkcijos.h"
#include <fstream>
#include <iomanip>

void generuotiStudentuFaila(int studentuKiekis, const string& failoPavadinimas) {
    std::ofstream isvedimoFailas(failoPavadinimas);
    if (!isvedimoFailas.is_open()) {
        throw runtime_error("Failo " + failoPavadinimas + " nera.");
    }

    isvedimoFailas << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
    for (int i = 1; i <= 15; ++i) {
        isvedimoFailas << setw(5) << "ND" + std::to_string(i);
    }
    isvedimoFailas << setw(10) << "Egz." << endl;

    for (int i = 0; i < studentuKiekis; ++i) {
        string vardas = generuotiVardaPavarde();
        string pavarde = generuotiVardaPavarde();
        
        isvedimoFailas << left << setw(20) << vardas << setw(20) << pavarde;
        
        for (int j = 0; j < 15; ++j) {
            isvedimoFailas << setw(5) << generuotiSkaiciu(1, 10);
        }
        
        isvedimoFailas << setw(10) << generuotiSkaiciu(1, 10) << endl;
    }

    isvedimoFailas.close();
    cout << "Failas '" << failoPavadinimas << "' su " << studentuKiekis << " studentais buvo sugeneruotas." << endl;
}

void generuotiFaila() {
    vector<int> fileSizes = {1000, 10000, 100000, 1000000, 10000000};
    
    cout << "Kiek studentu norite sugeneruoti:" << endl;
    for (int i = 0; i < fileSizes.size(); ++i) {
        cout << i + 1 << ". " << fileSizes[i] << " studentu." << endl;
    }

    int choice;
    while (true) {
        cout << "Prasome ivesti skaiciu (1-5): ";
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neteisingas pasirinkimas. Prasome ivesti 1, 2, 3, 4 arba 5." << endl;
        } else {
            break;
        }
    }

    int studentuKiekis = fileSizes[choice - 1];
    string failoPavadinimas = "studentai_" + std::to_string(studentuKiekis) + ".txt";

    try {
        generuotiStudentuFaila(studentuKiekis, failoPavadinimas);
    } catch (const exception& e) {
        cout << "Klaida: " << e.what() << endl;
    }
}