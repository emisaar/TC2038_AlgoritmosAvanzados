#include "cFunctionG.h"

FunctionG::FunctionG(int _exit_val, vector<int> _set){
  // Copiar set
  vector<int>::iterator it;
  for (it = _set.begin() ; it != _set.end() ; ++it){
    set.push_back(*it);
  }
  exit_val = _exit_val;
  result = 0;
}

// Encuentra las combinaciones de caminos en SET
vector<vector<int>> FunctionG::find_permutations(){
  
}