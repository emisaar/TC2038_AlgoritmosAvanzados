//  Actividad 3.2 - Implementación de "Dijkstra" y "Floyd"
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 06/10/2022
//  Node.h

class Node {
    public:
        int number;
        Node *prev;
        int distance;
        bool visited;

        Node(int _number);
};