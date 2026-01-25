#include <iostream>
using namespace std;

/*
    CONSTANTE GLOBALE
    -----------------
    Folosim constante pentru a evita numerele „magice”
    și pentru a putea modifica ușor programul.
*/

// Lungimea maximă a unui cuvânt (nume, prenume, localitate etc.)
// 50 caractere + 1 pentru caracterul '\0'
const int LUNGIME_MAX_CUV = 51;

// Numărul maxim de angajați
const int LUNGIME_MAX_ANGAJATI = 100;

/*
    STRUCTURA PENTRU DATA
    --------------------
    Grupăm anul, luna și ziua într-o singură structură
    pentru claritate și organizare.
*/
struct custom_data {
    int an;    // anul
    int luna;  // luna
    int zi;    // ziua
};

/*
    STRUCTURA PENTRU STUDII MEDII
    -----------------------------
    Se folosește DOAR dacă angajatul are studii 'm'
*/
struct studiiMedii {
    int anAbsolvire;  // anul absolvirii liceului
    char localitateAbsolvire[LUNGIME_MAX_CUV]; // orașul absolvirii
};

/*
    STRUCTURA PENTRU STUDII SUPERIOARE
    ---------------------------------
    Se folosește DOAR dacă angajatul are studii 's'
*/
struct studiiSuperioare {
    int anAbsolvire; // anul absolvirii facultății
    char facultate[LUNGIME_MAX_CUV]; // numele facultății
    char localitateAbsolvire[LUNGIME_MAX_CUV]; // orașul absolvirii
};

/*
    STRUCTURA PRINCIPALĂ - ANGAJAT
    ------------------------------
    Conține toate informațiile despre un angajat
*/
struct angajat {
    char nume[LUNGIME_MAX_CUV];     // numele angajatului
    char prenume[LUNGIME_MAX_CUV];  // prenumele angajatului

    custom_data data; // data angajării

    char studii;
    /*
        'f' - fără studii
        'm' - studii medii
        's' - studii superioare
    */

    // Structuri auxiliare pentru studii
    // Vor fi folosite în funcție de tipul de studii
    studiiMedii sm;
    studiiSuperioare ss;
};

/*
    FUNCȚIA DE CITIRE A ANGAJAȚILOR
    ------------------------------
    - citește numărul de angajați
    - citește datele fiecăruia
    - citește informații diferite în funcție de studii
*/
void read_angajati(angajat ang[], int& nrAngajati) {

    cin >> nrAngajati;
    cin.ignore(); // eliminăm '\n' din buffer

    for (int i = 0; i < nrAngajati; i++) {

        cout << "Angajat " << i + 1 << "\n";

        // Citire nume
        cout << "Nume: ";
        cin.getline(ang[i].nume, LUNGIME_MAX_CUV);

        // Citire prenume
        cout << "Prenume: ";
        cin.getline(ang[i].prenume, LUNGIME_MAX_CUV);

        // Citire data angajării
        cout << "Data angajarii (an luna zi): ";
        cin >> ang[i].data.an >> ang[i].data.luna >> ang[i].data.zi;

        // Citire tip studii
        cout << "Tip studii (f/m/s): ";
        cin >> ang[i].studii;
        cin.ignore();

        // Dacă are studii medii
        if (ang[i].studii == 'm') {

            cout << "An absolvire liceu: ";
            cin >> ang[i].sm.anAbsolvire;
            cin.ignore();

            cout << "Localitate absolvire: ";
            cin.getline(ang[i].sm.localitateAbsolvire, LUNGIME_MAX_CUV);
        }
        // Dacă are studii superioare
        else if (ang[i].studii == 's') {

            cout << "An absolvire facultate: ";
            cin >> ang[i].ss.anAbsolvire;
            cin.ignore();

            cout << "Facultate: ";
            cin.getline(ang[i].ss.facultate, LUNGIME_MAX_CUV);

            cout << "Localitate absolvire: ";
            cin.getline(ang[i].ss.localitateAbsolvire, LUNGIME_MAX_CUV);
        }

        cout << "\n";
    }
}

/*
    FUNCȚIA DE AFIȘARE
    -----------------
    Afișează angajații în ordinea:
    1. studii superioare
    2. studii medii
    3. fără studii
*/
void print_angajati(const angajat ang[], int nrAngajati) {

    // Ordinea cerută în problemă
    char ordine[3] = { 's', 'm', 'f' };

    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < nrAngajati; i++) {

            if (ang[i].studii == ordine[k]) {

                cout << ang[i].nume << " "
                     << ang[i].prenume << " - ";

                if (ang[i].studii == 's')
                    cout << "Studii superioare\n";
                else if (ang[i].studii == 'm')
                    cout << "Studii medii\n";
                else
                    cout << "Fara studii\n";
            }
        }
    }
}

/*
    FUNCȚIA MAIN
    ------------
    Coordonează programul
*/
int main() {

    angajat angajati[LUNGIME_MAX_ANGAJATI];
    int nrAngajati;

    read_angajati(angajati, nrAngajati);
    print_angajati(angajati, nrAngajati);

    return 0;
}
