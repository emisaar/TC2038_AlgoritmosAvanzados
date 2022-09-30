#include <iostream>
#include <vector>

using namespace std;

// Funcionamiento del algoritmo:
// Comparar pattern[j] desde j = 0 con la ventana actual del texto original:
//     Seguimos comparando caracteres text[i] con pattern[j]
//     Incrementamos i y j mientras text[i] == pattern[j]
//     (En particular, notar que j se incrementa después de revisar)
//     Al detectar que no son iguales:
//     	* Sabemos que pattern[0..j-1] son iguales que text[i-j..i-1]
//     	* Sabemos que LPPS[j-1] cuenta los caracteres de pattern[0..j-1] 
//     	    que son prefijo propio y también sufijo.
//     	* Concluimos que no se requiere revisar estos LPPS[j-1] caracteres
//     	    contra text[i-j..i-1] porque sí son iguales.

vector<char>RandomVector::genCharVectorFromString(string s){
    vector<char> charsVector(s.begin(), s.end());
    return charsVector;
}

void RandomVectors::print

int main(){
    string pattern = "AAACAAAAAC";
    vector<int> p = computeLPPS(pattern);

    for(int i = 0; i < p.size(); i++)
    cout << p[i] << ' ';

    return 0;
}
