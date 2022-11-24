//  Actividad Integradora 2
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 17/11/2022

#ifndef GSearch_hpp
#define GSearch_hpp

#include <stdio.h>
#include "Point.hpp"
class GSearch{
public:
    float calculaDistMinima(vector<Point> puntos);
    void calculaDistMinima2(vector<Point> puntos);
};

#endif /* GSearch_hpp */
