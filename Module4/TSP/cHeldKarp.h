#pragma once
#include "Graph.hpp"
#include "cFunctionG.h"
using namespace std;

class HeldKarp{
public:
  vector<vector<FunctionG*>> prev_results;
  Graph* g;

  HeldKarp(Graph* _g);
  vector<int> findHamilton(Node* start);
  void findHamilton(Node*, int size);
  vector<int> values_without(vector<int> v, int to_remove);
  void combinationUntil(vector<int>& arr, int n, int r, int index, vector<int>& data, int i, vector<int>& combos);
};