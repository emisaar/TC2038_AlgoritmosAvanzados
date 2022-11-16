//  Actividad Integradora 2
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 17/11/2022

#include "GSearch.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

//Ordenamos los puntos considerando su posición en el eje "x"
//Complejidad: O(1)
bool sortByX(Point a, Point b){
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

//Ordenamos los puntos considerando su posición en el eje "y"
//Complejidad: O(1)
bool sortByY(Point a, Point b){
    if (a.y == b.y)
        return a.x < b.x;
    return a.y < b.y;
}

//FUNCIÓN CALCULA-DISTANCIA-MÍNIMA: Calcula la menor distancia entre
//todos los puntos
//Complejidad: O(n*log(n) + 2*((n/2)^2) + c*log(c) + c^2)
// 1) Generar lista de puntos
float GSearch::calculaDistMinima(vector<Point> puntos){
    vector<pair<int, float>> id_dist;
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
    //Complejidad: O((n/2)^2)
    for (int i = 0; i < leftHalf.size(); i++){
        for (int j = i + 1; j < leftHalf.size(); j++){
            float dist = sqrt(pow(leftHalf[j].x - leftHalf[i].x, 2) + pow(leftHalf[j].y - leftHalf[i].y, 2));
            minDistLeft = min(minDistLeft, dist);
        }
    }
    //Complejidad: O((n/2)^2)
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
    //Complejidad: O(c*(log c))
     sort(puntos.begin(), puntos.end(), sortByY);

    // 12) Todos contra todos
    //Complejidad: O(c^2)
    float minCinta = minDist;
    for (int i = 0; i < cinta.size(); i++){
        for (int j = i + 1; j < cinta.size(); j++){
            float dist = sqrt(pow(cinta[j].x - cinta[i].x, 2) + pow(cinta[j].y - cinta[i].y, 2));
            minCinta = min(minCinta, dist);
        }
    }
    return min(minCinta, minDist);
}


//Ordenamos los puntos considerando su posición en el eje "x"
//Complejidad: O(1)
bool sortPairByDist(pair<Point, float> a, pair<Point, float> b){
    return a.second < b.second;
}

//FUNCIÓN CALCULA-DISTANCIA-MÍNIMA: Calcula la menor distancia entre
//todos los puntos
//Complejidad: O(n*log(n) + n)
void GSearch::calculaDistMinima2(vector<Point> puntos){
    vector<Point> comp(puntos.begin(), puntos.end() - 1);
    Point casa = puntos[puntos.size() - 1];
    vector<pair<Point, float>> dists;
    
    //Complejidad: O(n)
    for (int i = 0; i < comp.size(); i++){
        float dist = sqrt(pow(comp[i].x - casa.x, 2) + pow(comp[i].y - casa.y, 2));
        dists.push_back({comp[i], dist});
    }
    
    //Complejidad: O(n*log(n))
    sort(puntos.begin(), puntos.end(), sortByX);
    cout << "\tPuntos ordenados de izquierda a derecha: " << endl;
    int index = 1;
    //Complejidad: O(n)
    for (Point p : puntos){
        cout << "\t" << index++ << ".- (" << p.x  << ", " << p.y << ")" << endl;
    }
    cout << endl;
    
    //Complejidad: O(n)
    for (int i = 0; i < comp.size(); i++){
        cout << "\tDistancia de la nueva contratación (" << casa.x << ", " << casa.y << ") a la tienda (" << comp[i].x << ", " << comp[i].y << "): " << dists[i].second << "Km" << endl;
    }
    
    //Complejidad: O(n*log(n))
    sort(dists.begin(), dists.end(), sortPairByDist);
    cout << "\n\tLa central más cercana a la nueva contratación es: (" << dists[0].first.x << ", " << dists[0].first.y << ") con una distancia de " << dists[0].second << "Km" << endl;
}