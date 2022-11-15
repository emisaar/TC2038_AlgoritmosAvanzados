//  Actividad Integradora 1
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 08/09/2022
//
//  Referencias:
//          Parte 1:
//          https://www.youtube.com/watch?v=V5-7GzOfADQ
//          https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
//
//          Parte 2:
//          https://www.youtube.com/watch?v=SV1ZaKCozS4&t=581s
//          https://leetcode.com/problems/longest-palindromic-substring/discuss/378722/Java-Manacher's-Algorithm-with-detailed-comments-beats-99.34!
//
//          Parte 3:
//          https://www.programiz.com/dsa/longest-common-subsequence#:~:text=The%20longest%20common%20subsequence%20(LCS,positions%20within%20the%20original%20sequences.


#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
using namespace std;

// ============================================================= LECTURA DE ARCHIVO
/*
 Los archivos de transmision contienen caracteres de texto que representan
 el envío de datos de un dispositivo a otro.
 Los archivos mcodex.txt representan código malicioso que se puede encontrar
 dentro de una transmisión.
 */
vector<char> genCharVectorFromString(string s){
    vector<char> vecChar(s.begin(), s.end());
    return vecChar;
}

vector<char> readFile(string s){
    ifstream lector(s);
    if (lector.fail()){
        cout << "\nError en la carga del archivo" << endl;
        exit(1);
    }
    string str((istreambuf_iterator<char>(lector)), istreambuf_iterator<char>());
    return genCharVectorFromString(str);
}

// ============================================================= PARTE 1
/*
 El programa debe analizar si el contenido de los archivos mcode1.txt,
 mcode2.txt y mcode3.,txt están contenidos en los archivos transmission1.txt
 y transmission2.txt y desplegar un true o false si es que las secuencias de
 chars están contenidas o no. En caso de ser true, muestra true, seguido de
 exactamente un espacio, seguido de la posición en el archivo de transmissiónX.txt
 donde inicia el código de mcodeY.txt
 */

//Complejidad O(n)
vector<int> computeLPS(vector<char> pattern){
    vector<int> lps(pattern.size(), 0);
    
    int posPrevia = 0, posActual = 1;
    
    while (posActual < pattern.size()) {
        //Si dos posiciones consecutivas coinciden, significa que sus sufijos y prefijos también lo hacen,
        //por ello, lps en la posición actual es igual a la posición previa + 1. Movemos ambos iteradores
        //a la derecha
        if (pattern[posActual] == pattern[posPrevia]){
            lps[posActual] = posPrevia + 1;
            posPrevia += 1;
            posActual += 1;
        }
        //Si pp == 0, se traduce en que no hubo coincidencias, por lo que lps en
        //la posición actual es 0. Actualizamos el valor de pa+=1 (a la derecha)
        else if (posPrevia == 0){
            lps[posActual] = 0;
            posActual += 1;
        }
        //Si no coinciden recorremos el iterador pp a la izquierda, con respecto el valor de lps[pp-1], para
        //buscar alguna coincidencia. No necesariamente disminiye 1 unidad.
        else posPrevia = lps[posPrevia - 1];
    }
    
    return lps;
}


