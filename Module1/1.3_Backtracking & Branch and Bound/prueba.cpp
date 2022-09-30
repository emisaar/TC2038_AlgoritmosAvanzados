//  Actividad 1.3
//  Implementación de la técnica de programación "backtracking" y "ramificación y poda"
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 15/08/22.
//  Referencia: 

#include <iostream>
#include <vector>

using namespace std;

void imprimeTablero(vector<vector<int> > b){
  int rows = b.size();
  int cols = b[0].size();
  for (int r = 0 ; r < rows ; r++){
    for(int c = 0 ; c < cols ; c++){
      cout << b[r][c] << " ";
    }
    cout << endl;
  }
}

vector<vector<int> > creaTablero(int m, int n){
  vector<vector<int> > board;
  for (int r = 0 ; r < m ; r++){
    vector<int> row;
    for(int c = 0 ; c < n ; c++){
      int a = 0;
      cin >> a;
      row.push_back(a);
    }
    board.push_back(row);
  }
  return board;
}

vector<vector<int> > creaTableroEmpty(int m, int n){
  vector<vector<int> > board;
  for (int r = 0 ; r < m ; r++){
    vector<int> row;
    for(int c = 0 ; c < n ; c++){
      row.push_back(0);
    }
    board.push_back(row);
  }
  return board;
}
void branchAndBound(vector<vector<int> > b, vector<vector<int> > &sol, vector<vector<int> > &visited){
  int row, column = 0;
  int M, N;

  M = b.size();
  N = b[0].size();
  // queue<pair<int, int>> boardqueue;

  while ((row != M - 1) && (column != N - 1)) {
    vector<int> currPos;
    row = visited.front().at(0);
    column = visited.front().at(1);
    visited.pop_back();

    // Check down if pos == 1
    if (row < M - 1) {
      if (b[row + 1][column] == 1) {
        currPos.push_back(row);
        currPos.push_back(column);
        visited.push_back(currPos);
        row++;
      }
    }

    // Check left
    if (column < N - 1) {
      if (b[row][column + 1] == 1) {
        currPos.push_back(row);
        currPos.push_back(column);
        visited.push_back(currPos);
        column++;
      }
    }

    // Check up
    if (row >= 0) {
      if (b[row - 1][column] == 1) {
        currPos.push_back(row);
        currPos.push_back(column);
        visited.push_back(currPos);
        row--;
      }
    }

    // Check left
    if (column >= 0) {
      if (b[row][column - 1] == 1) {
        currPos.push_back(row);
        currPos.push_back(column);
        visited.push_back(currPos);
        column--;
      }
    }
  }

  if (visited.back().at(0) == M - 1) {
    if (visited.back().at(1) == N - 1) {
      // Do nothing
    } else if (visited.back().at(1) + 1 == N - 1) {
      vector<int> p;
      p.push_back(visited.back().at(0));
      p.push_back(visited.back().at(1) + 1);
      visited.push_back(p);
    } else {
      cout << "Not possible to solve" << endl;
    }
  }

  int r, c;
  while(!visited.empty()){
    r = visited.front().at(0);
    c = visited.front().at(1);
    sol[r][c] = 1;
    visited.pop_back();
  }
}

int main() {
    int N, M;
    cout << "Ingresa el valor de N: ";
    cin >> N;

    cout << "Ingresa el valor de M: ";
    cin >> M;

    vector<vector<int> > board = creaTablero(M, N);

    vector<vector<int> > sol = creaTableroEmpty(M, N);

    vector<vector<int> > visited;
    vector<int> initPos;
    initPos.push_back(0);
    initPos.push_back(0);

    visited.push_back(initPos);
    bool hasArrived = false;

    cout << endl;
    cout << "--------------- Print Board ----------------" << endl;
    imprimeTablero(board);

    cout << "-------------- Branch & Bound --------------" << endl;
    branchAndBound(board, sol, visited);
    imprimeTablero(sol);
}