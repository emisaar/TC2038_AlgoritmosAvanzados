
#pragma once
#include "Graph.hpp"
#include "cFunctionG.hpp"
using namespace std;

class HeldKarp
{
public:
  vector<vector<FunctionG *>> prev_results;
  Graph *g;

  HeldKarp(Graph *_g);
  vector<int> findHamilton(Node *start);
  void findHamilton(Node *start, int set_size);
  vector<int> values_without(vector<int> &v, int to_remove);
  void findCombinations(vector<int> &arr, int n, int r, int index, vector<int> &data, int i, vector<vector<int>> &combos);
  bool compareSets(vector<int> a, vector<int> b);
  int findPrevValueG(int e, vector<int> s);
  int findResultG(FunctionG *fg);
  int findResultP(vector<FunctionG *> vfg, Node *start);
};