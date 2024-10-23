#include "Vec_funkcijos.h"
#include "List_funkcijos.h"

int main() {
   
    char pabaiga = 'N';
    char vec_li;

    while (toupper(pabaiga) != 'T') { 

        cout << "Ar norite naudoti Vector ar List? Jeigu Vector - rasykite V, jeigu List - rasykite L: ";
        cin >> vec_li; 

        while (toupper(vec_li) != 'V' && toupper(vec_li) != 'L') {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Neteisingas pasirinkimas. Prasome ivesti V arba L: ";
            cin >> vec_li;
        }
        if (toupper(vec_li) == 'V'){
            programa();
        }
        else{
            List_programa();
        }
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Ar norite uzdaryti programa? Jeigu taip - rasykite T, jeigu ne - rasykite N: ";
        cin >> pabaiga; 

        while (toupper(pabaiga) != 'T' && toupper(pabaiga) != 'N') {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Neteisingas pasirinkimas. Prasome ivesti T arba N: ";
            cin >> pabaiga;
        }
        cout << "\n";
    }

    return 0;
}