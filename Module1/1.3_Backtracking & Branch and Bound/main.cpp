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
#include <queue>
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

void branchAndBound(vector<vector<int> > b, vector<vector<int> > &sol, int x, int y, vector<vector<int> > &visited, bool &hasArrived){
  // Determinar dimensiones del tablero
  int M = b.size();
  int N = b[0].size();

  int columns = x;
  int rows = y;

  vector<int> currPos;

  for(int i = 0; i < visited.size(); i++){
    cout << "(";
    for(int j = 0; j < visited[0].size(); j++){
      cout << visited[i][j];
    }
      cout << "), "; 
  }

  // Primera posición
  if(x == 0 && y == 0){
    sol[y][x] = 1;
  }

  // cout << "bef" << endl;
  // Caso base: Posición actual == b[N - 1][M - 1]
  if ((x == N - 1) && (y == M - 1)){
    // cout << "ins" << endl;
    sol[y][x] = 1;

    // Validar que ha finalizado de recorrer el tablero
    hasArrived = true;
    return;

  } else {
    // cout << "else" <<endl;
    // Revisar derecha
    int right = x + 1;
    // cout << b[rows][right] << endl;
    if (right <= N && b[rows][right] == 1 && hasArrived == false){
      cout << "Check right" << endl;
      // cout << "right" << endl;

      // Revisar si position actual se encuentra dentro de las posiciones visitadas
      // currPos = {rows, right};
      currPos.push_back(rows);
      currPos.push_back(right);
      vector<vector<int> >::iterator it;
      it = find(visited.begin(), visited.end(), currPos);
      // En caso de haber sido visitado, eso quiere decir que no lleva a la meta
      if(it == visited.end()){
        cout << "not" << endl;
        sol[right][columns] = 1;
        visited.push_back(currPos);
        branchAndBound(b, sol, right, rows, visited, hasArrived);
      }else{
        cout << "found" << endl;
        // cout << "else right" << endl;
        sol[rows][columns] = 0;
        return;
      }

      // cout << "t.t" << endl;
    }

    // Revisar izquierda
    int left = x - 1;
    if (left >= 0 && b[rows][left] == 1 && hasArrived == false){
      cout << "Check left" << endl;

      // Revisar si position actual se encuentra dentro de las posiciones visitadas
      // currPos = {rows, left};
      currPos.push_back(rows);
      currPos.push_back(left);
      vector<vector<int> >::iterator it;
      it = find(visited.begin(), visited.end(), currPos);
      // En caso de haber sido visitado, eso quiere decir que no lleva a la meta (0)
      if(it == visited.end()){
        cout << "not" << endl;
        sol[rows][left] = 1;
        visited.push_back(currPos);
        branchAndBound(b, sol, left, rows, visited, hasArrived);
      }else{
        cout << "found" << endl;
        sol[rows][columns] = 0;
        return;
      }
    }

    // Revisar arriba
    int up = y - 1;
    if (up >= 0 && b[up][columns] == 1 && hasArrived == false){
      cout << "Check up" << endl;

      // Revisar si position actual se encuentra dentro de las posiciones visitadas
      // currPos = {up, columns};
      currPos.push_back(up);
      currPos.push_back(columns);
      vector<vector<int> >::iterator it;
      it = find(visited.begin(), visited.end(), currPos);
      // En caso de haber sido visitado, eso quiere decir que no lleva a la meta (0)
      if(it == visited.end()){
        cout << "not" << endl;
        sol[up][columns] = 1;
        visited.push_back(currPos);
        branchAndBound(b, sol, columns, up, visited, hasArrived);
      }else{
        cout << "found" << endl;
        sol[rows][columns] = 0;
        return;
      }
    }

    

    // Revisar abajo
    int down = y + 1;
    if (down <= M && b[down][columns] == 1 && hasArrived == false){
      cout << "Check down" << endl;
      // cout << "down" << endl;

      // Revisar si position actual se encuentra dentro de las posiciones visitadas
      // currPos = {down, columns};
      currPos.push_back(down);
      currPos.push_back(columns);
      vector<vector<int> >::iterator it;
      it = find(visited.begin(), visited.end(), currPos);
      // En caso de haber sido visitado, eso quiere decir que no lleva a la meta (0)
      if(it == visited.end()){
        cout << "not" << endl;
        // cout << "if" << endl;
        sol[down][columns] = 1;
        visited.push_back(currPos);
        branchAndBound(b, sol, columns, down, visited, hasArrived);
      }else{
        cout << "found" << endl;
        // cout << "else" << endl;
        sol[rows][columns] = 0;
        return;
      }
    }
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
    branchAndBound(board, sol, initPos[0], initPos[1], visited, hasArrived);
    imprimeTablero(sol);
}