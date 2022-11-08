//  Actividad 4.3
//  Implementación búsqueda geométrica
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 07/11/2022

#include "Buscar.hpp"
#include <cmath>
#include <algorithm>

//FUNCIÓN CALCULA-DISTANCIA-MÍNIMA
//Complejidad: O(n^2)
float Buscar::calculaDistMinima(vector<Punto> puntos){
    float minDist = 100000;
    
    for (int i = 0; i < puntos.size(); i++){
        for (int j = i + 1; j < puntos.size(); j++){
            float dist = sqrt(pow(puntos[j].x - puntos[i].x, 2) + pow(puntos[j].y - puntos[i].y, 2));
            minDist = min(minDist, dist);
        }
    }
    return minDist;
}
