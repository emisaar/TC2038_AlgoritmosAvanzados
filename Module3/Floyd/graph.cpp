#include "Graph.h"

Graph::Graph(vector<Node*> _nodes, vector<Edge*> _edges){
    nodes = _nodes;
    edges = _edges;
}

vector<Node*> Graph::getNeighbors(Node *n){
    vector<Node*> neighbors;
    for (int i = 0; i < edges.size(); i++){
        if (edges[i]->first == n){
            neighbors.push_back(edges[i]->second);
        }
        else if (edges[i]->second == n){
            neighbors.push_back(edges[i]->first);
        }
    }
    return neighbors;
}

void Graph::print(){
    cout << "Nodes:" << endl;
    for (int i = 0; i < nodes.size(); i++){
        cout << "N: " << nodes[i]->number << " P: " << nodes[i]->prev << " D: " << nodes[i]->distance << endl;
    }

    cout << "\nEdges:" << endl;
    for (int i = 0; i < edges.size(); i++){
        cout << "N1: " << edges[i]->first->number << " N2: " << edges[i]->second->number << " D: " << edges[i]->weight << endl;
    }
}

void Graph::runDijkstra(Node *source) {
    vector<Node*> Q;
    
    for (int v = 0; v < nodes.size(); v++){
        nodes[v]->distance = 1000;
        nodes[v]->prev = nullptr;
        Q.push_back(nodes[v]);
    }

    source->distance = 0;

    while (!Q.empty()) {
        Node *u = getMinDist(Q);
        remove(Q, u);
        vector<Node*> neighbors = getNeighbors(u);
        for(int n = 0; n < neighbors.size(); n++) {
            int alt;
            Node *v = neighbors[n];
            alt = u->distance + getLength(u, v);
            if(alt < v->distance) {
                v->distance = alt;
                v->prev = u;
            }
        }
    }
}

Node * Graph::getMinDist(vector<Node*> qs) {
    Node *min = qs[0];
    for (int i = 0; i < qs.size(); i++){
        if (qs[i]->distance < min->distance){
            min = qs[i];
        }
    }
    return min;
}

void Graph::remove(vector<Node*> &qs, Node *q) {
    for(int i = 0; i < qs.size(); i++) {
        if(q == qs[i]){
            qs.erase(qs.begin() + i);
        }
    }
}

int Graph::getLength(Node *u, Node *v) {
    return abs(u->distance - v->distance);
}