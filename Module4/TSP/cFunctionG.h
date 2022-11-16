#pragma once
#include <iostream>
#include <vector>
using namespace std;

class FunctionG
{
public:
    vector<int> set; // conjunto que va a la derecha en p
    int exit_val;    // número que va a la izquierda en p
    int result;
    FunctionG(int exit_val, vector<int> set);

    string toString();

    vector<vector<int>> find_permutations();
};