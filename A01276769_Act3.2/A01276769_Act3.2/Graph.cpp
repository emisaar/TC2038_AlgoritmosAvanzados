//  Actividad 3.3
//  Flujo Máximo
//
//  Alejandro Díaz Villagómez | A01276769
//
//  Fecha: 17/10/2022
//
//  Referencias:
//  https://favtutor.com/blogs/ford-fulkerson-algorithm
//  https://github.com/fit-coder/fitcoderyoutube/blob/master/graph/ford_fulkerson.cpp
//  https://www.programiz.com/dsa/ford-fulkerson-algorithm
//  https://github.com/BedirT/Algorithms_and_DS/blob/master/Algorithms/Graph/Ford%20Fulkerson.cpp
//  https://www.youtube.com/watch?v=_UcOALraATY

#include "Graph.hpp"
#include <queue>

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
            _edges.push_back(new Edge(_nodes[i], _nodes[j], matGraph[i][j], 0));
        }
    }
    nodes = _nodes;
    edges = _edges;
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

//FUNCIÓN PRINT: Imprimimos el grafo según el recorrido de Dijkstra
//Complejidad --> O(n)
void Graph::printDijkstra(Node* source){
    for (Node* n : nodes){
        if (n->number == source->number) continue;
        cout << "\tnode " << source->number << " to node " << n->number << " : " << n->distance << endl;
    }
    //cout << endl;
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


int Graph::bfs(Node* s, Node* t, vector<Node*>& flow, vector<vector<int>>& path){
    int V = (int)path.size();
    s->distance = -2;
    flow[s->number - 1] = s;
    
    queue<pair<Node*, int>> q;
    //Falta agregar librería para calcular INT_MAX
    q.push({s, INFINITO});
    
    while (!q.empty()) {
        Node* u = q.front().first;
        int capacity = q.front().second;
        q.pop();
        
        for (int av = 0; av < V; av++){
            if (u->number - 1 != av and flow[av]->distance == -1 and path[u->number - 1][av] != 0){
                flow[av] = u;
                int min_cap = min(capacity, path[u->number - 1][av]);
                
                if (av == t->number - 1)
                    return min_cap;
                q.push({flow[av], min_cap});
            }
        }
    }
    return 1000;
}

//int Graph::FordFulkerson(Node* s, Node* t){
int Graph::FordFulkerson(int sInt, int tInt, vector<vector<int>>& graph){
    int max_flow = 0, min_cap = 0;
    vector<vector<int>> path = graph;
    vector<Node*> flow = nodes;
    for (Node* f : flow){
        f->distance = -1;
        f->prev = nullptr;
    }
    Node* s = flow[sInt - 1];
    Node* t = flow[tInt - 1];
    
    
    while (min_cap = bfs(s, t, flow, path)) {
        max_flow += min_cap;
        Node* end = t;
        while (s != end) {
            Node* v = flow[s->number];
            path[s->number - 1][v->number - 1] += min_cap;
            path[v->number - 1][s->number - 1] -= min_cap;
            s = v;
        }
    }
    
    return max_flow;
}
