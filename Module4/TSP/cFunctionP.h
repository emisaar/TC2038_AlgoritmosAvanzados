#pragma once
#include <iostream>
#include <vector>
using namespace std;

class FunctionP{
    public:
        vector<int> set; // Conjunto que va a la derecha en p
        int exitVal; // Número que va a la izquierda en p
        int result; // resultado de evaluar p
        FunctionP(int _exitVal, vector<int> _set);

        vector<vector<int>> findPermutations();
};