#include "cHeldKarp.h"

HeldKarp::HeldKarp(Graph* _g){
  g = _g;
}

vector<int> HeldKarp::findHamilton(Node* start){
    for (int s = 0; s < g->nodes.size() - 1; s++) {
        findHamilton(start, s);
    }

    vector<int> finalSet;
    vector<Node*>::iterator ni;

    for (ni = g->nodes.begin(); ni != g->nodes.end(); ++ni) {
        finalSet.push_back((*ni)->number);
    }
    finalSet = values_without(finalSet, start->number);

    FunctionG *fg = new FunctionG(start->number, finalSet);
    fg->result = findResultG(fg);
    vector<FunctionG*> finalLevel;
    finalLevel.push_back(fg);
    prev_results.push_back(finalLevel);

    // Opcional. Para comprobar el funcionamiento
    cout << "Functions G: {" << endl;
    vector<vector<FunctionG*>>::iterator ri;
    for (ri = prev_results.begin(); ri != prev_results.end(); ++ri) {
        cout << endl << "[" << endl;
        vector<FunctionG*>::iterator fi;
        for (fi = (*ri).begin(); fi != (*ri).end(); ++fi) {
            cout << "  " << (*fi)->toString() << endl;
        }
        cout << "]" << endl;
    }
    cout << "}" << endl << endl;

    // Encontrar los valores P
    vector<int> valuesP;
    for(ri = prev_results.begin(); ri != prev_results.end(); ++ri) {
        int p = findResultP(*ri, start);
        valuesP.push_back(p);
    }
    valuesP.push_back(start->number);

    // Opcional. Mostrar el recorrido TSP obtenido:
    cout << endl << "TSP: ";
    vector<int>::reverse_iterator pi;
    for (pi = valuesP.rbegin(); pi != valuesP.rend(); ++pi) {
        if (pi + 1 != valuesP.rend()) {
            cout << to_string(*pi) << " -> ";
        } else {
            cout << to_string(*pi) << endl;
        }
    }

    return valuesP;
}

void HeldKarp::findHamilton(Node* start, int set_size){
  // Llama a findHamilton(start, size_i) donde size_i va de 0 a N-1
  // Guarda funcitionP (aún no está hecha, obtiene el mejor costo) para el tamaño size_i y agrega a un vector de functionP
  // Construye el path final usando el vector de functionP

  if (set_size == 0){
    vector<FunctionG*> prev;  // Prev es nuevo porque estamos en tamaño 0.
    // Tomar los nodos que llegan a start y construir conjuntos + FunctionG.

    vector<Edge*>::iterator ei;

    for (ei = g->edges.begin(); ei != g->edges.end(); ++ei){
      if ((*ei)->second == start){   // Llega a start 
        vector<int> vi;  // conjunto de tamaño 0
        FunctionG* fg = new FunctionG((*ei)->first->number, vi);
        fg -> result = (*ei) -> weight;
        // Lo anterior es:   g(vecino de start, {})
        prev.push_back(fg);
      }
    }
    prev_results.push_back(prev);
  } else {

    vector<FunctionG*> curr;
    vector<FunctionG*> prev = prev_results[set_size - 1];   // prev es el vector anterior.
    // Ahora, los conjuntos salen de la combinación de la iteración anterior. 

    vector<FunctionG*>::iterator gi;
    vector<int> values;

    // A. Toma los valores (únicos) de salida anteriores.
    for (gi = prev.begin(); gi != prev.end(); ++gi){
      if (find(values.begin(), values.end(), (*gi)->exit_val) == values.end()){  // Si no se encuentra 
        values.push_back((*gi)->exit_val);  // Agregarlo para que sea único
      }  
    }

    // B. Combínalos con conjutnos creados a partir de los demás valores, sin pasar del tamaño del conjunto. Si es necesario, hacer más conjuntos.
    vector<int>::iterator vi;
    for(vi = values.begin() ; vi != values.end() ; ++vi){
      vector<int> superset = values_without(values, *vi);
      vector<vector<int>> subsets;
      vector<int> d(set_size, 0);
      findCombinations(superset, superset.size(), set_size, 0, d, 0, subsets);
      vector<vector<int>>::iterator si;

      for(si = subsets.begin(); si != subsets.end(); ++si){
        FunctionG *fg = new FunctionG(*vi, *si);
        fg->result = findResultG(fg);
        curr.push_back(fg);
      }
    }
    // Agregar curr a un vector de vectores de FunctionG
    
  }
  // Con ellos, construye los posibles sets 

  // crea los functionG con esos sets
  // guarda los functionG en los prev results
  prev_results.push_back(level);
}

vector<int> HeldKarp::values_without(vector<int> v, int to_remove){
  vector<int> result;
  vector<int>::iterator vi;
  for(vi = v.begin() ; vi != v.end( ; ++vi)
    if((*vi) != to_remove) result.push_back(*vi);
  return result;
}

void HeldKarp::findCombinations(vector<int>& arr, int n, int r, int index, vector<int>& data, int i, vector<int>& combos){
  // Current combination is ready, print it
  if (index == r){

    // Un subconjunto está listo, lo guardamos en combos:
    vector<int> subset;

    for( int j = 0 ; j < r ; j++){
      subset.push_back(data[j]);
    }
    combos.push_back(subset);
    return; 
  } if (i >= n) return;
  data[index] = arr[i];
  findCombinations(arr, n, r, index + 1, data, i + 1, combos);
  findCombinations(arr, n, r, index, data, i + 1, combos);
  
}