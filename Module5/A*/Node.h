//  Actividad 3.2 - Implementación de "Dijkstra" y "Floyd"
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 06/10/2022
//  Node.h

#pragma once
#include <vector>
#include <string>
using namespace std;

class Node
{
public:
    int x, y;
    // Node *prev;
	Node* parent;

	int number; // optional row, col
	float f; 	// g + h
	float g;	// g(n) = parent->g + hCost or parent->g +dCost
	float h;	// euclidean distance to goal
	vector<Node*> neighbors; // exclude walls and out-of-the-board cells
    Node(int _number);
};