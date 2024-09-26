#include "funkcijos.h"
#include "failo_apdorojimas.h"

int main() {
    inicializuotiAtsitiktinius();
    
    char pabaiga = 'N';

    while (toupper(pabaiga) != 'T') { 
        programa();

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
