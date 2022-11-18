//  Actividad Integradora 2
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 17/11/2022

#include "Graph.hpp"
#include "DisjointSets.hpp"
#include <limits.h>

#define INFINITO INT_MAX

//----------------------------------------------------------------------------------------------CONSTRUCTORES
//Complejidad --> O(n^2)
Graph::Graph(vector<vector<int>> matDists){
    int numNodos = (int)matDists.size();
    vector<Node*> _nodes;
    vector<Edge*> _edges;
    
    //Creamos los nodos
    for (int i = 1; i <= numNodos; i++){
        Node* n = new Node(i);
        _nodes.push_back(n);
    }
    
    //Creamos las aristas
    for (int i = 0; i < numNodos; i++){
        for (int j = 0; j < numNodos; j++){
            //Significa que es el mismo nodo, o bien, no hay arista entre ambos nodos
            if (matDists[i][j] == 0 or matDists[i][j] == -1)
                continue;
            
            //Caso contrario, agregamos la arista al vector de Edges*
            _edges.push_back(new Edge(_nodes[i], _nodes[j], matDists[i][j]));
        }
    }
    nodes = _nodes;
    edges = _edges;
}

//Complejidad --> O(1)
Graph::Graph(vector<Node*> _nodes, vector<Edge*> _edges){
    nodes = _nodes;
    edges = _edges;
}


//----------------------------------------------------------------------------------------------PREGUNTA 1


//----------------------------------------------------------------------------------------------PREGUNTA 2

//----------------------------------------------------------------------------------------------PREGUNTA 3

//----------------------------------------------------------------------------------------------PREGUNTA 4


//----------------------------------------------------------------------------------------------DIJKSTRA
//FUNCIÓN DIJKSTRA: Hace el recorrido de Dijkstra para todos los nodos
//Complejidad --> O(n^3)
void Graph::Dijkstra(){
    cout << "\n############ RUNNING DIJKSTRA ############" << endl;
    //Complejidad --> O(n)
    for (Node* n : nodes){
        //Complejidad --> O(n^2)
        runDijkstra(n);
        //Complejidad --> O(n)
        printDijkstra(n);
    }
}

//FUNCIÓN DIJKSTRA: Hacemos el recorrido Dijkstra en un nodo
//Complejidad --> O(n^2)
void Graph::runDijkstra(Node* source){
    vector<Node*> Q = nodes;
    
    //Inicializamos los valores de cada nodo para realizar el recorrido
    //Complejidad --> O(n)
    for (Node* q : Q){
        q->distance = 1000;
        q->prev = nullptr;
    }
    
    //La distancia del nodo en donde inicia el recorrido es 0
    source->distance = 0;
    
    //Complejidad --> O(n)
    while (!Q.empty()) {
        Node* u = getMinDist(Q);
        remove(Q, u);
        
        vector<Node*> neighbors = getNeighbors(Q, u);
        //Complejidad --> O(n)
        for (Node* v : neighbors){
            int alt = u->distance + getLength(u, v);
            if (alt < v->distance){
                v->distance = alt;
                v->prev = u;
            }
        }
    }
}

//FUNCIÓN PRINT: Imprimimos el grafo según el recorrido de Dijkstra
//Complejidad --> O(n)
void Graph::printDijkstra(Node* source){
    for (Node* n : nodes){
        if (n->number == source->number) continue;
        cout << "\tnode " << source->number << " to node " << n->number << " : " << n->distance << endl;
    }
    //cout << endl;
}


//FUNCIÓN NEIGHBORS: Obtenemos un vector de nodos vecinos de n
//Complejidad --> O(n*e)
vector<Node*> Graph::getNeighbors(vector<Node*> Q, Node* n){
    vector<Node*> nodos;
    for (Node* q : Q){
        for (Edge* e : edges){
            if (e->first == n and e->second == q)
                nodos.push_back(e->second);
            /* Funcionalidad para grafo NO dirigido
            else if (e->second == n and e->first == q)
                nodos.push_back(e->first);
             */
        }
    }
    return nodos;
}


//FUNCIÓN MIN-DISTANCE: Devolvemos el nodo con menor distancia
//Complejidad --> O(n)
Node* Graph::getMinDist (vector<Node*> qs){
    Node* u = new Node(100);
    for (Node* q : qs){
        if (q->distance < u->distance)
            u = q;
    }
    return u;
}

//FUNCIÓN REMOVE: Eliminamos el nodo (del vector) con menor distancia
//Complejidad --> O(n)
void Graph::remove(vector<Node*> &qs, Node* q){
    int index = 0;
    for (Node* n : qs){
        if (n == q) break;
        index++;
    }
    qs.erase(qs.begin() + index);
}

