//  Actividad Integradora 2
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 17/11/2022

#include "cHeldKarp.hpp"
#include <limits.h>

// CONSTRUCTOR HELDKARP
// Complejidad: O(1)
HeldKarp::HeldKarp(Graph *_g)
{
    g = _g;
}

// FUNCIÓN FINDHAMILTON
// Complejidad: O(n^2 * 2^n)
vector<int> HeldKarp::findHamilton(Node *start)
{
    // Llama a findHamilton(start, size_i) donde size_i va de 0 a N-1
    // Guarda functionP (obtiene el mejor costo) para el tamaño size_i y agrega a un vector de valores P
    // Construye el path final usando el vector de valores P
    
    for (int s = 0; s < g->nodes.size() - 1; ++s) {
        // cout << "s: " << s << endl;
        findHamilton(start, s);
    }

    vector<int> finalSet;
    // Agrega todos los nodos a un set
    vector<Node *>::iterator ni;
    for (ni = g->nodes.begin(); ni != g->nodes.end(); ++ni) {
        finalSet.push_back((*ni)->number);
    }
    // Quita el nodo inicial
    finalSet = values_without(finalSet, start->number);

    FunctionG *fg = new FunctionG(start->number, finalSet);
    fg->result = findResultG(fg);
    
    vector<FunctionG *> finalLevel;
    finalLevel.push_back(fg);
    prev_results.push_back(finalLevel);

    // Opcional. Para comprobar el funcionamiento:
    cout << "Functions G: {" << endl;
    vector<vector<FunctionG *>>::iterator ri;
    for (ri = prev_results.begin(); ri != prev_results.end(); ++ri) {
        cout << endl << "[" << endl;
        vector<FunctionG *>::iterator fi;
        for (fi = (*ri).begin(); fi != (*ri).end(); ++fi) {
            cout << (*fi)->toString() << endl;
        }
        cout << "]" << endl;
    }
    cout << "}" << endl;

    // Encontrar los valores P
    vector<int> valuesP = findResultP(start);
    // for (ri = prev_results.begin(); ri != prev_results.end(); ++ri) {
    //     int p = findResultP(*ri, start);
    //     valuesP.push_back(p);
    // }

    // valuesP.push_back(start->number); // Salir del inicio

    // Opcional. Mostrar el recorrido TSP obtenido
    cout << endl << "\tTSP: ";
    vector<int>::reverse_iterator pi;
    for (pi = valuesP.rbegin(); pi != valuesP.rend(); ++pi) {
        if (pi + 1 != valuesP.rend())
            cout << to_string(*pi) << " --> ";
        else
            cout << to_string(*pi) << endl;
    }
    return valuesP;
}

// FUNCIÓN FINDHAMILTON
// Complejidad: O(n^2)
// Construye todos los subconjuntos de tamaño set_size
void HeldKarp::findHamilton(Node *start, int set_size) {
    if (set_size == 0) {
        vector<FunctionG *> prev; // prev es nuevo porque estamos en tamaño 0.
        
        // Tomar los nodos que llegan a start y construir conjuntos + FunctionG.
        vector<Edge *>::iterator ei;
        for (ei = g->edges.begin(); ei != g->edges.end(); ++ei) {
            if ((*ei)->second == start){ // Llega a start
                vector<int> vi; // conjunto de tamaño 0
                FunctionG *fg = new FunctionG((*ei)->first->number, vi); // FunctionG con el nodo que llega a start
                fg->result = (*ei)->weight; // Costo de la arista
                // Lo anterior es:   g(vecino de start, {})
                prev.push_back(fg);
            }
        }
        prev_results.push_back(prev);
    } else {
        vector<FunctionG *> curr;
        vector<FunctionG *> prev = prev_results[set_size - 1]; // prev es el vector anterior.
        
        // Ahora, los conjuntos salen de la combinación de la iteración anterior.
        vector<FunctionG *>::iterator gi;
        vector<int> values;

        // A. Toma los valores (únicos) de salida anteriores.
        for (gi = prev.begin(); gi != prev.end(); ++gi) {
            // Agrega los valores de salida a un vector
            if (std::find(values.begin(), values.end(), (*gi)->exit_val) == values.end()) { // Si no se encuentra
                values.push_back((*gi)->exit_val); // Agregarlo para que sea único
            }
            // cout << "values: " << (*gi)->exit_val << endl;
        }

        // B. Combínalos con conjuntos creados a partir de los demás valores, sin pasar del tamaño del conjunto. 
            //Si es necesario, hacer más conjuntos.
        vector<int>::iterator vi;
        for (vi = values.begin(); vi != values.end(); ++vi) {
            vector<int> superset = values_without(values, *vi); // Quita el valor actual
            vector<vector<int>> subsets; // Subconjuntos de tamaño set_size
            vector<int> d(set_size, 0); // Vector de ceros tamaño set_size
            findCombinations(superset, superset.size(), set_size, 0, d, 0, subsets); 
            vector<vector<int>>::iterator si;
            for (si = subsets.begin(); si != subsets.end(); ++si) {
                FunctionG *fg = new FunctionG(*vi, *si);
                fg->result = findResultG(fg);
                curr.push_back(fg);
            }
        }
        prev_results.push_back(curr);
    }
}


// FUNCIÓN VALUES_WITHOUT: Regresa un vector de enteros con todos los valores excepto "to_remove"
// Complejidad: O(n)
vector<int> HeldKarp::values_without(vector<int> &v, int to_remove){
    vector<int> result;
    vector<int>::iterator vi;
    for (vi = v.begin(); vi != v.end(); ++vi)
        if ((*vi) != to_remove) result.push_back(*vi);
    return result;
}

