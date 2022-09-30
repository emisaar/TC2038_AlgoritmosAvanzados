//  Actividad 3.1 - Implementación de "Tries"
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 26/09/2022
//  main.cpp

/* Instrucciones:
Escribe un programa en C++ que implemente una estructura de datos TRIE.
Escribe también un programa que permita verificar su funcionalidad.
La entrada al programa es un número N, seguido de N palabras, que serán insertadas a la estructura TRIE.
Después se lee un dato M seguido de M palabras a buscar en la estructura TRIE.

La salida del programa es el recorrido DFS del TRIE, seguido de M booleanos correspondientes al resultado 
de buscar cada una de las M palabras en la estructura.

Tu programa debe ser llamado main.cpp y debe compilar utilizando el comando g++ en un ambiente linux.
*/

/* Estructura TRIE (Concepto)
La estructura de datos TRIE resulta ser de gran utilidad cuando se desea implementar diccionarios 
debido a la eficiencia que tiene para la búsqueda de prefijos. Una de sus principales desventajas, 
es que requieren de mucho espacio extra.

Referencias:
https://www.geeksforgeeks.org/overview-of-data-structures-set-3-graph-trie-segment-tree-and-suffix-tree/#code10
https://www.digitalocean.com/community/tutorials/trie-data-structure-in-c-plus-plus
*/

#include "Trie.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int DM;
    int numOfWords, copyNumOfWords, numOfQueries, copyNumOfQueries;
    string word, query;
    vector<string> queryVec;

    cout << "¿Correr pruebas por default (0) o manuales (1)? (Ingrese 0 o 1): ";
    
    cin >> DM;

    while (DM != 0 && DM != 1) {
        cout << "Input incorrecto. Favor de introducir 0 o 1." << endl;
        cout << "¿Correr pruebas por default (0) o manuales (1)? (Ingrese 0 o 1): ";
        cin >> DM;
    }

    if (DM == 0) {
        cout << "-------- Caso 1 --------" << endl;
        Node *r = new Node();
        Trie *t = new Trie(r);
        string a = "aba";
        string b = "abc";
        string c = "abd";
        string d = "ad";
        string e = "bad";
        string f = "bag";
        t->Add(a);
        cout << "'" << a << "'" << " added" << endl;
        t->Add(b);
        cout << "'" << b << "'" << " added" << endl;
        t->Add(c);
        cout << "'" << c << "'" << " added" << endl;
        t->Add(d);
        cout << "'" << d << "'" << " added" << endl;
        t->Add(e);
        cout << "'" << e << "'" << " added" << endl;
        t->Add(f);
        cout << "'" << f << "'" << " added" << endl;

        cout << "\nRecorrido DFS TRIE: ";
        t->Print();   // imprime    a|b|a|c|d|d|b|a|d|g|

        cout << "\nQueries:" << endl;
        cout << "Query('ac'): " << t->Query("ac") << endl;
        cout << "Query('abg'): " << t->Query("abg") << endl;
        cout << "Query('abad'): " << t->Query("abad") << endl;
        cout << "Query('abc'): " << t->Query("abc") << endl;
        cout << "Query('bga'): "<< t->Query("bga") << endl;
        cout << "Query('bag'): " << t->Query("bag") << endl;
    // //////////////////////////////////////////////////////////
        cout << endl;
        cout << "-------- Caso 2 --------" << endl;
        Node* r2 = new Node();
        Trie* t2 = new Trie(r2);
        string test = "test";
        string tear = "tear";
        string team = "team";
        string road = "road";
        t2->Add(test);
        cout << "'" << test << "'" << " added" << endl;
        t2->Add(tear);
        cout << "'" << tear << "'" << " added" << endl;
        t2->Add(team);
        cout << "'" << team << "'" << " added" << endl;
        t2->Add(road);
        cout << "'" << road << "'" << " added" << endl;

        cout << "\nRecorrido DFS TRIE: ";
        t2->Print();  // imprime    r|o|a|d|t|e|a|m|r|s|t|

        cout << "\nQueries:" << endl;
        cout << "Query('dte'): " << t2->Query("dte") << endl;
        cout << "Query('team'): " << t2->Query("team") << endl;
        cout << "Query('rst'): " << t2->Query("rst") << endl;
        cout << "Query('tear'): "<< t2->Query("tear") << endl;
        cout << "Query('st'): " << t2->Query("st") << endl;
    } else {
        cout << "Ingrese el número de palabras a insertar en la estructura TRIE: ";
        cin >> numOfWords;

        while (numOfWords < 0) {
            cout << "Input incorrecto. Favor de introducir un valor mayor a 0." << endl;
            cout << "Ingrese el número de palabras a insertar en la estructura TRIE: ";
            cin >> numOfWords;
        }
        copyNumOfWords = numOfWords - 1;

        Node *root = new Node();
        Trie *trie = new Trie(root);

        for (int i = 0; i < numOfWords; i++){
            cout << "Ingrese las palabras (Nota: Solo se aceptan letras minúsculas): ";
            
            cin >> word;
            trie->Add(word);
            cout << "\t" << word << " added" << endl;

            if (copyNumOfWords != 0){
                cout << "\tFalta(n) " << copyNumOfWords--  << " palabras" << endl;
            }
        }
        
        cout << "\nRecorrido DFS TRIE: ";
        trie->Print();

        cout << "Ingrese el número de queries a realizar: ";
        cin >> numOfQueries;

        while (numOfQueries < 0) {
            cout << "Input incorrecto. Favor de introducir un valor mayor a 0." << endl;
            cout << "Ingrese el número de palabras a insertar en la estructura TRIE: ";
            cin >> numOfQueries;
        }

        copyNumOfQueries = numOfQueries - 1;

        for (int i = 0; i < numOfQueries; i++){
            cout << "Ingrese las palabras a buscar (Nota: Solo se aceptan letras minúsculas): ";
            cin >> query;
            queryVec.push_back(query);
            
            if (copyNumOfQueries != 0){
                cout << "\tFaltan " << copyNumOfQueries--  << " queries" << endl;
            }
        }

        for(int i= 0; i < queryVec.size(); i++){
            cout << "\tQuery('" << queryVec[i] << "'): " << trie->Query(queryVec[i]) << endl;
        }
    }
}
