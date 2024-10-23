#include "Vec_funkcijos.h"
#include "List_funkcijos.h"

int main() {
    char pabaiga = 'N';
    char vec_li;

    do {
        // Vartotojas įveda konteinerio tipą (vektorius arba sąrašas)
        do {
            cout << "Ar norite naudoti Vector ar List? Jeigu Vector - rasykite V, jeigu List - rasykite L: ";
            cin >> vec_li;
            vec_li = toupper(vec_li);

            if (vec_li != 'V' && vec_li != 'L') {
                cout << "Neteisingas pasirinkimas. Prasome ivesti V arba L: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (vec_li != 'V' && vec_li != 'L');

        // Vykdyti atitinkamą funkciją pagal naudotojo įvestį
        if (vec_li == 'V') {
            Vec_programa();
        } else {
            List_programa();
        }

        // Vartotojo įvestis programos užbaigimui
        do {
            cout << "Ar norite uzdaryti programa? Jeigu taip - rasykite T, jeigu ne - rasykite N: ";
            cin >> pabaiga;
            pabaiga = toupper(pabaiga);

            if (pabaiga != 'T' && pabaiga != 'N') {
                cout << "Neteisingas pasirinkimas. Prasome ivesti T arba N: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (pabaiga != 'T' && pabaiga != 'N');

        cout << "\n";

    } while (pabaiga != 'T');

    return 0;
}
