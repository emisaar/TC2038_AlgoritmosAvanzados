//  Actividad Integradora 2
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 17/11/2022

#include "GSearch.hpp"
#include <cmath>
#include <algorithm>

//Complejidad: O(1)
bool sortByX(Point a, Point b){
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

//Complejidad: O(1)
bool sortByY(Point a, Point b){
    if (a.y == b.y)
        return a.x < b.x;
    return a.y < b.y;
}

//FUNCIÓN CALCULA-DISTANCIA-MÍNIMA
//Complejidad: O(n(log n) + (log(n))^2)
// 1) Generar lista de puntos
float GSearch::calculaDistMinima(vector<Point> puntos){
    float minDistLeft = 100000, minDistRight = 100000;
    
    // 2) Ordenar con respecto a "x"
    //Complejidad: O(n*(log n))
    sort(puntos.begin(), puntos.end(), sortByX);
    
    // 3) Dividir por la mitad
    int mitad = int(puntos.size() / 2);
    vector<Point> leftHalf(puntos.begin(), puntos.begin() + mitad);
    vector<Point> rightHalf(puntos.begin() + mitad, puntos.end());
    
    // 4) Todos contra todos
    // 5) Obtener la menor distancia de cada subarreglo
    //Complejidad: O((log(n))^2)
    for (int i = 0; i < leftHalf.size(); i++){
        for (int j = i + 1; j < leftHalf.size(); j++){
            float dist = sqrt(pow(leftHalf[j].x - leftHalf[i].x, 2) + pow(leftHalf[j].y - leftHalf[i].y, 2));
            minDistLeft = min(minDistLeft, dist);
        }
    }
    //Complejidad: O((log(n))^2)
    for (int i = 0; i < rightHalf.size(); i++){
        for (int j = i + 1; j < rightHalf.size(); j++){
            float dist = sqrt(pow(rightHalf[j].x - rightHalf[i].x, 2) + pow(rightHalf[j].y - rightHalf[i].y, 2));
            minDistRight = min(minDistRight, dist);
        }
    }
    
    // 6) Middle X
    Point MiddleX = rightHalf[0];
    
    // 7) Distancia menor de ambas listas
    float minDist = min(minDistLeft, minDistRight);
    
    // 8) MIDD-D
    float midd1 = MiddleX.x - minDist;
    
    // 9) MIDD+D
    float midd2 = MiddleX.x + minDist;
    
    // 10) Puntos dentro de la cinta
    //Complejidad: O(n)
    vector<Point> cinta;
    for (int i = 0; i < puntos.size(); i++){
        if (puntos[i].x >= midd1 && puntos[i].x <= midd2){
            cinta.push_back(puntos[i]);
        }
    }

    // 11) Ordenar los puntos con respecto a Y (menor a mayor)
    //Complejidad: O(n*(log n))
     sort(puntos.begin(), puntos.end(), sortByY);

    // 12) Todos contra todos
    //Complejidad: O(c) --> c < log(n)  --> c = cinta
    float minCinta = minDist;
    for (int i = 0; i < cinta.size(); i++){
        for (int j = i + 1; j < cinta.size(); j++){
            float dist = sqrt(pow(cinta[j].x - cinta[i].x, 2) + pow(cinta[j].y - cinta[i].y, 2));
            minCinta = min(minCinta, dist);
        }
    }
    return min(minCinta, minDist);
}