//Complejidad O(m+n)
int KMPSearch(vector<char> pat, vector<char> txt){
    int M = pat.size();
    int N = txt.size();
    
    //Valor para almacenar el índice en donde empieza la coincidencia en transmissiónX.txt
    int index = INT_MIN;
    
    //Mandamos llamar el preproceso para clacular la tabla LPS
    //Complejidad O(n)
    vector<int> lps = computeLPS(pat);
    
    //Iterador para la cadena (i) y subcadena (j)
    int i = 0, j = 0;
    
    //Complejidad O(m)
    while ((N - i) >= (M - j)) {
        //Hay coincidencia, recorremos a la derecha ambos iteradores
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        //Si j recorre toda la subcadena, significa que el patrón existe en el texto
        if (j == M) {
            //Calculamos el índice
            index = i - j;
            break;
            //j = lps[j - 1];
        }
 
        //Hay un mismatch
        else if (i < N && pat[j] != txt[i]) {
            // Nos apoyamos de la tabla LPS
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return index;
}

// ============================================================= PARTE 2
/*
 Suponiendo que el código malicioso tiene siempre código "espejeado" (palíndromos de chars),
 sería buena idea buscar este tipo de código en una transmisión. El programa después debe
 buscar si hay código "espejeado" dentro de los archivos de transmisión. (palíndromo a nivel
 chars, no meterse a nivel bits). El programa muestra en una sola linea dos enteros separados
 por un espacio correspondientes a la posición (iniciando en 1) en donde inicia y termina el
 código "espejeado" más largo (palíndromo) para cada archivo de transmisión. Puede asumirse
 que siempre se encontrará este tipo de código.
 */

//Complejidad O(n)
pair<int, int> longestPalindrome(vector<char> cadena) {
    //Creamos un vector char que contenga los caracteres especiales
    vector<char> cadManacher;
    
    //Complejidad O(n)
    for (int i = 0; i < cadena.size(); i++){
        cadManacher.push_back('#');
        cadManacher.push_back(cadena[i]);
    }
    cadManacher.push_back('#');
    
    //Creamos el vector que almacene las diferentes longitudes de los palíndromos
    vector<int> longPalindrome(cadManacher.size(), 0);
    
    //Definimos 2 variables que funcionarán como apuntadores:
    //centro (línea de espejismo) y límite derecho
    int center = 0, right = 0;
    
    //Iteramos cadManacher de manera efectiva, es decir, evitando,
    //estratégicamente, algunas iteraciones
    //Complejidad O(n)
    for (int i = 1; i < longPalindrome.size() - 1; i++) {
        //Valor del índice a la izquierda del espejo
        int mirror = center - (i - center);
        
        //Corroborar que el iterador i no sobrepasa el límite de la derecha (right)
        if (right > i) {
            longPalindrome[i] = min(right  - i, longPalindrome[mirror]);
        }
        
        //Aplicamos la "expansión"
        while (cadManacher[i + (1 + longPalindrome[i])] == cadManacher[i - (1 + longPalindrome[i])]) {
            longPalindrome[i]++;
        }
        
        // Si la expansión va más allá del límite derecho, es necesario actualizar el centro y el límite derecho
        if (i + longPalindrome[i] > right) {
            center = i;
            right = i + longPalindrome[i];
        }
    }
    //Buscamos el palíndromo más largo y su índice
    int maxLen = 0, centerIdx = 0;
    for (int i = 1; i < longPalindrome.size() - 1; i++) {
        if (longPalindrome[i] > maxLen) {
            maxLen = longPalindrome[i];
            centerIdx = i;
        }
    }

    int inicio =(centerIdx - 1 - maxLen) / 2;
    int fin = (centerIdx - 1 + maxLen) / 2;
    
    //El índice debe iniciar en 1, no en 0
    pair<int, int> res = make_pair(inicio + 1, fin);
    return res;
}



 
 

// ============================================================= PARTE 3
/*
 Finalmente el programa analiza que tan similares son los archivos de transmisión, y debe
 mostrar la posición inicial y la posición final (iniciando en 1) del primer archivo en
 donde se encuentra el substring más largo común entre ambos archivos de transmisión
 */

//Complejidad O(n*m)
//Como solo necesitamos calcular los índices, podemos evitar pasos para acelerar la función
//pair<int, int> makeLCSTables(vector<char> x, vector<char> y, vector<vector<string>> &B, vector<vector<int>> &C){
pair<int, int> makeLCSTables(vector<char> x, vector<char> y){
    int m = x.size();
    int n = y.size();
    
    //Variabales para una bandera, el índice de inicio y el índice final
    int flag = 0, start = 0, end = 0;
    
    /*
    for (int i = 0; i <= m; i++){
        vector<int> rowC(n+1, 0);
        C.push_back(rowC);
        
        vector<string> rowB(n+1, "*");
        B.push_back(rowB);
    }
     */
    //Complejidad O(m*n)
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            //Encontramos una coincidencia, por ello, almacenamos el índice en la variable
            //que corresponda
            if (x[i-1] == y [j-1]){
                //C[i][j] = C[i-1][j-1] + 1;
                //B[i][j] = "D";
                //Si flag == 0, significa que i representa el índice del inicio
                if (flag == 0){
                    start = i;
                    flag = 1;
                }
                //En caso contrario, actualizamos el valor del índice que representa el final
                else end = i;
            }
            else{
                /*
                if (C[i-1][j] > C[i][j-1]){
                    C[i][j] = C[i-1][j];
                    B[i][j] = "U";
                }
                else{
                    C[i][j] = C[i][j-1];
                    B[i][j] = "L";
                }
                 */
                continue;
            }
        }
    }
    
    pair<int, int> res = make_pair(start, end);
    return res;
}