/*
FUNCIÓN FINDCOMBINATIONS:
    Encuentra los posibles subconjuntos de arr (arr de tamaño n).
    Almacena estos subconjuntos en "combos".
    Los subconjuntos son de tamaño r.
    Original de: https://www.geeksforgeeks.org/print-subsets-given-size-set/

    Complejidad: O(n^r)
*/
void HeldKarp::findCombinations(vector<int> &arr, int n, int r, int index, vector<int> &data, int i, vector<vector<int>> &combos) {
    if (index == r) {
        // Un subconjunto está listo (de data[0] a data[r]), lo guardamos en combos:
        vector<int> subset;

        for (int j = 0; j < r; j++){
            subset.push_back(data[j]);
        }
        combos.push_back(subset);
        return;
    }

    if (i >= n) return; // No hay más elementos
    data[index] = arr[i]; // Agrega el elemento a data
    findCombinations(arr, n, r, index + 1, data, i + 1, combos); // Recursión
    findCombinations(arr, n, r, index, data, i + 1, combos); // Recursión
}

/*
FUNCIÖN COMPARESETS:
    Compara dos vectores de enteros.
    Regresa true si contienen los mismos elementos (no necesariamente ordenados), false si no.
    Complejidad: O(n^2)
*/
bool HeldKarp::compareSets(vector<int> a, vector<int> b) {
    if (a.size() == b.size()){
        vector<int>::iterator ia;
        for (ia = a.begin(); ia != a.end(); ++ia){
            if (std::find(b.begin(), b.end(), *ia) == b.end()) return false;
        }
        return true;
    }
    return false;
}

/*
FUNCIÓN findResultG:
    Busca en prev_results el resultado de la función g(e, s) para un conjunto s.
    Si no encuentra dicha función, regresa -1.
    Complejidad: O(n^2)
*/
int HeldKarp::findPrevValueG(int e, vector<int> s)
{
    int sizeToFind = s.size();
    vector<FunctionG *> search_space = prev_results[sizeToFind];
    vector<FunctionG *>::iterator gi;
    for (gi = search_space.begin(); gi != search_space.end(); ++gi)
    {
        if ((*gi)->exit_val == e && compareSets(s, (*gi)->set))
            return (*gi)->result;
    }

    FunctionG *fg = new FunctionG(e, s);
    cout << "Warning: Previous FuncionG not found: " << fg->toString() << endl;
    return -1;
}

/*
FUNCIÓN findResultG:
    Regresa el resultado de la función g(e, s).
    g(exit, S) = min{Edge(Si, exit) + g(Si, S - {Si})} para toda Si en el conjunto S.
    Es decir, g(exit, S) = min{peso del arco de Si hasta exit + g(Si, S menos el elemento Si)}.
    Complejidad: O(n^2)
*/
int HeldKarp::findResultG(FunctionG *fg) {
    vector<int>::iterator si;
    vector<int> candidates;

    for (si = fg->set.begin(); si != fg->set.end(); ++si) {
        vector<int> subset = values_without(fg->set, *si);
        Edge *e = g->findEdge2(fg->exit_val, *si);
    
        if (e != nullptr){
            int c = e->weight + findPrevValueG(*si, subset);
            candidates.push_back(c); // weight(Si, exit) + g(Si, S - {Si})
        } else {
            cout << "Warning: Edge not found from: " << to_string(fg->exit_val) << "to" << to_string(*si) << "." << endl;
        }
    }

        if (candidates.size() == 0) {
            cout << "Warning: candidates for findWeight is empty: " << fg->toString() << endl;
            return -1;
        }

        int minC = *std::min_element(candidates.begin(), candidates.end());
        return minC;
}

/*
FUNCIÓN findResultP:
    Para encontrar el valor de P:
        1. Encontrar el mínimo valor de fg para este tamaño de conjunto.
        2. El valor de P será el penúltimo nodo en el conjunto S, hacia la salida.
        2.1 Si S == {} entonces P = salida.
        2.2 Si |S| < 2 entonces no tiene penúltimo elemento y se toma el único disponible.

    Complejidad: O(n^2) 
*/
vector<int> HeldKarp::findResultP(Node* start)
{
	vector<int> tsp = { start->number };
	vector<int> tempSet;
	int counter = 1;
	for (int r = prev_results.size() - 1; r >= 0; r--)
	{
		vector<FunctionG*> gs = prev_results[r];
		if (r == prev_results.size() - 1)
		{
			int step = -1;
			if (gs[0]->set.size() > 1) step = gs[0]->set[1];
			else step = gs[0]->set[0];
			tempSet = values_without(gs[0]->set, step);
			tsp.push_back(step);
		}
		else
		{
			int step = -1;
			vector<FunctionG*>::iterator gi;
			for (gi = gs.begin(); gi != gs.end(); ++gi)
			{
				if ((*gi)->exit_val == tsp[counter-1] && compareSets(tempSet, (*gi)->set))
				{
					if ((*gi)->set.size() > 1) step = (*gi)->set[1];
					else if ((*gi)->set.size() == 1) step = (*gi)->set[0];
					else step = start->number;

					tempSet = values_without((*gi)->set, step);
					tsp.push_back(step);
				}
			}
		}
		counter++;
	}
	return tsp;
}