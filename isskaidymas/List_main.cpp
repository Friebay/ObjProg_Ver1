#include "List_funkcijos.h"
#include "List_failo_apdorojimas.h"

int main() {
   
    char pabaiga = 'N';

    while (toupper(pabaiga) != 'T') { 
        List_programa();

        cout << "Ar norite uzdaryti programa? Jeigu taip - rasykite T, jeigu ne - rasykite N: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cin >> pabaiga; 

        while (toupper(pabaiga) != 'T' && toupper(pabaiga) != 'N') {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Neteisingas pasirinkimas. Prasome ivesti T arba N: ";
            cin >> pabaiga;
        }
    }

    return 0;
}