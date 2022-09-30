//  Actividad 2.1
//  Implementación de "Hash String"
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 01/08/22.

// Referencias:
// https://www.geeksforgeeks.org/program-decimal-hexadecimal-conversion/

#include <iostream>
#include <vector>
#include <string>
#include <fstream> // leer el archivo

using namespace std;

/*
genCharVectorFromString > omplejidad --> O(1)
- Retorna un vector de caracteres a partir de un string
*/
vector<char> genCharVectorFromString(string s){
    vector<char> vecChar(s.begin(), s.end());
    return vecChar;
}

/*
readFile > Complejidad --> O(1)
- Permite la lectura de archivos a partir de un string de entrada (nombre del archivo + extensión
*/

vector<char> readFile(string s){
    ifstream lector(s);
    if (lector.fail()){
        cout << "\nError en la carga del archivo" << endl;
        exit(1);
    }
    string str((istreambuf_iterator<char>(lector)), istreambuf_iterator<char>());
    return genCharVectorFromString(str);
}

/*
makeTable > Complejidad --> O(n)
- Recibe:
    * Un vector (vc) que contiene todos los caracteres del archivo de entrada
    * Un int (lim) que corresponde al número de columnas seleccionadas por el usuario
*/
vector<vector<char> > makeTable(vector<char> vc, int lim){
    
    // Inicializar tabla de salida
    vector<vector<char> > table;

    // Rellenar elementos faltantes con caracter especial (*)
    while (vc.size() % lim != 0) {
        vc.push_back('*');
    }

    // Recorrer vector de caracteres para crear filas (row) con un size establecido por lim (número de columnas)
    for (int i = 0; i < vc.size() - 1; i += lim) {
        vector<char> row;
        for (int j = i; j < i + lim; j++) {
          row.push_back(vc[j]);
        }
        table.push_back(row);
    }

  return table;
}

/*
printTable > Complejidad --> O(n^2)
- Impresión del tablero, colocando símbolo especial (*) en saltos de línea
*/
void printTable(vector<vector<char> > vvc){
    for (int i = 0; i < vvc.size(); i++) {
        for (int j = 0; j < vvc[i].size(); j++) {
            if (vvc[i][j] == '\n' || vvc[i][j] == '\r'){
                cout << setfill('|') << setw(2) << '*';
            }else{
                cout << setfill('|') << setw(2) << vvc[i][j];
            }
        }
        cout << '|' << endl;
    }
}

/*
convertDecToHex > Complejidad --> O(n)
- Recibe un int (num) que corresponde al número decimal a convertir
*/
string convertDecToHex(int num){
    // Arreglo tipo char para almacenar el valor hexadecimal
    char h[100];
    string hex;
 
    // Contador para el arreglo del número hexadecimal
    int cnt = 0;
    while (num != 0) {
        // Variable temporal para guardar el residuo
        int temp = 0;
        temp = num % 16;

        if (temp < 10) {
            h[cnt] = temp + 48;
            cnt++;
        } else {
            h[cnt] = temp + 55;
            cnt++;
        }
 
        num /= 16;
    }
 
    // Concatenar el valor hexadecimal de forma inversa
    for (int j = cnt - 1; j >= 0; j--)
        hex += h[j];

    return hex;
}

/*
computeHash > Complejidad --> O(n^2)
- Recibe de entrada la tabla
- Suma las columnas de la tabla y guarda los resultados en un arreglo. Estos valores se convierten 
posteriormente a hexadecimal y se concatenan en un string.
*/
string computeHash(vector<vector<char> > table){
    vector<int> values;
    string hexVec;
    int colSum = 0;

    for (int i = 0; i < table[0].size(); i++){
        for(int j = 0; j < table.size(); j++){
            char c = table[j][i];
            colSum += (int)c;
        }
        values.push_back(colSum % 256);
        colSum = 0;
    }

    for(int i = 0; i < values.size(); i++){
       if (convertDecToHex(values[i]).size() > 1) {
        hexVec += convertDecToHex(values[i]);
    } else {
      hexVec += "0";
      hexVec += convertDecToHex(values[i]);
    }
    }

    return hexVec;
}


int main() {
    int width = 0;
    string filename = "";

    cout << "Ingresar ancho de la tabla: ";
    cin >> width;
    cout << "Ingresar nombre del archivo: ";
    cin >> filename;
    cout << endl;
    
    vector<char> vc = readFile(filename);
    vector<vector<char> > charTable = makeTable(vc, width);
    cout << "Caracteres: " << vc.size() << endl;
    cout << "csize: " << vc.size() << endl;
    cout << "csize: " << charTable.size() * charTable[0].size() << endl;
    
    cout << "------------------ Tabla ------------------" << endl;
    printTable(charTable);

    cout << endl;
    string hash = computeHash(charTable);
    cout << "Resultado: " << hash << endl;
    cout << endl;
    cout << "N: " << width << endl;
    cout << "N*2: " << width * 2 << endl;
    cout << "Longitud del hash: " << hash.size() << endl;

}
