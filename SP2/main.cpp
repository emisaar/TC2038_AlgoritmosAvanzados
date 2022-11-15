//  Actividad Integradora 2
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 17/11/2022

#include "Graph.hpp"
#include "GSearch.hpp"
#include "DisjointSets.hpp"
#include <fstream>
#include <iostream>
using namespace std;

//Usaremos variables globales
vector<vector<int>> matDistances, matMaxFlows;
vector<pair<float, float>> coordenates;


// ============================================================= LECTURA DE ARCHIVO
/*
 Lectura de un archivo de entrada que contiene la información de un grafo
 representado en forma de una matriz de adyacencias con grafos ponderados.
 Entrada:
    a) Un numero entero N que representa el número de colonias en la ciudad
    b) Matriz cuadrada de N x N que representa el grafo con las distancias
       en kilómetros entre las colonias de la ciudad
    c) Matriz cuadrada de N x N que representa las capacidades máximas de
       flujo de datos entre colonia i y colonia j
    d) Lista de N pares ordenados de la forma (A,B) que representan la
       ubicación en un plano coordenado de las centrales
 */
// ============================================================= PROTOTIPOS DE FUNCIONES ADICIONALES
void readFile(string s);
void info2program(vector<string> data);
vector<vector<int>> createMatrix(vector<string> vec, int start, int end);
vector<pair<float, float>> readCoordenates(vector<string> vec, int start);
void printVec2d(vector<vector<int>> mat);
void printCoord(vector<pair<int, int>> vec);





// ============================================================= FUNCIÓN PRINCIPAL
int main() {
    //Cambiar nombre de la ruta!!!
    readFile("CasoPrueba.txt");
    
    //1) Forma de cablear las colonias con fibra. (lista de arcos de la forma (A,B))
    cout << "===================================== PREGUNTA 1: CABLEADO\n";
    Graph* g = new Graph(matDistances);
    cout << "\tFloyd-Warshall:\n";
    g->FloydWarshall();
    cout << "\tKruskal:\n";
    g->runKruskal();
    
    
    //2) Ruta a seguir por el personal que reparte correspondencia
    cout << "\n===================================== PREGUNTA 2: MEJOR RUTA\n";
    
    //3) Valor de flujo máximo de información del nodo inicial al nodo final
    Graph* g2 = new Graph(matMaxFlows);
    cout << "\n===================================== PREGUNTA 3: FLUJO MÁXIMO\n\tFlujo Máximo de Información: "
    << g2->runFordFulkerson(1, (int)matDistances.size()) << endl;;
    
    
    //4) Lista de polígonos (cada elemento es una lista de puntos de la forma (x,y))
    cout << "\n===================================== PREGUNTA 4: LISTA DE SUCURSALES\n";
    GSearch search;
    vector<Point> vp;
    for (pair<float, float> p : coordenates){
        vp.push_back(Point(p.first, p.second));
    }
    cout << "\tDame la nueva coordenada de la sucursal: ";
    int x, y; cin >> x >> y;
    vp.push_back(Point(x, y));
    cout << search.calculaDistMinima(vp) << endl;
}



// ============================================================= FUNCIONES AUXILIARES
//Función para abrir el archivo
void readFile(string s){
    ifstream lector(s);
    //No se pudo leer/abrir el archivo
    if (lector.fail()){
        cout << "\nError en la carga del archivo" << endl;
        exit(1);
    }
    string line;
    vector<string> DataArray;
    while (getline(lector, line)){
        //NO líneas en blanco
        if (line.size() != 0){
            DataArray.push_back(line);
        }
    }
    info2program(DataArray);
}


void info2program(vector<string> data){
    //Número de colonias
    int num_nodes = stoi(data[0]);
    
    //Distancias en kilómetros entre las colonias de la ciudad
    matDistances = createMatrix(data, 1, num_nodes + 1);
    
    //Capacidades máximas de flujo de datos entre colonia i y colonia j
    matMaxFlows = createMatrix(data, num_nodes + 1, 2 * num_nodes + 1);
    
    //Ubicación en un plano coordenado de las centrales
    coordenates = readCoordenates(data, 2 * num_nodes + 1);
}


vector<vector<int>> createMatrix(vector<string> vec, int start, int end){
    vector<vector<int>> mat2d;
    
    vector<string>::iterator vs;
    for (vs = vec.begin() + start; vs != vec.begin() + end; ++vs){
        string words = *vs, str = "";
        vector<int> nums;
        for (int i = 0; i < words.size(); i++){
            if (i == words.size() - 1){
                str += words[i];
                int num = stoi(str);
                nums.push_back(num);
            }
            else if (words[i] == ' '){
                int num = stoi(str);
                nums.push_back(num);
                str = "";
            }
            else str += words[i];
        }
        mat2d.push_back(nums);
    }
    return mat2d;
}

vector<pair<float, float>> readCoordenates(vector<string> vec, int start){
    vector<pair<float, float>> vecCoord;
    
    vector<string>::iterator vs;
    for (vs = vec.begin() + start; vs != vec.end(); ++vs){
        string words = *vs, str = "";
        pair<int, int> coords;
        for (int i = 1; i < words.size(); i++){
            if (words[i] == ','){
                float num = stof(str);
                coords.first = num;
                str = "";
            }
            else if (words[i] == ')'){
                float num = stof(str);
                coords.second = num;
                str = "";
            }
            else str += words[i];
        }
        vecCoord.push_back(coords);
    }
    return vecCoord;
}



void printVec2d(vector<vector<int>> mat){
    for (int i = 0; i < mat.size(); i++){
        for (int j = 0; j < mat.size(); j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void printCoord(vector<pair<int, int>> vec){
    for (pair<int, int> p : vec){
        cout << p.first << " " << p.second << endl;
    }
}



