#include "Vec_funkcijos.h"
#include "Vec_funkcijos_papildomos.h"
#include "Vec_failo_apdorojimas.h"

// Pagrindinė vektoriaus programos funkcija
void Vec_programa() {
    vector<Studentas> studentai;
    int pasirinkimas;
    int failoPasirinkimas;
    int studentuKiekis;
    bool gerasPasirinkimas = false;
    
    // Meniu
    cout << "1. Ivesti duomenis ranka\n";
    cout << "2. Automatiskai generuoti duomenis\n";
    cout << "3. Nuskaityti duomenis is failo\n";
    cout << "4. Sukurti atsitiktiniu studentu failus\n";
    cout << "5. Suskaiciuoti rezultatus\n";
    cout << "6. Padalinti rezultatu faila i islaikius ir neislaikius\n";
    cout << "7. Sugeneruoti 5 atsitiktinius failus\n";
    cout << "8. Vykdyti visus zingsnius visiems studentu kiekiams\n";
    cout << "Jusu pasirinkimas: ";
    
    // Vartotojo pasirinkimo tikrinimas
    while (!gerasPasirinkimas) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Iveskite pasirinkima (1-8): ";
        cin >> pasirinkimas;

        if (cin.fail() || pasirinkimas < 1 || pasirinkimas > 8) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neteisingas pasirinkimas. Prasome ivesti skaiciu nuo 1 iki 8.\n";
        } else {
            gerasPasirinkimas = true;
        }
    }

    try {
        long long trukmeSkaitymo = 0, trukmeVidurkio = 0, trukmeIrasymo = 0;
        switch (pasirinkimas) {
            case 1: {
                // Duomenų įvedimas ranka
                cout << "Kiek studentu norite irasyti? ";
                bool gerasPasirinkimas = false;

                while (!gerasPasirinkimas) {
                    cin >> studentuKiekis;
                    if (cin.fail() || studentuKiekis < 1) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Klaida: Ivestas neteisingas studentu skaicius. Prasome ivesti skaiciu didesni uz 0: ";
                    } else {
                        gerasPasirinkimas = true;
                    }
                }

                studentai.resize(studentuKiekis);
                for (Studentas& studentas : studentai) {
                    ivestiStudentoDuomenis(studentas);
                    // Spausdinama vektoriaus vieta atmintyje
                    cout << "Studento vektoriaus objektas atmintyje saugomas adresu: " << &studentas << endl;
                }
                break;
            }

            case 2: {
                // Automatinis duomenų generavimas
                cout << "Kiek studentu norite sugeneruoti? ";
                bool gerasPasirinkimas = false;

                while (!gerasPasirinkimas) {
                    cin >> studentuKiekis;
                    if (cin.fail() || studentuKiekis < 1) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Klaida: Ivestas neteisingas studentu skaicius. Prasome ivesti skaiciu didesni uz 0: ";
                    } else {
                        gerasPasirinkimas = true;
                    }
                }

                for (int i = 0; i < studentuKiekis; i++) {
                    studentai.push_back(generuotiAtsitiktiniStudenta());
                }
                break;
            }

            case 3: {
                // Duomenų nuskaitymas iš failo
                cout << "Pasirinkite faila (1. studentai10.txt, 2. studentai100.txt, 3. studentai10000.txt, 4. studentai100000.txt, 5. studentai1000000.txt, 6. studentai10_blog.txt, 7. tuscias.txt): ";
                bool gerasPasirinkimas = false;

                while (!gerasPasirinkimas) {
                    cin >> failoPasirinkimas;
                    if (cin.fail() || failoPasirinkimas < 1 || failoPasirinkimas > 7) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Neteisingas pasirinkimas. Prasome ivesti skaiciu nuo 1 iki 7: ";
                    } else {
                        gerasPasirinkimas = true;
                    }
                }

                string failoPavadinimas;
                switch (failoPasirinkimas) {
                    case 1: failoPavadinimas = "txt_failai/studentai10.txt"; break;
                    case 2: failoPavadinimas = "txt_failai/studentai100.txt"; break;
                    case 3: failoPavadinimas = "txt_failai/studentai10000.txt"; break;
                    case 4: failoPavadinimas = "txt_failai/studentai100000.txt"; break;
                    case 5: failoPavadinimas = "txt_failai/studentai1000000.txt"; break;
                    case 6: failoPavadinimas = "txt_failai/studentai10_blog.txt"; break;
                    case 7: failoPavadinimas = "txt_failai/tuscias.txt"; break;
                }

                skaitytiDuomenisIsFailo(failoPavadinimas, studentai, trukmeSkaitymo, trukmeVidurkio);
                cout << "Duomenys nuskaityti is " << failoPavadinimas << " per " << trukmeSkaitymo << " ms\n";
                break;
            }

            case 4: {
                // Atsitiktinių studentų failų kūrimas
                generuotiFaila();
                return;
            }   
            case 5: {
                // Skaičiuoti rezultatus
                vector<string> studentuSkaicius = {"_1000", "_10000", "_100000", "_1000000", "_10000000", "1000", "10000", "100000", "1000000", "10000000"};
                cout << "Pasirinkite rezultatu faila:\n";
                cout << "Kodo generuoti duomenys\n1. studentai_1000.txt\n2. studentai_10000.txt\n3. studentai_100000.txt\n4. studentai_1000000.txt\n5. studentai_10000000.txt\n";
                cout << "Pavyzdiniai duomenys\n6. studentai1000.txt\n7. studentai10000.txt\n8. studentai100000.txt\n9. studentai1000000.txt\n10. studentai10000000.txt\n";
                

                int failoPasirinkimas;
                cout << "Jusu pasirinkimas: ";
                cin >> failoPasirinkimas;
                if (failoPasirinkimas < 1 || failoPasirinkimas > 10) {
                    throw runtime_error("Neteisingas failo pasirinkimas.");
                }

                string duomenuFailas = "txt_failai/studentai" + (studentuSkaicius[failoPasirinkimas - 1]) + ".txt";
                string isvestiesFailoPavadinimas = "txt_failai/rezultatai" + (studentuSkaicius[failoPasirinkimas - 1]) + ".txt";


                skaitytiIrIsvestiDuomenis(duomenuFailas, isvestiesFailoPavadinimas, trukmeSkaitymo, trukmeVidurkio, trukmeIrasymo);
                cout << "Duomenys nuskaityti is " << duomenuFailas << " per " << trukmeSkaitymo << "ms ir isvesti i " << isvestiesFailoPavadinimas << " per " << trukmeIrasymo << " ms.\n";
                return;
            }

            case 6: {
                // Rūšiuoti į išlaikiusius ir neišlaikiusius
                vector<string> studentuSkaicius = {"_1000", "_10000", "_100000", "_1000000", "_10000000", "1000", "10000", "100000", "1000000", "10000000"};
                cout << "Pasirinkite rezultatu faila:\n";
                cout << "Kodo generuoti duomenys\n1. rezultatai_1000.txt\n2. rezultatai_10000.txt\n3. rezultatai_100000.txt\n4. rezultatai_1000000.txt\n5. rezultatai_10000000.txt\n";
                cout << "Pavyzdiniai duomenys\n6. rezultatai1000.txt\n7. rezultatai10000.txt\n8. rezultatai100000.txt\n9. rezultatai1000000.txt\n10. rezultatai10000000.txt\n";
                

                int failoPasirinkimas;
                cout << "Jusu pasirinkimas: ";
                cin >> failoPasirinkimas;
                if (failoPasirinkimas < 1 || failoPasirinkimas > 10) {
                    throw runtime_error("Neteisingas failo pasirinkimas.");
                }

                string duomenuFailas = "txt_failai/rezultatai" + (studentuSkaicius[failoPasirinkimas - 1]) + ".txt";
                string islaikiusiuFailoPavadinimas = "txt_failai/rezultatai" + (studentuSkaicius[failoPasirinkimas - 1]) + "_islaike.txt";
                string neislaikiusiuFailoPavadinimas = "txt_failai/rezultatai" + (studentuSkaicius[failoPasirinkimas - 1]) + "_neislaike.txt";

                long long trukmeRezultatuSkaitymo, trukmeRezultatuSkaidymas, trukmeSkaidymoIrasymas;
                padalintiRezultatuFaila(duomenuFailas, islaikiusiuFailoPavadinimas, neislaikiusiuFailoPavadinimas, trukmeRezultatuSkaitymo, trukmeRezultatuSkaidymas, trukmeSkaidymoIrasymas);
                cout << "Rezultatu failas padalintas i " << islaikiusiuFailoPavadinimas << " ir " << neislaikiusiuFailoPavadinimas << '\n';
                return;
            }

            case 7: {
                // Generuoti 5 atsitiktinio dydžio studentų failus
                generuotiAtsitiktiniusFailus();
                return;
            }

            case 8: {
                // Kelius kartus sukamas kodas, kad sužinoti kiek laiko užtrunka kodas
                int kartai;
                bool validInput = false;
                
                while (!validInput) {
                    cout << "Kiek kartu norite paleisti funkcija 'vykdytiVisusZingsnius'? ";
                    cin >> kartai;
                    
                    if (cin.fail() || kartai <= 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Neteisingas skaicius. Prasome ivesti teigiama skaiciu.\n";
                    } else {
                        validInput = true;
                    }
                }

                for (int i = 0; i < kartai; i++) {
                    cout << "Vykdoma " << i + 1 << " karta:\n";
                    vykdytiVisusZingsnius();
                }

                return;
            }  
        }

        if (studentai.empty()) {
            throw runtime_error("Nera studentu duomenu.");
        }

        int pasirinkimas;
        cout << "Jeigu norite rusiuoti pagal varda - rasykite 1, jeigu pagal pavarde - 2: ";
        cin >> pasirinkimas;

        // Rūšiuoja studentus
        if (pasirinkimas == 1){
            rusiuotiStudentusPagalVarda(studentai);
        }
        else if (pasirinkimas == 2) {
            rusiuotiStudentusPagalPavarde(studentai);
        }
        else {
            cout << "Blogas pasirinkimas, rusiuojama pagal varda.\n";
            rusiuotiStudentusPagalVarda(studentai);
        }

        // Spausdina rezultatus
        cout << left << setw(16) << "Pavarde" << setw(16) << "Vardas" << setw(25) << "Galutinis Vidurkis" << " / " << "Galutine Mediana\n";
        cout << "-------------------------------------------------------------------------\n";
        cout << fixed << setprecision(2);

        for (const Studentas& studentas : studentai) {
            cout << left << setw(16) << studentas.pavarde 
                << setw(16) << studentas.vardas 
                << setw(25) << studentas.galutinisVidurkis 
                << "   " << studentas.galutineMediana << '\n';
        }
    } catch (const exception& e) {
        cout << "Ivyko klaida: " << e.what() << '\n';
    }
}
