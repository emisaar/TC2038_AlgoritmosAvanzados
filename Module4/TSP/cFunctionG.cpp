#include "cFunctionG.h"

FunctionG::FunctionG(int _exit_val, vector<int> _set)
{
    // Copiar set
    vector<int>::iterator it;
    for (it = _set.begin(); it != _set.end(); ++it)
    {
        _set.push_back(*it);
    }
    exit_val = _exit_val;
    result = 0;
}

string FunctionG::toString()
{
    string s = "G(" + to_string(exit_val) + ", {";
    vector<int>::iterator it;
    for (it = set.begin(); it != set.end(); ++it)
    {
        s += to_string(*it) + ", ";
    }
    s += "})";
    return s;
}