//GETTER COST: Obtenemos el costo de la arista de 2 nodos
//Complejidad --> O(e)
int Graph::getLength(Node* u, Node* v){
    for (Edge* e : edges){
        if (e->first == u and e->second == v)
            return e->weight;
        /* Funcionalidad para grafo NO dirigido
        if (e->first == v and e->second == u)
            return e->weight;
         */
    }
    return -1000;
}


//----------------------------------------------------------------------------------------------FLOYD-WARSHALL
//FUNCIÓN FLOYD-WARSHALL: Calcula el camino más corto con el algoritmo Floyd-Warshall
//Complejidad --> O(n^3)
void Graph::FloydWarshall(){
    //Preparamos la matriz
    vector<vector<int>> dist;
    int v = (int)nodes.size();
    
    //Complejidad --> O(n)
    for (int i = 0; i < v; i++){
        vector<int> row(v, INFINITO);
        row[i] = 0; //La diagonal queda en 0
        dist.push_back(row);
    }
    
    //Inicializamos los valores correspondientes a los edges existentes
    //Complejidad --> O(e)
    for (Edge* e : edges){
        dist[e->first->number - 1][e->second->number - 1] = e->weight;
    }
    
    //Crearemos v matrices para calcular el resultado
    //Además necesitamos 2 ciclos adicionales para iterar la matriz
    //Complejidad --> O(n^3)
    for (int k = 0; k < v; k++){
        for (int i = 0; i < v; i++){
            for (int j = 0; j < v; j++){
                if (dist[i][k] != INFINITO && dist[k][j] != INFINITO &&
                    dist[i][k] + dist[k][j] < dist[i][j] )
                 dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    
    //Impresión del resultado
    //Complejidad --> O(n^2)
    for (int i = 0; i < v; i++){
        for (int j = 0; j < v; j++){
            if (dist[i][j] == INFINITO or dist[i][j] == 0) continue;
            else cout << "\tArco: (" << to_string(i + 1) << ", " << to_string(j + 1) << ")\t\tDistancia: " << dist[i][j] << "\tKm\n";
        }
    }
    cout << endl;
}





//----------------------------------------------------------------------------------------------FORD-FULKERSON
//FUNCIÓN FORD-FULKERSON: Calcula el flujo máximo en un grafo
//Complejidad --> O(n^3 * m)
int Graph::runFordFulkerson(int source, int sink) {
    Node* s = findNode(source);
    Node* t = findNode(sink);
    
    if (s == nullptr || t == nullptr) return -100000;
    
    int maxFlow = 0;
    for (Edge* e : edges) {
        // Actualizar el flujo (flow) de cada arco con el valor de capacidad (weight) del mismo
        e->flow = e->weight;
        while(bfs(s, t)) {
            int pathFlow = INT_MAX;
            // Nodo temporal para recorrer el path
            Node *curr = t;
            while (curr != s) {
                // Obtener la arista que conecta el nodo previo con el nodo actual
                Edge *e = findEdge(curr->prev, curr);
                // Encontrar el flujo mínimo
                pathFlow = min(pathFlow, e->flow);
                curr = curr->prev;
            }
            // Se realiza el camino inverso para actualizar los flujos
            curr = t;
            // Mientras el nodo actual no sea el nodo s
            while(curr != s) {
                // Buscar arista que conecta el nodo previo con el nodo actual para actualizar el flujo
                Edge *e1 = findEdge(curr->prev, curr);
                e1->flow -= pathFlow;

                // Buscar arista que conecta el nodo actual con el nodo previo para actualizar el flujo
                Edge *e2 = findEdge(curr, curr->prev);
                if (e2 != nullptr) e2->flow += pathFlow;
                curr = curr->prev;
            }
            // Actualizar el flujo máximo
            maxFlow += pathFlow;
        }
    }
    return maxFlow;
}

//FUNCIÓN FIND-NODE: Busca a un nodo que tenga como atributo number el entero recibido
//Complejidad --> O(n)
Node* Graph::findNode(int node){
    for (Node* n : nodes){
        if (n->number == node)
            return n;
    }
    return nullptr;
}

Node* Graph::getStartNode(){
    return nodes[0];
}

//FUNCIÓN FIND-EDGE: Busca la arista que conecta a los nodos "u" y "v"
//Complejidad --> O(n)
Edge* Graph::findEdge(Node *u, Node *v) {
    Edge *e = nullptr;
    for (Edge* e : edges) {
        if (e->first == u && e->second == v)
            return e;
    }
    return e;
}

Edge *Graph::findEdge2(int u, int v) {
    return findEdge(findNode(u), findNode(v));
}

//FUNCIÓN BFS: Función que hace el recorrido en anchura en un grafo
//Complejidad --> O(n^2)
bool Graph::bfs(Node *s, Node *t) {
    for (Node* n : nodes) {
        n->visited = false;
    }
    vector<Node*> q;
    q.push_back(s);
    s->prev = nullptr;
    s->visited = true;

    while(q.size() > 0) {
        Node *u = q[0];
        remove(q, u);
       for (Node* v : getNeighbors2(u)) {
           Edge *e = findEdge(u, v);
           if(e != nullptr){
               if(!v->visited && e->flow > 0) {
                   q.push_back(v);
                   v->prev = u;
                   v->visited = true;
               }
           }
       }
    }
    // Regresar si el nodo sink (t) ha sido visitado
    return t->visited == true;
}

vector<Node*> Graph::getNeighbors2(Node *n){
    vector<Node*> neighbors;
    vector<Edge*>::iterator ei;
    for(ei = edges.begin(); ei != edges.end(); ++ei) {
        if((*ei)->first == n) {
            neighbors.push_back((*ei)->second);
        }
    }
    return neighbors;
}



//----------------------------------------------------------------------------------------------KNAPSACK PROBLEM
//FUNCIÓN FIND-PATHS: Función que resuelve "The Knapsack Problem" con grafos
//Complejidad --> O(n^3 * m)
void Graph::findPaths(Node *s, Node *t, vector<int> &weights, vector<int> &values) {
    Node* source = s;
    int pathFlow = INT_MAX;
    vector<Edge*>::iterator ei;
    for(ei = edges.begin(); ei != edges.end(); ++ei) {
        (*ei)->flow = (*ei)->weight;
    }
    
    while(bfs(s, t)) {
        // cout << "inside while" << endl;
        int pathTotalWeight = 0;
        int pathTotalValue = 0;
        Node *curr = t;
        while (curr != s) {
            if(curr != t) pathTotalValue += curr->number;
            Edge *e1 = findEdge(curr->prev, curr);
            pathTotalWeight += e1->weight;
            pathFlow = min(pathFlow, e1->flow);
            curr = curr->prev;
        }

        pathTotalValue += curr->number;
        weights.push_back(pathTotalWeight);
        values.push_back(pathTotalValue);
        curr = t;
        while(curr != s) {
            Edge *e1 = findEdge(curr->prev, curr);
            e1->flow -= pathFlow;
            Edge *e2 = findEdge(curr, curr->prev);
            if (e2 != nullptr) e2->flow += pathFlow;
            curr = curr->prev;
        }
    }
}

//FUNCIÓN PRINT-GRAPH: Función que imprime las aristas (y su costo) de un grafo
//Complejidad --> O(n)
void Graph::printGraph(){
    vector<Edge*>::iterator ei;
    for(ei = edges.begin(); ei != edges.end(); ++ei) {
        cout << (*ei)->first->number << " -> " << (*ei)->second->number << " : " << (*ei)->weight << endl;
    }       
}

//----------------------------------------------------------------------------------------------KRUSKAL'S ALGORITHM

// FUNCIÓN COMPAREWEIGHT: Función para comparar los pesos de dos aristas
// Complejidad --> O(1)
bool Graph::compareWeight(Edge* a, Edge* b){
    return a->weight < b->weight;
}

// FUNCIÓN KRUSKAL: Función para encontrar el árbol de expansión mínima
// Compljidad --> O(n^2 * m)
void Graph::runKruskal() {

    DisjointSets ds;
    // F = {}
    vector<Edge*> F;
    vector<Edge*>::iterator ei;
    // For each vertex v in G.V do MAKE-SET(v) 
    for(ei = edges.begin(); ei != edges.end(); ++ei) {
        ds.makeSet((*ei)->first);
        ds.makeSet((*ei)->second);
    }

    // sort the edges of G.E by weight
    sort(edges.begin(), edges.end(), compareWeight);

    // For each edge (u, v) in G.E
    for(ei = edges.begin(); ei != edges.end(); ++ei) {
        vector<Node*> set1 = ds.findSet((*ei)->first);
        vector<Node*> set2 = ds.findSet((*ei)->second);
        // If FIND-SET(u) != FIND-SET(v)
        if(set1 != set2) {
            // F = F U {(u, v)} U {(v, u)}
            F.push_back((*ei));
            ds.do_union(set1, set2);
        }
    }

    // Return F
    cout << "\t\tMST: " << endl;
    vector<Edge*>::iterator ki;
    for(ki = F.begin(); ki != F.end(); ++ki) {
        cout << "\t\tArco: " <<(*ki)->first->number << " -> " << (*ki)->second->number << ": " << (*ki)->weight << endl;
    }

}