int main(){
    //======================================================================= LECTURA DE ARCHIVOS
    vector<char> mcode1 = readFile("/Users/alejandrodiazvillagomez/Desktop/SP1a/mcode1.txt");
    vector<char> mcode2 = readFile("/Users/alejandrodiazvillagomez/Desktop/SP1a/mcode2.txt");
    vector<char> mcode3 = readFile("/Users/alejandrodiazvillagomez/Desktop/SP1a/mcode3.txt");
        
    vector<char> transmission1 = readFile("/Users/alejandrodiazvillagomez/Desktop/SP1a/transmission1.txt");
    vector<char> transmission2 = readFile("/Users/alejandrodiazvillagomez/Desktop/SP1a/transmission2.txt");
    
    
    //======================================================================= PARTE 1
    cout << "PARTE 1: Substring Search (KMP Algorithm)" << endl;
    
    int kmpIndex1 = KMPSearch(mcode1, transmission1);
    int kmpIndex2 = KMPSearch(mcode2, transmission1);
    int kmpIndex3 = KMPSearch(mcode3, transmission1);
    
    int kmpIndex4 = KMPSearch(mcode1, transmission2);
    int kmpIndex5 = KMPSearch(mcode2, transmission2);
    int kmpIndex6 = KMPSearch(mcode3, transmission2);
    
    vector<int> kmpIndices = {kmpIndex1, kmpIndex2, kmpIndex3, kmpIndex4, kmpIndex5, kmpIndex6};
    
    for (int i = 0; i < kmpIndices.size(); i++){
        if (i < 3)
            cout << "\ttransmission1.txt && mcode" << i + 1 << ".txt --> ";
        else
            cout << "\ttransmission2.txt && mcode" << i - 2 << ".txt --> ";
        
        if (kmpIndices[i] != INT_MIN)
            cout << "true   |   index: " << kmpIndices[i] << endl;
        else cout << "false" << endl;
    }
    
    //======================================================================= PARTE 2
    cout << "\nPARTE 2: Longest Palindromic String (Manacher Algorithm)" << endl;
    pair<int, int> manacherIndex1 = longestPalindrome(transmission1);
    pair<int, int> manacherIndex2 = longestPalindrome(transmission2);
    
    cout << "\tLPS transmission1.txt --> startIndex: " << manacherIndex1.first
    << "  |  lastIndex: " << manacherIndex1.second << endl;
    cout << "\tLPS transmission2.txt --> startIndex: " << manacherIndex2.first
    << "  |  lastIndex: " << manacherIndex2.second << endl;
    
    
    
    //======================================================================= PARTE 3
    cout << "\nPARTE 3: Longest Common Subsequence (Dynamic Programming)" << endl;
    
    pair<int, int> LCSIndex = makeLCSTables(transmission1, transmission2);
    cout << "\tLCS transmission1.txt --> startIndex: " << LCSIndex.first
    << "  |  lastIndex: " << LCSIndex.second << endl;
    
    pair<int, int> LCSIndex2 = makeLCSTables(transmission2, transmission1);
    cout << "\tLCS transmission2.txt --> startIndex: " << LCSIndex2.first
    << "  |  lastIndex: " << LCSIndex2.second << endl;
    
    cout << endl;
}
