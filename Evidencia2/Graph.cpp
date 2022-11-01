//  Actividad 3.2
//  Implementación de "Dijkstra y Floyd"
//
//  Alejandro Díaz Villagómez | A01276769
//
//  Fecha: 06/10/2022
//
//  Referencias:
//  https://www.youtube.com/watch?v=oNI0rf2P9gE
//  https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/

#include "Graph.hpp"

#define INFINITO INT_MAX

//CONSTRUCTOR
//Complejidad --> O(n^2)
Graph::Graph(vector<vector<int>> matGraph){
    int numNodos = (int)matGraph.size();
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
            if (matGraph[i][j] == 0 or matGraph[i][j] == -1)
                continue;
            
            //Caso contrario, agregamos la arista al vector de Edges*
            _edges.push_back(new Edge(_nodes[i], _nodes[j], matGraph[i][j]));
        }
    }
    nodes = _nodes;
    edges = _edges;
}
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
    cout << "\n######## RUNNING FLOYD-WARSHALL ########" << endl;
    
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
            if (dist[i][j] == INFINITO)
                cout << "\t∞ ";
            else cout << "\t" << dist[i][j];
        }
        cout << endl;
    }
    cout << endl;
}





//----------------------------------------------------------------------------------------------FORD-FULKERSON
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

Node* Graph::findNode(int node){
    for (Node* n : nodes){
        if (n->number == node)
            return n;
    }
    return nullptr;
}

Edge* Graph::findEdge(Node *u, Node *v) {
    Edge *e = nullptr;
    for (Edge* e : edges) {
        if (e->first == u && e->second == v)
            return e;
    }
    return e;
}


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
void Graph::findPaths(Node *s, Node *t, vector<int> &weights, vector<int> &values){
    int pathFlow = INT_MAX;
    vector<Edge*>::iterator ei;
    for(ei = edges.begin(); ei != edges.end(); ++ei) {
        (*ei)->flow = (*ei)->weight;
    }
    while(bfs(s, t)) {
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
