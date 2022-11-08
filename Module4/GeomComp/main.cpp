//  Actividad 4.3
//  Implementación búsqueda geométrica
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 07/11/2022

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Buscar.hpp"

using namespace std;

int main() {
    cout << "4.3 - Implementación búsqueda geométrica" << endl << "\nDame N:\n";
    int n; cin >> n;
    
    Buscar p;
    vector<Punto> puntos;
    
    while (n--) {
        string xStr, yStr; cin >> xStr >> yStr;
        xStr.pop_back();
        float x = stof(xStr);
        float y = stof(yStr);
        puntos.push_back(Punto(x, y));
    }
    
    float answer = p.calculaDistMinima(puntos);
    cout << "\nLa distancia mas corta es: " << answer << endl << endl;
    
}


/*
6
2.0, 3.0
12.2, 30.1
40.23, 50.98
5.0, 1.0
12.0, 10.0
3.0, 4.0
 
La distancia mas corta es: 1.41421
*/
