#include "List_funkcijos.h"
#include "Vec_funkcijos_papildomos.h"

void List_generuotiStudentuFaila(int studentuKiekis, const string& failoPavadinimas) {
    ofstream isvedimoFailas(failoPavadinimas);
    if (!isvedimoFailas.is_open()) {
        throw runtime_error("Nepavyko atidaryti failo " + failoPavadinimas);
    }

    // Generuojama antraštės eilutė
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
    cout << "Failas '" << failoPavadinimas << "' su " << studentuKiekis << " studentais buvo sugeneruotas.\n";
}

void List_generuotiFaila() {
    const vector<int> studentuSkaicius = {1000, 10000, 100000, 1000000, 10000000};
    
    cout << "Kiek studentu norite sugeneruoti:\n";
    for (int i = 0; i < studentuSkaicius.size(); ++i) {
        cout << i + 1 << ". " << studentuSkaicius[i] << " studentu.\n";
    }

    int pasirinkimas = 0;
    while (true) {
        cout << "Prasome ivesti skaiciu (1-5): ";
        cin >> pasirinkimas;
        if (cin.fail() || pasirinkimas < 1 || pasirinkimas > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neteisingas pasirinkimas. Prasome ivesti nuo skaiciu nuo 1 iki 5.\n";
        } else {
            break;
        }
    }

    int studentuKiekis = studentuSkaicius[pasirinkimas - 1];
    string failoPavadinimas = "txt_failai/studentai_" + to_string(studentuKiekis) + ".txt";

    try {
        auto pradziaSkaitymo = std::chrono::high_resolution_clock::now();
        List_generuotiStudentuFaila(studentuKiekis, failoPavadinimas);
        auto pabaigaSkaitymo = std::chrono::high_resolution_clock::now();
        long long trukmeSkaitymo = std::chrono::duration_cast<std::chrono::milliseconds>(pabaigaSkaitymo - pradziaSkaitymo).count();
        cout << "Duomenu generavimas ir failo irasymas truko " << trukmeSkaitymo << "ms.\n";
    } catch (const exception& e) {
        cout << "Klaida: " << e.what() << '\n';
    }
}