//  Actividad 2.2
//  Implementación de "Sufix Array"
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 01/09/2022
//  Referencias:
//  https://cplusplus.com/reference/algorithm/sort/
//  https://softwareengineering.stackexchange.com/questions/258509/algorithms-how-do-i-sum-on-and-onlogn-together


/*
 Escribe un programa en C++ que dado un string, se calcule el arreglo de substrings y
 lo muestre ordenado alfabéticamente
 
 Ejemplo:
         s  =   CABALLO
 
     vector =   (7) O
   ordenado     (6) LO
                (5) LLO
                (2) ALLO
                (3) BALLO
                (1) ABALLO
                (4) CABALLO
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;


void printVector(vector<string> v){                             //Complejidad --> O(n)
    for(int i = 0; i < v.size(); i++)
        cout << i + 1 << ") " << v[i] << endl;
    cout << endl;
}

vector<string> sortedSubstrings(string pattern){             //Complejidad --> O(nlog(n))
    vector<string> res;
    string r;
    //Recorremos el string al revés para obtener los sufijos
    //O(n)
    for (int i = pattern.size() - 1; i >= 0; i--){
        r = pattern[i] + r;
        res.push_back(r);
    }
    //Ordenamos el vector que contiene los sufijos con la función sort
    //O(nlogn)
    sort(res.begin(), res.end());
    return res;
}

int main() {
    string s = "AGUA";
    vector<string> vs = sortedSubstrings(s);
    
    cout << "STRING: " << s << endl << endl;
    cout << "SUBSTRINGS ORDENADOS ALFABETICAMENTE: " << endl;
    printVector(vs);
}
