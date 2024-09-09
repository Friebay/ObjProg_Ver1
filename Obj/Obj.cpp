#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

struct Duomenys {
    string Vardas, Pavarde;
    int paz[5];
    int egz;
    int paz_suma = 0;
    float vidurkis = 0;
};

int main()
{
    Duomenys stud1, stud2;

    cout << "Vardas: ";
    cin >> stud1.Vardas;

    cout << "Pavarde: ";
    cin >> stud1.Pavarde;

    for (int i = 0; i < 5; i++) {
        cout << "Pazymys: ";
        cin >> stud1.paz[i];

        stud1.paz_suma += stud1.paz[i];
    }

    stud1.vidurkis = float((stud1.paz_suma) / 5);
    cout << stud1.Vardas << " " << stud1.Pavarde << " Vidurkis: " << stud1.vidurkis << endl;

    cout << "Vardas: ";
    cin >> stud2.Vardas;

    cout << "Pavarde: ";
    cin >> stud2.Pavarde;

    for (int i = 0; i < 5; i++) {
        cout << "Pazymys: ";
        cin >> stud2.paz[i];

        stud2.paz_suma += stud2.paz[i];
    }

    stud2.vidurkis = float((stud2.paz_suma) / 5);
    cout << stud2.Vardas << " " << stud2.Pavarde << " Vidurkis: " << stud2.vidurkis << endl;

    return 0;
}