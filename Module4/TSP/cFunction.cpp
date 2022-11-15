#include "cFunctionP.h"

FunctionP::FunctionP(int _exitVal, vector<int> _set){
    vector<int>::iterator it;
    for(it = _set.begin(); it != _set.end(); it++){
        set.push_back(*it);
    }
    exitVal = _exitVal;
    result = 0;
}

// Encuentra todas las combinaciones de caminos en SET
vector<vector<int>> FunctionP::findPermutations(){
}    